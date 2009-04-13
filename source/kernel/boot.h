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
struct multiBootHeader
{
DWORD magic;
DWORD flags;
DWORD checksum;
DWORD headAddress;
DWORD loadAddress;
DWORD loadEndAddress;
DWORD bssEndAddress;
DWORD entryAddress;
};

struct elfHeader
{
DWORD num;
DWORD size;
DWORD address;
DWORD shndx;
};

struct multiBootInfo
{
DWORD flags;
DWORD lowmem;
DWORD highmem;
DWORD bootDevice;
DWORD commandLine;
DWORD modules;
DWORD modulesAddress;
struct elfHeader elf;
DWORD mapLength;
DWORD mapAddress;
};
#endif