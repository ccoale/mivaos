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

//! Handles system calls
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
//	ConsolePuts("Loading system calls...");
	SystemCallInstall(SYSCALL_DEBUGMESSAGE, SysCall_DebugMessage);
	SystemCallInstall(SYSCALL_CONSOLEPUTCH, SysCall_ConsolePutch);
	SystemCallInstall(SYSCALL_CONSOLEPUTS, SysCall_ConsolePuts);
	SystemCallInstall(SYSCALL_GETBOOTHEADER, SysCall_GetBootHeader);
	SystemCallInstall(SYSCALL_TIMER_GETTIME, SysCall_TimerGetTime);
	SystemCallInstall(SYSCALL_TIMER_GETTICKS, SysCall_TimerGetTicks);
SystemCallInstall(SYSCALL_EXIT,SysCall_Nop);
SystemCallInstall(SYSCALL_CLOSE,SysCall_Nop);
SystemCallInstall(SYSCALL_EXECVE,SysCall_Nop);
SystemCallInstall(SYSCALL_FORK,SysCall_Nop);
SystemCallInstall(SYSCALL_FSTAT,SysCall_Nop);
SystemCallInstall(SYSCALL_GETPID,SysCall_Nop);
SystemCallInstall(SYSCALL_ISTTY,SysCall_Nop);
SystemCallInstall(SYSCALL_KILL,SysCall_Nop);
SystemCallInstall(SYSCALL_LINK,SysCall_Nop);
SystemCallInstall(SYSCALL_LSEEK,SysCall_Nop);
SystemCallInstall(SYSCALL_OPEN,SysCall_Nop);
SystemCallInstall(SYSCALL_READ,SysCall_Nop);
SystemCallInstall(SYSCALL_SBRK,SysCall_Nop);
SystemCallInstall(SYSCALL_STAT,SysCall_Nop);
SystemCallInstall(SYSCALL_TIMES,SysCall_Nop);
SystemCallInstall(SYSCALL_UNLINK,SysCall_Nop);
SystemCallInstall(SYSCALL_WAIT,SysCall_Nop);
SystemCallInstall(SYSCALL_WRITE,SysCall_Nop);
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

void SysCall_Nop(struct regs *r)
{
r->eax=0;
}
