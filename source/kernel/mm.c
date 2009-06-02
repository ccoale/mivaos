/*
** Provides definitions for the memory management prototypes.
**
*/
#include "mm.h"
#include "memory.h"
#include "types.h"

static DWORD _memmgr_memsize = 0;
static DWORD _memmgr_usedblocks = 0;
static DWORD _memmgr_maxblocks = 0;
static DWORD* _memmgr_memmap = 0;

// Friendly names for memory types
//! different memory regions (in memory_region.type)
char* GSTR_MEMORY_TYPES[] = {

	"Available",			//memory_region.type==0
	"Reserved",			//memory_region.type==1
	"ACPI Reclaim",			//memory_region.type==2
	"ACPI NVS Memory"		//memory_region.type==3
};

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

//! Finds the next block of memory based on the size
DWORD MemMgrGetFreeBlockSize(DWORD size)
{
	if (size==0) return MEMMGR_ERROR_OUTOFBLOCKS;
	if (size==1) return MemMgrGetFreeBlock(); // only 1 block requested
	DWORD count = MemMgrGetFreeBlockCount();
	DWORD i;
	for (i = 0; i < count; i++) 
	{
		if (_memmgr_memmap[i] != 0xffffffff)
		{
			int j;
			for (j=0; j<32; j++) 
			{	
				// test each bit in the dword
				int bit = 1 << j;
				if (! (_memmgr_memmap[i] & bit) ) 
				{
					int startingBit = i * 32;
					startingBit += bit; //get the free bit in the dword at index i

					DWORD free = 0; //loop through each bit to see if its enough space
					DWORD c;
					for (c = 0; c <= size; c++) 
					{
						if (! MemMgrGetBlockStatus(startingBit+count) )
							free++;	// this bit is clear (free frame)

						if (free == size)
							return i*4*8+j; //free count==size needed; return index
					}
				}
			}
		}
	}

	return MEMMGR_ERROR_OUTOFBLOCKS;
}

//! Allocates multiple blocks of memory
LPVOID MemMgrAllocBlocks(DWORD ct)
{
	if (MemMgrGetFreeBlockCount() <= 0)
		return NULL; // out of memory

	DWORD frame = MemMgrGetFreeBlockSize(ct);
	if (frame == MEMMGR_ERROR_OUTOFBLOCKS)
		return NULL;

	// set each block
	DWORD i;
	for (i = 0; i < ct; i++)
		MemMgrSetBlockStatus(frame + i, MEMMGR_STATUS_INUSE);

	// now we need to return the physical address
	DWORD addr = frame * MEMMGR_BLOCK_SIZE;
	_memmgr_usedblocks += ct;

	return (LPVOID)addr;
}

//! Frees multiple blocks of memory
void MemMgrFreeBlocks(LPVOID p, DWORD ct)
{
	DWORD addr = (DWORD)p;
	int frame = addr / MEMMGR_BLOCK_SIZE;

	DWORD i;
	for (i = 0; i < ct; i++) MemMgrSetBlockStatus(frame + i, MEMMGR_STATUS_FREE);

	_memmgr_usedblocks -= ct;
}

//! Enables paging
void MemMgrEnablePaging()
{
	__asm__ __volatile__ ("movl %cr0, %eax;");
	__asm__ __volatile__ ("or $0x80000000, %eax;"); // set bit 31
	__asm__ __volatile__ ("movl %eax, %cr0;");
}

//! Disables paging
void MemMgrDisablePaging()
{
	__asm__ __volatile__ ("movl %cr0, %eax;");
	__asm__ __volatile__ ("and $0x7FFFFFFF, %eax;"); // clear bit 31
	__asm__ __volatile__ ("movl %eax, %cr0;");
}

//! Gets whether or not paging is enabled
BOOL MemMgrIsPaging()
{
	DWORD res = 0;
	__asm__ __volatile__ ("movl %cr0, %eax;");
	__asm__ __volatile__ ("movl %%eax, %0;" : "=r"(res));

	return (res & 0x80000000) ? FALSE : TRUE;
}

//! Loads the Page Directory Base Register
void MemMgrLoadPDBR(LPVOID base_addr)
{
	DWORD addr = (DWORD)base_addr;
	__asm__ __volatile__ ("movl %0, %%eax;" : "=r"(addr));
	__asm__ __volatile__ ("movl %eax, %cr0;");
}

//! Gets the Page Directory Base Register
LPVOID MemMgrGetPDBR()
{
	DWORD ret = 0;
	__asm__ __volatile__ ("movl %cr0, %eax;");
	__asm__ __volatile__ ("movl %%eax, %0;" : "=r"(ret));

	return (LPVOID)ret;
}

