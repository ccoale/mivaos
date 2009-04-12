#include "video.h" 
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"

void kmain(void* mbd,unsigned int magic)
{
	console_cls();
	console_puts("MivaOS (kernel 0.0.1) Loading...\n");
	gdt_install(); // setup gdt
	idt_install(); // setup idt
	isrs_install(); // setup isrs
	irq_install(); // setup irq
	timer_install(100); // setup our timer..

	// allows us to use our IRQs
	__asm__ __volatile__ ("sti"); 

	DWORD start = GetTickCount();
	while (1) 
	{
		int x = 500 / 0;
	}
} 

