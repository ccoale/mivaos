/*
** Provides an implementation of memory paging and virtual memory
**
*/
#ifndef _INC_PAGING_H
#define _INC_PAGING_H
#include "mm.h"

// Page Table Entry flags
#define PTE_PRESENT		1		//
#define PTE_WRITABLE		2		//
#define PTE_USER		4		//
#define PTE_WRITETHOUGH		8,		//
#define PTE_NOT_CACHEABLE	0x10		//
#define PTE_ACCESSED		0x20		//
#define PTE_DIRTY		0x40		//
#define PTE_PAT			0x80		//
#define PTE_CPU_GLOBAL		100		//
#define PTE_LV4_GLOBAL		200		//
#define PTE_FRAME		0x7FFFF000 	//

// Page Directory Entry flags
#define PDE_PRESENT		0x01
#define PDE_WRITABLE		0x02
#define PDE_USER		0x04
#define PDE_PWT			0x08
#define PDE_PCD			0x10
#define PDE_ACCESSED		0x20
#define PDE_DIRTY		0x40
#define PDE_4MB			0x80
#define PDE_CPU_GLOBAL		0x100
#define PDE_LV4_GLOBAL		0x200
#define PDE_FRAME		0x7FFFF000

// Constants
#define PAGES_PER_TABLE		1024
#define PAGES_PER_DIR		1024

// Represents a page table entry
typedef DWORD PT_ENTRY;
typedef DWORD PD_ENTRY;

//! sets a flag in the page table entry
void PtEntryAddAttrib (PT_ENTRY* e, DWORD attrib);

//! clears a flag in the page table entry
void PtEntryDelAttrib (PT_ENTRY* e, DWORD attrib);

//! sets a frame to page table entry
void PtEntrySetFrame (PT_ENTRY*, LPVOID);

//! test if page is present
BOOL PtEntryIsPresent (PT_ENTRY e);

//! test if page is writable
BOOL PtEntryIsWritable (PT_ENTRY e);

//! get page table entry frame address
LPVOID PtEntryPfn (PT_ENTRY e);


//! sets a flag in the page table entry
void PdEntryAddAttrib (PD_ENTRY* e, DWORD attrib);

//! clears a flag in the page table entry
void PdEntryDelAttrib (PD_ENTRY* e, DWORD attrib);

//! sets a frame to page table entry
void PdEntrySetFrame (PD_ENTRY*, LPVOID);

//! test if page is present
BOOL PdEntryIsPresent (PD_ENTRY e);

//! test if directory is user mode
BOOL PdEntryIsUser (PD_ENTRY);

//! test if directory contains 4mb pages
BOOL PdEntryIs4mb (PD_ENTRY);

//! test if page is writable
BOOL PdEntryIsWritable (PD_ENTRY e);

//! get page table entry frame address
LPVOID PdEntryPfn (PD_ENTRY e);

//! enable global pages
void PdEntryEnableGlobal (PD_ENTRY e);



//-- Structures
struct PAGE_TABLE
{
	PT_ENTRY entries[1024];
};

struct PAGE_DIRECTORY
{
	PD_ENTRY entries[1024];
};

//! initialize the memory manager
void VirtMemMgrInitialize ();

//! allocates a page in physical memory
BOOL VirtMemMgrAllocPage (PT_ENTRY *);

//! frees a page in physical memory
void VirtMemMgrFreePage (PT_ENTRY* e);

//! switch to a new page directory
BOOL VirtMemMgrSwitchDirectory(struct PAGE_DIRECTORY*);

//! get current page directory
struct PAGE_DIRECTORY* VirtMemMgrGetDirectory ();

//! flushes a cached translation lookaside buffer (TLB) entry
void VirtMemMgrFlushTLBEntry (LPVOID addr);

//! clears a page table
void VirtMemMgrTableClear (struct PAGE_TABLE* p);

//! convert virtual address to page table index
DWORD VirtMemMgrTableVirtToIndex (LPVOID addr);

//! get page entry from page table
PT_ENTRY* VirtMemMgrTableLookupEntry (struct PAGE_TABLE* p, LPVOID addr);

//! convert virtual address to page directory index
DWORD VirtMemMgrDirectoryVirtToIndex (LPVOID addr);

//! clears a page directory table
void VirtMemMgrDirectoryClear (struct PAGE_DIRECTORY* dir);

//! get directory entry from directory table
PD_ENTRY* VirtMemMgrDirectoryLookupEntry (struct PAGE_DIRECTORY* p, LPVOID addr);

#endif /* _INC_PAGING_H */
