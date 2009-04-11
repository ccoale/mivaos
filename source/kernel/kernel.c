#include "video.h" 
#include "gdt.h"
void kmain(void* mbd,unsigned int magic) 
{ 
	gdt_install();
	console_clear(); // clear the console..
	console_puts("Hello World!");
} 

