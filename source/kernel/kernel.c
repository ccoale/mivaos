#include "video.h" 
void kmain(void* mbd,unsigned int magic) 
{ 
cls(); 
unsigned char*videoram=(unsigned char*)0xb8000; 
videoram[0]=makeDefChar('a');
videoram[1]=0x07; 
} 

