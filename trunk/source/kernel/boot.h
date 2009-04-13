/*
Our boot structures
*/
#ifndef _BOOT_H
#define __BOOT_H
#include "types.h"

//our multiboot magic number:
#define BOOT_MAGIC 0x1BADB002
#define BOOT_FLAGS 0x00000003
#define BOOTLOADER_MAGIC 0x2BADB002
#define STACK_SIZE 0x4000

struct ELF_HEADER
{
	DWORD num;
	DWORD size;
	DWORD address;
	DWORD shndx;
};

struct MULTIBOOT_INFO
{
	DWORD flags;
	DWORD lowmem;
	DWORD highmem;
	DWORD bootDevice;
	DWORD commandLine;
	DWORD modules;
	DWORD modulesAddress;
	struct ELF_HEADER elf;
	DWORD mapLength;
	DWORD mapAddress;
};

//! Initializes the boot data by maybe a copy of the data and putting it in the global multiboot header
void InitBootData(LPVOID mhd);

//! Get boot info (returns by pointer).
void GetBootInfo(struct MULTIBOOT_INFO *pOutData);

#endif
