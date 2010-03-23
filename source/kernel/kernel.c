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
	ConsoleCls(); // clear the screen
OutputAsciiHeader();	// optionally show the ascii header -- not yet 
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

	// display some boot info
	kprintf((const char *)info->cmdLine);
	kprintf("Memory lo: %d\nMemory hi: %d\n",
		info->memoryLo, info->memoryHi);
	kprintf("Flags: %d\n", info->flags);
	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 

	// all is good..
	return TRUE;
}
