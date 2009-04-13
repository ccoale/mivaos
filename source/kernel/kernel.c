#include "video.h" 
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "keyboard.h"
#include "boot.h"

// makes our pretty ascii logo :)
void OutputAsciiHeader()
{
	ConsolePuts(" ____    ____   _                   ___     ______   \n");
	ConsolePuts("|_   \\  /   _| (_)                .'   `. .' ____ \\  \n");
	ConsolePuts("  |   \\/   |   __  _   __  ,--.  /  .-.  \\| (___ \\_| \n");
	ConsolePuts("  | |\\  /| |  [  |[ \\ [  ]`'_\\ : | |   | | _.____`.  \n");
	ConsolePuts(" _| |_\\/_| |_  | | \\ \\/ / // | |,\\  `-'  /| \\____) | \n");
	ConsolePuts("|_____||_____|[___] \\__/  \'-;__/ `.___.'  \\______.' \n");
}

void kmain(void* mbd,unsigned int magic)
{
	struct MULTI_BOOT_INFO *boot=(struct MULTI_BOOT_INFO*)mbd;
	ConsoleCls();
	OutputAsciiHeader();
	ConsolePuts("\nMivaOS written by Chris Coale <chris95219@gmail.com) and Tyler Littlefield <tyler@tysdomain.com>.\n");
	ConsolePuts("MivaOS (kernel 0.0.1) Loading...\n");
	kprintf("Booting with %d KB lower memory and %d KB upper memory...\n",boot->lowmem,boot->highmem);
	GdtInstall(); // setup gdt
	IdtInstall(); // setup idt
	IsrsInstall(); // setup isrs
	IrqInstall(); // setup irq
	TimerInstall(100); // setup our timer..
	KeyboardInstall();

	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 

	DWORD start = 0;

	while (1)
	{
		
	}
} 
