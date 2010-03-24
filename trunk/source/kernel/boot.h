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
	DWORD flags; // required
	DWORD memoryLo; // memory size, flags[0]
	DWORD memoryHi;
	DWORD bootDevice; // boot device, flags[1]
	DWORD cmdLine; // kernel command line, flags[2]
	DWORD modCount; // number of modules loaded, flags[3]
	DWORD modAddr;
	DWORD sym[3]; // symbol table info, flags[4]/flags[5]
	DWORD memMapLength; // memory map, flags[6]
	DWORD memMapAddr;
// 	DWORD drivesLength; // drives, flags[7]
//	DWORD drivesAddr;
//	DWORD configTable; // ROM configuration table, flags[8]
//	DWORD bootLoaderName; // boot loader name, flags[9]
//	DWORD apmTable; // advanced power management table, flags[10]
//	DWORD vbeControlInfo; // video bios extension, flags[11]
//	DWORD vbeModeInfo;
//	WORD vbeMode;
//	WORD vbeInterfaceSeg;
//	WORD vbeInterfaceOff;
//	WORD vbeInterfaceLen;
};
typedef struct mmap
{
DWORD size;
DWORD base_l;
DWORD base_h;
DWORD length_l;
DWORD length_h;
DWORD type;
} mmap_t;

//! Initializes the boot data by maybe a copy of the data and putting it in the global multiboot header
void InitBootData(LPVOID mhd);

//! Get boot info (returns by pointer).
void GetBootInfo(struct MULTIBOOT_INFO *pOutData);

#endif
