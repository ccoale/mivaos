/*
** Provides definitions for the memory management prototypes.
**
*/
#include "mm.h"
#include "memory.h"

static DWORD _memmgr_memsize = 0;
static DWORD _memmgr_usedblocks = 0;
static DWORD _memmgr_maxblocks = 0;
static DWORD* _memmgr_memmap = 0;

//! Initializes the memory manager. 
//! size - the number of bytes of memory we have to work with
//! bitmap - a pointer to the location of the bitmap. THIS LOCATION MUST NOT BE CHANGED!
void MemMgrInit(DWORD size, LPVOID bitmap)
{
	_memmgr_memsize = size;
	_memmgr_memmap = (DWORD *)bitmap;
	_memmgr_maxblocks = (size * 1024) / MEMMGR_BLOCK_SIZE;
	_memmgr_usedblocks = _memmgr_maxblocks;
	
	_memset((LPVOID)_memmgr_memmap, 0xF, _memmgr_maxblocks / MEMMGR_BLOCKS_PER_BYTE);
}

//! Sets the status of a single memory block.
void MemMgrSetBlockStatus(DWORD block, DWORD status)
{
	DWORD _stat = MemMgrGetBlockStatus(block);
	if (_stat == status) return; // we already have this status set...

	if (status == MEMMGR_STATUS_INUSE)
		_memmgr_memmap[(DWORD)(block / 32)] |= (1 << (block % 32));
	else if (status == MEMMGR_STATUS_FREE)
		_memmgr_memmap[(DWORD)(block / 32)] &= ~(1 << (block % 32));

	return;
}

//! Gets the status of a single memory block.
DWORD MemMgrGetBlockStatus(DWORD block)
{
	return (DWORD)(_memmgr_memmap[(DWORD)(block / 32)]);
}

//! Gets the next first free memory block. If we have no more memory blocks, return MEMMGR_ERROR_OUTOFBLOCKS.
DWORD MemMgrGetFreeBlock()
{
	DWORD i = 0;
	DWORD _blocks = MemMgrGetBlockCount();
	for (; i < (_blocks / 32); i++) {
		if (_memmgr_memmap[i] != 0xFFFFFFFF) {
			DWORD j = 0;
			for (; j < 32; j++) {
				DWORD bit = 1 << j;
				if (! (_memmgr_memmap[i] & bit))
					return i * 4 * 8 * j;
			}
		}
	}

	return MEMMGR_ERROR_OUTOFBLOCKS;
}

//! Gets the number of free blocks in memory.
DWORD MemMgrGetFreeBlockCount()
{
	return _memmgr_maxblocks - _memmgr_usedblocks;
}

//! Gets the number of memory blocks this system supports.
DWORD MemMgrGetBlockCount()
{
	return _memmgr_maxblocks;
}

//! Initializes a region of memory in blocks. This should be the first thing the kernel calls.
void MemMgrCreateRegion(LPVOID base, DWORD length)
{
	DWORD align = (DWORD)((DWORD)base / MEMMGR_BLOCK_SIZE);
	DWORD blocks = (DWORD)(length / MEMMGR_BLOCK_SIZE);

	for (; blocks > 0; blocks--) {
		MemMgrSetBlockStatus(align++, MEMMGR_STATUS_FREE);
		_memmgr_usedblocks--;
	}

	// never let the first block become deleted!
	MemMgrSetBlockStatus(0, MEMMGR_STATUS_INUSE);
}

//! Uninitializes a region of memory in blocks.
void MemMgrDeleteRegion(LPVOID base, DWORD length)
{
	DWORD align = (DWORD)((DWORD)base / MEMMGR_BLOCK_SIZE);
	DWORD blocks = (DWORD)(length / MEMMGR_BLOCK_SIZE);

	for (; blocks > 0; blocks--) {
		MemMgrSetBlockStatus(align++, MEMMGR_STATUS_INUSE);
		_memmgr_usedblocks++;
	}
}

//! Allocates the next block of memory and returns a pointer to it
LPVOID MemMgrAllocBlock()
{
	if (MemMgrGetFreeBlockCount() <= 0)
		return NULL; // out of memory
	
	DWORD frame = MemMgrGetFreeBlock();
	if (frame == MEMMGR_ERROR_OUTOFBLOCKS)
		return NULL; //out of memory

	MemMgrSetBlockStatus(frame, MEMMGR_STATUS_INUSE);
	DWORD paddr = frame * MEMMGR_BLOCK_SIZE;
	_memmgr_usedblocks++;
	
	return (LPVOID)paddr;
}

//! Frees an allocated block
void MemMgrFreeBlock(LPVOID mem)
{
	DWORD addr = (DWORD)mem;
	DWORD frame = (DWORD)(addr / MEMMGR_BLOCK_SIZE);
	
	MemMgrSetBlockStatus(frame, MEMMGR_STATUS_FREE);
	_memmgr_usedblocks--;
}

