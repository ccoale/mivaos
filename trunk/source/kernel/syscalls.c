/*
** Provides definitions for system calls
**
*/
#include "syscalls.h"
#include "idt.h"
#include "types.h"
#include "video.h"
#include "boot.h"
#include "timer.h"

#define SYSCALL_MAX 16
// system call list
LPVOID g_pSysCallProcs[SYSCALL_MAX] = { 0 };

//! Installs a system call routine
void SystemCallInstall(DWORD code, LPVOID proc)
{
	g_pSysCallProcs[code] = proc;
}

//! Handles sytem calls
void SystemCallHandler(struct regs *r)
{
	if ((r->eax < 0) || (r->eax >= SYSCALL_MAX))
		return;

	// get system call procedure address
	void (*tmp)(struct regs *r) = g_pSysCallProcs[r->eax];
	
	// call it
	if (tmp != NULL) tmp(r);
}

//! Setup system calls
void SetupSystemCalls()
{
	ConsolePuts("Loading system calls...");
	SystemCallInstall(0x00000000, SysCall_DebugMessage);
	SystemCallInstall(0x00000001, SysCall_ConsolePutch);
	SystemCallInstall(0x00000002, SysCall_ConsolePuts);
	SystemCallInstall(0x00000003, SysCall_GetBootHeader);
	SystemCallInstall(0x00000004, SysCall_TimerGetTime);
	SystemCallInstall(0x00000005, SysCall_TimerGetTicks);
	ConsolePuts(" success!\n");
}

// -- System call list --
void SysCall_DebugMessage(struct regs *r)
{
	// we want to output all the debug information we currently have... (this includes getting our boot info)
	struct MULTIBOOT_INFO info;
	GetBootInfo(&info);

	kprintf("Memory lower: %d KB, memory upper %d KB\n", info.mem_lower, info.mem_upper);
	kprintf("Registered system calls: ");
	int i = 0;
	for (; i < SYSCALL_MAX; i++) {
		if (g_pSysCallProcs[i] == NULL) break;
		kprintf(" 0x%x[0x%x] ", i, (DWORD)g_pSysCallProcs[i]);
	}
}

void SysCall_ConsolePutch(struct regs *r)
{
	// the character is stored in r->ebx.
	ConsolePutch((char)r->ebx);
}

void SysCall_ConsolePuts(struct regs *r)
{
	// the string pointer is in r->ebx
	ConsolePuts((const char *)r->ebx);
}

void SysCall_GetBootHeader(struct regs *r)
{
	// the address to copy data to is in r->ebx.
	GetBootInfo((LPVOID)r->ebx);
}

void SysCall_TimerGetTime(struct regs *r)
{
	// the address to copy data to is in r->ebx.
	TimerGetTime((LPVOID)r->ebx);
}

void SysCall_TimerGetTicks(struct regs *r)
{
	// return the tick count in eax
	r->eax = TimerGetTicks();
}
