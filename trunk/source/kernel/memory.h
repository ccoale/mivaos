#ifndef __MEMORY_H
#define __MEMORY_H
#include "types.h"
/*
Basic memory functions
*/
//memSet
//Will set a specified length of memory to the value specified, starting at the specified address
void* memSet(void* dest,BYTE val,size_t len);
//memZero
//uses memSet to write NULL (0x00) values to the specified block of memory
void* memZero(void* dest, size_t len);
#endif

