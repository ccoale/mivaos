/*
** Paging
**
*/
#include "paging.h"

//! page table represents 4mb address space
#define PTABLE_ADDR_SPACE_SIZE 0x400000

//! directory table represents 4gb address space
#define DTABLE_ADDR_SPACE_SIZE 0x10000000 //0 

//! page sizes are 4k
#define PAGE_SIZE 4096

//! current directory table
struct PAGE_DIRECTORY*		_cur_directory = 0;

//! current page directory base register
LPVOID			_cur_pdbr = 0;

void PtEntryAddAttrib (PT_ENTRY* e, DWORD attrib) { *e |= attrib; }
void PtEntryDelAttrib (PT_ENTRY* e, DWORD attrib) { *e &= ~attrib; }
void PtEntrySetFrame (PT_ENTRY* e, LPVOID addr) { *e = (*e & ~PTE_FRAME) | (DWORD)addr; }
BOOL PtEntryIsPresent (PT_ENTRY e) { return e & PTE_PRESENT; }
BOOL PtEntryIsWritable (PT_ENTRY e) { return e & PTE_WRITABLE; }
LPVOID PtEntryPfn (PT_ENTRY e) { return (LPVOID)(DWORD)(e & PTE_FRAME); }
void PdEntryAddAttrib (PD_ENTRY* e, DWORD attrib) { *e |= attrib; }
void PdEntryDelAttrib (PD_ENTRY* e, DWORD attrib) { *e &= ~attrib; }
void PdEntrySetFrame (PD_ENTRY* e, LPVOID addr) { *e = (*e & ~PDE_FRAME) | (DWORD)addr; }
BOOL PdEntryIsPresent (PD_ENTRY e) {	return e & PDE_PRESENT; }
BOOL PdEntryIsWritable (PD_ENTRY e) { return e & PDE_WRITABLE; }
LPVOID PdEntryPfn (PD_ENTRY e) { return (LPVOID)(e & PDE_FRAME); }
BOOL PdEntryIsUser (PD_ENTRY e) { return e & PDE_USER; }
BOOL PdEntryIs4mb (PD_ENTRY e) { return e & PDE_4MB; }
void PdEntryEnableGlobal (PD_ENTRY e) { }

//! initialize the memory manager
void VirtMemMgrInitialize ()
{
	//! allocate default page table
	struct PAGE_TABLE* table = (struct PAGE_TABLE*) MemMgrAllocBlock();
	if (!table) return;

	//! clear page table
	VirtMemMgrTableClear (table);

	//! idenitity map the page table (First 4mb of virtual memory mapped to same phys address)
	int i = 0;
	int frame = 0;
	for (; i < 1024; i++, frame+=4096) 
	{
		//! create a new page
		PT_ENTRY page=0;
		PtEntryAddAttrib (&page, PTE_PRESENT);
		PtEntrySetFrame (&page, (LPVOID)frame);

		//! ...and add it to the page table
		table->entries [VirtMemMgrTableVirtToIndex ((LPVOID)frame) ] = (DWORD)page;
	}

	//! create default directory table
	struct PAGE_DIRECTORY*	dir = (struct PAGE_DIRECTORY*) MemMgrAllocBlocks (3);
	if (!dir) return;

	//! clear directory table and set it as current
	VirtMemMgrDirectoryClear (dir);

	//! get first entry in dir table and set it up to point to our table
	PD_ENTRY* entry = VirtMemMgrDirectoryLookupEntry (dir,0);
	PdEntryAddAttrib (entry, PDE_PRESENT);
	PdEntryAddAttrib (entry, PDE_WRITABLE);
	PdEntrySetFrame (entry, (LPVOID)table);

	//! store current PDBR
	_cur_pdbr = (LPVOID) &dir->entries;

	//! switch to our page directory
	VirtMemMgrSwitchDirectory (dir);

	//! enable paging
	MemMgrEnablePaging(TRUE);
}

//! allocates a page in physical memory
BOOL VirtMemMgrAllocPage (PT_ENTRY *e)
{
	//! allocate a free physical frame
	void* p = MemMgrAllocBlock();
	if (!p)
		return FALSE;

	//! map it to the page
	PtEntrySetFrame (e, (LPVOID)p);
	PtEntryAddAttrib (e, PTE_PRESENT);

	return TRUE;
}

//! frees a page in physical memory
void VirtMemMgrFreePage (PT_ENTRY* e)
{
	void* p = (void*)PtEntryPfn (*e);
	if (p)
		MemMgrFreeBlock(p);

	PtEntryDelAttrib (e, PTE_PRESENT);
}

//! switch to a new page directory
BOOL VirtMemMgrSwitchDirectory (struct PAGE_DIRECTORY* dir)
{
	if (!dir)
		return FALSE;

	_cur_directory = dir;
	MemMgrLoadPDBR (_cur_pdbr);

	return TRUE;
}

//! get current page directory
struct PAGE_DIRECTORY* VirtMemMgrGetDirectory ()
{
	return _cur_directory;
}

//! flushes a cached translation lookaside buffer (TLB) entry
void VirtMemMgrFlushTLBEntry (LPVOID addr)
{
	__asm__ __volatile__ ("cli");
	__asm__ __volatile__ ("invlpg %0" :: "m"((DWORD)addr));
	__asm__ __volatile__ ("sti");
}

//! clears a page table
void VirtMemMgrTableClear (struct PAGE_TABLE* p)
{
	if (p)
		_memset (p, 0, sizeof (struct PAGE_TABLE) );
}

//! convert virtual address to page table index
DWORD VirtMemMgrTableVirtToIndex (LPVOID addr)
{
	return ((DWORD)addr >= (DWORD)PTABLE_ADDR_SPACE_SIZE) ? 0 : (DWORD)addr / PAGE_SIZE;
}

//! get page entry from page table
PT_ENTRY* VirtMemMgrTableLookupEntry (struct PAGE_TABLE* p, LPVOID addr)
{
	if (p)
		return &p->entries[ VirtMemMgrTableVirtToIndex (addr) ];

	return 0;
}

//! convert virtual address to page directory index
DWORD VirtMemMgrDirectoryVirtToIndex (LPVOID addr)
{
	return ((DWORD)addr >= (DWORD)DTABLE_ADDR_SPACE_SIZE) ? 0 : (DWORD)addr / PAGE_SIZE;
}

//! clears a page directory table
void VirtMemMgrDirectoryClear (struct PAGE_DIRECTORY* dir)
{
	if (dir)
		_memset (dir, 0, sizeof (struct PAGE_DIRECTORY) );
}

//! get directory entry from directory table
PD_ENTRY* VirtMemMgrDirectoryLookupEntry (struct PAGE_DIRECTORY* p, LPVOID addr)
{
	if (p)
		return &p->entries[ VirtMemMgrTableVirtToIndex (addr) ];

	return 0;
}
