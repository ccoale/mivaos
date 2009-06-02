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
	ConsoleCls();
	OutputAsciiHeader();
	ConsolePuts("\nMivaOS written by Chris Coale <chris95219@gmail.com) and Tyler Littlefield <tyler@tysdomain.com>.\n");
	ConsolePuts("MivaOS (kernel 0.0.1) Loading...\n");
	kprintf("Booting with %d KB lower memory and %d KB upper memory...\n", bootInfo.mem_lower, bootInfo.mem_upper);
	GdtInstall(); // setup gdt...
	IdtInstall(); // setup idt...
	IsrsInstall(); // setup isrs...			
	IrqInstall(); // setup irq...
	TimerInstall(100); // setup our timer...
	KeyboardInstall(); // setup our keyboard driver...
	SetupSystemCalls(); // setup our basic system calls...
	VirtMemMgrInitialize();
	kprintf("Kernel begin: %x\nKernel end: %x\nKernel length: %x\n", &kernelBegin, &kernelEnd, &kernelEnd - &kernelBegin);
	//MemMgrInit(bootInfo.mem_lower + bootInfo.mem_upper, 0x100000);
	
	
	struct DATE_TIME tm;
	TimerGetTime(&tm);
	kprintf("Today is %d/%d/%d and it is currently %d:%d:%d!\n", tm.month, tm.day, tm.year,
		tm.hour, tm.min, tm.sec);

	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 

	while (1);
} 
