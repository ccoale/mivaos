#include "video.h" 
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "keyboard.h"
#include "boot.h"
#include "syscalls.h"
#include "timer.h"
#include "physmm.h"

extern long kernelBegin;
extern long kernelEnd;
extern UINT* memStack[1024];
extern UINT memIndex;
DWORD memory[10];

//! Initializes basic kernel functionality...
BOOL InitKernel(struct MULTIBOOT_INFO *info);

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
int memIndex=0; //used for holding the index into the stack for memory blocks
struct mmap* map;
DWORD base,pages,index;

	ConsoleCls(); // clear the screen
OutputAsciiHeader();	// optionally show the ascii header -- not yet 
	kprintf("MivaOS\nWritten by Christopher Coale and Tyler Littlefield.\n\nLoading... ");
	
	// We want to setup our GDT, IDT, ISRs, and IRQs, and setup system calls.
	GdtInstall();
	IdtInstall();
	IsrsInstall();
	IrqInstall();
	SetupSystemCalls();
	TimerInstall(100);
	KeyboardInstall();
	kprintf("Memory lo: %d\nMemory hi: %d\n",
		info->memoryLo, info->memoryHi);

//we actually initialize our memory here
map=(struct mmap*)info->memMapAddr;
while ((UINT)map<(info->memMapAddr+info->memMapLength))
{
if (map->type==1)
{
base=map->base_l;
pages=map->length_l>>12; //divide by 4096
if (pages>0)
{
for (index=0;index<pages;index++)
{
memStack[memIndex]=(UINT*)(base+(4096*index));
memIndex++;
}
}
}
map=(struct mmap*)((UINT)map+map->size+sizeof(UINT));
}
kprintf("Allocated %d physical pages.\n",memIndex-1);
	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 

	// all is good..
	return TRUE;
}
