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

struct MULTIBOOT_HEADER
{
	DWORD magic;
	DWORD flags;
	DWORD checksum;
	DWORD header_addr;
	DWORD load_addr;
	DWORD load_end_addr;
	DWORD bss_end_addr;
	DWORD entry_addr;
};

struct MULTIBOOT_INFO
{
	DWORD flags;
	DWORD mem_lower;
	DWORD mem_upper;
	DWORD boot_device;
	DWORD cmdline;
	DWORD mods_count;
	DWORD mods_addr;
	struct ELF_HEADER elf;
	DWORD map_length;
	DWORD map_addr;
	DWORD drives_length;
	DWORD drives_addr;
	DWORD config_table;
	DWORD boot_loader_name;
	DWORD apm_table;
	DWORD vbe_control_info;
	DWORD vbe_mode_info;
	USHORT vbe_mode;
	USHORT vbe_interface_seg;
	USHORT vbe_interface_off;
	USHORT vbe_interface_len;
	
};

//! Initializes the boot data by maybe a copy of the data and putting it in the global multiboot header
void InitBootData(LPVOID mhd);

//! Get boot info (returns by pointer).
void GetBootInfo(struct MULTIBOOT_INFO *pOutData);

#endif
