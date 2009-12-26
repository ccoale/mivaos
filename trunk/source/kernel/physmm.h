/*
	This header declares constants, function prototypes, data structures, etc.
	for the use of the Physical Memory Manager.

	The Physical Memory Manager allows the efficient allocation/deallocation of Memory Blocks.
	Memory Blocks are 4KB.
	When the Physical Memory Manager is initialized, the entire RAM is partitioned into 4KB chunks.
	All of these chunks are set to 'used' until we grab memory region information from the BIOS.

	This Physical memory Manager uses a stack-based approach at managing memory.
	When the memory manager is initialized, it pushes all 4KB memory blocks onto the memory stack.
	When a block needs to be allocated/used, it is popped from the stack.
	When a block is deallocated/freed, it is pushed back onto the stack.
*/
#ifndef _PHYSMM_H
#define _PHYSMM_H
#include "types.h"

//! The size of each physical memory block.
#define PHYSMEM_BLOCK_SIZE	4096

//! An error (usually, out of blocks).
#define PHYSMEM_ERROR		(DWORD)0xFFFFFFFF

//! Initializes the physical memory manager.
//! 'size' is the size in bytes of the memory area to manage.
//! 'stack' is a pointer to the area of memory that stores the memory stack.
void PhysMemInit(DWORD size, LPVOID stack);

//! Gets the stack pointer.
LPVOID PhysMemGetStack();

//! Gets the size of the managed memory area. (can't be set)
DWORD PhysMemGetSize();

//! Gets the number of available blocks.
DWORD PhysMemGetFreeBlocks();

//! Gets the number of used blocks.
DWORD PhysMemGetUsedBlocks();

//! Gets the maximum number of blocks (regardless of state).
DWORD PhysMemGetTotalBlocks();

//! Allocates a single block of memory and returns its address.
LPVOID PhysMemAllocBlock();

//! Frees an allocated block of memory.
void PhysMemFreeBlock(LPVOID mem);

#endif /* _PHYSMM_H */
