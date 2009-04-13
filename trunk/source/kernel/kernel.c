#include "video.h" 
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "keyboard.h"


void kmain(void* mbd,unsigned int magic)
{
	ConsoleCls();
	ConsolePuts("MivaOS (kernel 0.0.1) Loading...\n");
	GdtInstall(); // setup gdt
	IdtInstall(); // setup idt
	IsrsInstall(); // setup isrs
	IrqInstall(); // setup irq
	TimerInstall(100); // setup our timer..
	KeyboardInstall();

	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 
	DWORD start = 0;
	kprintf("The address of variable 'start' is at: %d.\n", &start);

	while (1)
	{
		
	}
} 
