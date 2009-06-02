/*
** Provides a physical memory manager
**
*/
#ifndef _INC_MM_H
#define _INC_MM_H
#include "types.h"

/*
For most efficiency, the memory manager will only store a BITMAP of
used memory BLOCKS. Each bit represents a block of memory, if the bit
is 0, the block is free for use. If it is 1, it is currently in use.

With this method, we only have 1 byte of overhead per 32,768 bytes of 
memory. It is up to the memory pager/kernel how to work with these
blocks.
*/

//! The number of blocks per byte (DO NOT CHANGE!)
#define MEMMGR_BLOCKS_PER_BYTE		8

//! The number of bytes in 1 block (changeable, but recommended to stay the same for paging)
#define MEMMGR_BLOCK_SIZE		4096 // 4KB

//! Memory block data alignment (DO NOT CHANGE!!)
#define MEMMGR_BLOCK_ALIGN		MEMMGR_BLOCK_SIZE

//! IN USE status for a memory block
#define MEMMGR_STATUS_INUSE		1

//! FREE status for a memory block
#define MEMMGR_STATUS_FREE		0

//! Out of blocks error
#define MEMMGR_ERROR_OUTOFBLOCKS	((DWORD)-1)

//! Structure format of a MEMORY_REGION
struct MEMORY_REGION
{
	DWORD	dwStartLo;
	DWORD	dwStartHi;
	DWORD	dwSizeLo;
	DWORD	dwSizeHi;
	DWORD	dwType;
	DWORD	dwACPI_3_0;
};

//! Memory Type strings
extern char* GSTR_MEMORY_TYPES[];

//! Initializes the memory manager. 
//! size - the number of bytes of memory we have to work with
//! bitmap - a pointer to the location of the bitmap. THIS LOCATION MUST NOT BE CHANGED!
void MemMgrInit(DWORD size, LPVOID bitmap);

//! Sets the status of a single memory block.
void MemMgrSetBlockStatus(DWORD block, DWORD status);

//! Gets the status of a single memory block.
DWORD MemMgrGetBlockStatus(DWORD block);

//! Gets the next first free memory block. If we have no more memory blocks, return -1.
DWORD MemMgrGetFreeBlock();

//! Gets the number of free blocks in memory.
DWORD MemMgrGetFreeBlockCount();

//! Gets the number of memory blocks this system supports.
DWORD MemMgrGetBlockCount();

//! Initializes a region of memory in blocks and makes it ready for use. This should be the first thing the kernel calls.
void MemMgrCreateRegion(LPVOID base, DWORD length);

//! Uninitializes a region of memory in blocks.
void MemMgrDeleteRegion(LPVOID base, DWORD length);

//! Allocates the next block of memory and returns a pointer to it
LPVOID MemMgrAllocBlock();

//! Frees an allocated block
void MemMgrFreeBlock(LPVOID mem);

//! Finds the next block of memory based on the number of blocks
DWORD MemMgrGetFreeBlockSize(DWORD sz);

//! Allocates multiple blocks of memory
LPVOID MemMgrAllocBlocks(DWORD ct);

//! Frees multiple blocks of memory
void MemMgrFreeBlocks(LPVOID p, DWORD ct);

//! Enables paging
void MemMgrEnablePaging();

//! Disables paging
void MemMgrDisablePaging();

//! Gets whether or not paging is enabled
BOOL MemMgrIsPaging();

//! Loads the Page Directory Base Register
void MemMgrLoadPDBR(LPVOID base_addr);

//! Gets the Page Directory Base Register
LPVOID MemMgrGetPDBR();



#endif /* _INC_MM_H */
