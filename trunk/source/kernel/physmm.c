#include "physmm.h"
#include "memory.h"

//! The size, in bytes, of the memory we are managing.
static DWORD _PhysMemSize 	= 0;

//! The number of blocks that are currently used.
static DWORD _PhysMemUsedBlocks = 0;

//! The maximum number of blocks we have to work with.
static DWORD _PhysMemMaxBlocks 	= 0;

//! The pointer to the stack that stores our memory addresses.
static DWORD* _PhysMemStack 	= 0;

//! The current stack index.
static DWORD _PhysMemStackIndex = 0;

//! Initializes the physical memory manager.
//! 'size' is the size in bytes of the memory area to manage.
//! 'stack' is a pointer to the area of memory that stores the memory stack.
void PhysMemInit(DWORD size, LPVOID stack)
{
	DWORD addr		= 16384; // skip the first 16MB
	_PhysMemSize 		= size;
	_PhysMemMaxBlocks 	= size / PHYSMEM_BLOCK_SIZE;
	_PhysMemStack 		= (DWORD *)stack;
	_PhysMemUsedBlocks 	= 0;
	_PhysMemStackIndex	= 0;

	// push each 4KB address to the stack
	for (; _PhysMemStackIndex < _PhysMemMaxBlocks; _PhysMemStackIndex++, addr+=PHYSMEM_BLOCK_SIZE)
	{
		_PhysMemStack[_PhysMemStackIndex] = addr;
	}
}

//! Gets the stack pointer.
LPVOID PhysMemGetStack()
{
	return (LPVOID)_PhysMemStack;
}

//! Gets the size of the managed memory area. (can't be set)
DWORD PhysMemGetSize()
{
	return _PhysMemSize;
}

//! Gets the number of available blocks.
DWORD PhysMemGetFreeBlocks()
{
	return _PhysMemMaxBlocks - _PhysMemUsedBlocks;
}

//! Gets the number of used blocks.
DWORD PhysMemGetUsedBlocks()
{
	return _PhysMemUsedBlocks;
}

//! Gets the maximum number of blocks (regardless of state).
DWORD PhysMemGetTotalBlocks()
{
	return _PhysMemMaxBlocks;
}

//! Allocates a single block of memory and returns its address.
LPVOID PhysMemAllocBlock()
{
	// Make sure we aren't out of memory
	if (_PhysMemStackIndex < 0)
		return 0;

	_PhysMemUsedBlocks++;

	// Otherwise, we can pop the next value from the stack
	return (LPVOID)_PhysMemStack[_PhysMemStackIndex--];
}

//! Frees an allocated block of memory.
void PhysMemFreeBlock(LPVOID mem)
{
	// Make sure it is a valid address (must be block-aligned)
	if ( (((DWORD)mem) % PHYSMEM_BLOCK_SIZE) != 0)
		return; // can't free a bad memory address

	// Make sure that we have memory to push
	if (_PhysMemStackIndex >= _PhysMemMaxBlocks)
		return; // no more memory (all of it is free)

	_PhysMemUsedBlocks--;
	// Otherwise, push it back onto the stack
	_PhysMemStack[_PhysMemStackIndex++] = (DWORD)mem;
}
