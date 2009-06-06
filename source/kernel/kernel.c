#include "video.h" 
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "keyboard.h"
#include "boot.h"
#include "syscalls.h"
#include "timer.h"
#include "mm.h"
#include "paging.h"

extern long kernelBegin;
extern long kernelEnd;

// makes our pretty ascii logo :)
void OutputAsciiHeader()
{
	ConsoleSetColor(COLOR_LBLUE, COLOR_BLACK);
	ConsolePuts(" ____    ____   _                   ___     ______   \n");
	ConsolePuts("|_   \\  /   _| (_)                .'   `. .' ____ \\  \n");
	ConsolePuts("  |   \\/   |   __  _   __  ,--.  /  .-.  \\| (___ \\_| \n");
	ConsolePuts("  | |\\  /| |  [  |[ \\ [  ]`'_\\ : | |   | | _.____`.  \n");
	ConsolePuts(" _| |_\\/_| |_  | | \\ \\/ / // | |,\\  `-'  /| \\____) | \n");
	ConsolePuts("|_____||_____|[___] \\__/  \'-;__/ `.___.'  \\______.' \n");
	ConsoleSetColor(COLOR_WHITE, COLOR_BLACK);
}

void kmain(void* mbd,unsigned int magic)
{
	struct MULTIBOOT_INFO bootInfo;
	InitBootData(mbd);
	GetBootInfo(&bootInfo);
	if (! InitKernel(&bootInfo)) {
		kprintf("\nError loading kernel...\n");
		return;
	}

	while (1);
}

//! Initializes basic kernel functionality...
BOOL InitKernel(struct MULTIBOOT_INFO *info)
{
	ConsoleCls(); // clear the screen
	// OutputAsciiHeader();	// optionally show the ascii header -- not yet 
	kprintf("MivaOS\nWritten by Christopher Coale and Tyler Littlefield.\n\nLoading... ");
	
	// We want to setup our GDT, IDT, ISRs, and IRQs, and setup system calls.
	GdtInstall();
	IdtInstall();
	IsrsInstall();
	IrqInstall();
	SetupSystemCalls();
	kprintf("success!\nLoading system timer... ");
	TimerInstall(100);
	kprintf("success!\nLoading system keyboard driver... ");
	KeyboardInstall();
	kprintf("success!\nInitializing system memory... \n");

	// Now we need to init our memory manager and set our regions
	unsigned long int totalMemory = info->mem_lower + info->mem_upper; // in KB??
	MemMgrInit(totalMemory*1024, (LPVOID)kernelBegin);

	// now we need to setup our memory regions...
	struct MEMORY_REGION *region = (struct MEMORY_REGION *)0x1000; // NOT kernelBegin!!
	int i = 0;
	for (i = 0; i < 15; ++i)
	{
		// quick sanity check...
		if (region[i].dwType > 4) region[i].dwType = 1;
		
		// if our base address is 0, we're done
		if ((i > 0) && (region[i].dwStartLo == 0)) break;

		// Display our region...
		kprintf("Region [%d]: start=0x%x%x, length=0x%x%x, type=%s\n", i, region[i].dwStartHi,
			region[i].dwStartLo, region[i].dwSizeHi, region[i].dwSizeLo, region[i].dwType,
			GSTR_MEMORY_TYPES[region[i].dwType - 1]);

		// if the region is available, lets use it!
		if (region[i].dwType == 1) MemMgrCreateRegion((LPVOID)region[i].dwStartLo, region[i].dwSizeLo);
	}

	// make sure we deinit the region our kernel is in...
//	MemMgrDeleteRegion(&kernelBegin, (&kernelEnd - &kernelBegin) * 512);
	
	// display memory information to the user...
	unsigned long int totalBlocks = MemMgrGetBlockCount();
	unsigned long int freeBlocks = MemMgrGetFreeBlockCount();
	kprintf("Total Memory: %dB\nLower Memory: %dB\nUpper Memory: %dB\nAllocation Blocks: %d\nReserved Blocks: %d\nFree Blocks: %d\n", totalMemory, info->mem_lower, info->mem_upper, totalBlocks, (totalBlocks - freeBlocks), freeBlocks);

	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 

	// all is good..
	return TRUE;
}
