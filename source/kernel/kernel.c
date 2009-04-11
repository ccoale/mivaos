#include "video.h" 
#include "gdt.h"
void kmain(void* mbd,unsigned int magic) 
{ 
	gdt_install();
cls(); 
unsigned char*videoram=(unsigned char*)0xb8000; 
videoram[0]=makeDefChar('a');
videoram[1]=0x07; 
} 

