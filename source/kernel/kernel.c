#include "video.h" 
#include "gdt.h"
void kmain(void* mbd,unsigned int magic) 
{ 
	gdt_install();
idt_install();
	console_cls(); // clear the console..
	console_puts("Hello World!");
} 

