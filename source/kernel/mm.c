/*
** Memory Manager
** Provides functions for allocating and freeing memory.
*/
#include "mm.h"
#define MEM_BASE 0x1000

// pointer to base memory block
struct memory_block* top;
struct memory_block* bottom;

// Initializes the memory block
void InitMemory()
{
top=bottom=NULL;
}

//! Returns the first block in memory, whether it is used or not.
struct memory_block* GetFirstMemoryBlock()
{
	return top;
}

//! Returns the next block of memory based on the first memory block
//! Return value of NULL when no block is available or this is the last block.
struct memory_block* GetNextMemoryBlock(struct memory_block* blk)
{
	if (blk == NULL)
		return NULL;

	return blk->next;
}

//! Creates a new memory block
struct memory_block* CreateMemoryBlock(BYTE flags, UINT size, LPVOID base)
{
struct memory_block *block=(struct memory_block*)base;
block->flags=flags;
block->length=size;
}

//! Allocate the specified number of bytes, and returns a pointer to the newly allocated data.
LPVOID mmalloc(size_t size)
{
struct memory_block* block=NULL;
if (top==NULL)
{
top=CreateMemoryBlock(0,size,(LPVOID)MEM_BASE);
bottom=top;
return top;
}
block=CreateMemoryBlock(0,size,(LPVOID)(bottom+(sizeof(struct memory_block)+bottom->length)));
return block;
}

//! Frees an allocated memory block
void mmfree(LPVOID mem)
{
}
