/*
Main memory functions
Contains functions for manipulating blocks of memory
*/
#include "memory.h"
void* memSet(void* dest,BYTE val,size_t len)
{
BYTE* ptr=(BYTE*)dest;
for (;len!=0;len--)
{
*ptr++=val;
}
return dest;
}

void* memZero(void* dest,size_t len)
{
return (memSet(dest,NULL,len));
}
