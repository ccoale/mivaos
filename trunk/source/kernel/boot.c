/*
** Provides functions for retrieving boot information
**
*/
#include "boot.h"
#include "memory.h"

// The multiboot header...
struct MULTIBOOT_INFO g_nBootHeader;

//! Initializes the boot data by maybe a copy of the data and putting it in the global multiboot header
void InitBootData(LPVOID mhd)
{
	_memcpy((LPVOID)&g_nBootHeader, mhd, sizeof(struct MULTIBOOT_INFO));
}

//! Get boot info (returns by pointer).
void GetBootInfo(struct MULTIBOOT_INFO *pOutData)
{
	_memcpy((LPVOID)pOutData, (LPVOID)&g_nBootHeader, sizeof(struct MULTIBOOT_INFO));
}
