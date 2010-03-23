/*
Basic memory functions
used for manipulating blocks of memory
*/

#ifndef __MEMORY_H
#define __MEMORY_H
#include "types.h"

void *_memcpy(void *dest, const void *src, size_t count);
void *_memset(void *dest, char val, size_t count);
unsigned short *_memsetw(unsigned short *dest, unsigned short val, size_t count);
void *_zeromem(void *dest, size_t count);
size_t _strlen(const char *str);
UINT _kmalloc(UINT size);
UINT _kmalloc_a(UINT size);
UINT _kmalloc_p(UINT size, BOOL align, UINT* phys);
unsigned char _inportb (unsigned short _port);
void _outportb (unsigned short _port, unsigned char _data);

#endif

