/*
** Provides a memory management API for the kernel
**
*/
#ifndef __MEMORYM_H
#define __MEMORYM_H
#include "memory.h"
#include "types.h"

//! The memory block is reserved and cannot be allocated
#define MEMBLOCK_RESERVED	0x00

//! The memory block is currently in use, and cannot be allocated
#define MEMBLOCK_INUSE		0x01

//! The memory block is available to be allocated
#define MEMBLOCK_FREE		0x02

//! Memory block data structure
struct memory_block
{
	//! A pointer to the next memory block in the list.
	memory_block *next;

	//! Flags (such as whether or not the block is in use)
	BYTE flags;

	//! The starting address of the allocated memory
	LPVOID base_address;

	//! The length in bytes of the allocated memory
	size_t length;
} __attribute__ ((packed));

//! Allocate the specified number of bytes, and returns a pointer to the newly allocated data.
LPVOID mmalloc(size_t size);

//! Frees an allocated memory block
void mmfree(LPVOID mem);

#endif /* __MM_H */
