/*
Main memory functions
Contains functions for manipulating blocks of memory
*/
#include "memory.h"
extern UINT kernelEnd;
UINT top=(UINT)&kernelEnd; //where we start allocating for kmalloc and friends

void *_memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *_memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *_memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

void *_zeromem(void *dest, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = 0;

}

size_t _strlen(const char *str)
{
	const char *end = str;
	while (*end != 0)
		end++;
	
	return (end - str + 1);
}

UINT _kmalloc(UINT size)
{
UINT start=top;
top+=size;
return start;
}
UINT _kmalloc_a(UINT size)
{
if (top&0xFFFFF000) //starting address isn't aligned
{
top&=0xFFFFF000;
top+=0x1000;
}
return _kmalloc(size);
}
UINT _kmalloc_p(UINT size, BOOL align, UINT* phys)
{
UINT temp=0;
if (align)
{
temp=_kmalloc_a(size);
}
else
{
temp=_kmalloc(size);
}
*phys=temp;
return temp;
}

unsigned char _inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void _outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
