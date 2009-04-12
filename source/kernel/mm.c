/*
** Memory Manager
** Provides functions for allocating and freeing memory.
*/
#include "mm.h"

// pointer to base memory block
const memory_block *start_block = 0x1000;
memory_block *end_block = start_block;

// Initializes the memory block
void InitMemory()
{
	start_block->flags = MEMBLOCK_FREE;
	start_block->base_address = start_block + sizeof(memory_block);
	start_block->length = 0;
	start_block->next = end_block;
}

//! Returns the first block in memory, whether it is used or not.
memory_block* GetFirstMemoryBlock()
{
	return start_block;
}

//! Returns the next block of memory based on the first memory block
//! Return value of NULL when no block is available or this is the last block.
memory_block* GetNextMemoryBlock(memory_block* blk)
{
	if (blk == NULL)
		return NULL;

	return blk->next;
}

//! Creates a new memory block
memory_block* CreateMemoryBlock(BYTE flags, UINT size, LPVOID base)
{

}

//! Allocate the specified number of bytes, and returns a pointer to the newly allocated data.
LPVOID mmalloc(size_t size)
{
}

//! Frees an allocated memory block
void mmfree(LPVOID mem)
{
}
