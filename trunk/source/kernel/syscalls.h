/*
** Provides declaration for most (if not all) kernel-side system call handlers.
**
*/
#ifndef __SYSCALLS__H
#define __SYSCALLS__H
#include "memory.h"
#include "isrs.h"

/*
(for more information, see the syscalls.c)
------------------------------------------------------------------
code		- 	system call 	- 	description
------------------------------------------------------------------
0x00000000	-	DebugMessage	-	Outputs debug information to the console
0x00000001	-	ConsolePutch	- 	Outputs a character to the console
0x00000002	-	ConsolePuts	-	Outputs a null-terminated string to the console
0x00000003	-	GetBootHeader	-	Returns basic information about the computer pulled berfore loading the kernel
0x00000004	-	TimerGetTime	-	Returns the current date and time
0x00000005	-	TimerGetTicks	-	Returns the current timer tick count
*/

//! System Call Interrupt Number
#define SYSCALL_INT		0x80

//! System Call Codes
#define SYSCALL_DEBUGMESSAGE	0x00000000
#define SYSCALL_CONSOLEPUTCH	0x00000001
#define SYSCALL_CONSOLEPUTS	0x00000002
#define SYSCALL_GETBOOTHEADER	0x00000003
#define SYSCALL_TIMER_GETTIME 0x00000004
#define SYSCALL_TIMER_GETTICKS 0x00000005
#define SYSCALL_EXIT 0x00000006
#define SYSCALL_CLOSE 0x0000007
#define SYSCALL_EXECVE 0x00000008
#define SYSCALL_FORK 0x00000009
#define SYSCALL_FSTAT 0x0000000A
#define SYSCALL_GETPID 0x0000000B
#define SYSCALL_ISTTY 0x0000000C
#define SYSCALL_KILL 0x0000000D
#define SYSCALL_LINK 0x0000000E
#define SYSCALL_LSEEK 0x00000010
#define SYSCALL_OPEN 0x00000011
#define SYSCALL_READ 0x00000012
#define SYSCALL_SBRK 0x00000013
#define SYSCALL_STAT 0x00000014
#define SYSCALL_TIMES 0x00000015
#define SYSCALL_UNLINK 0x00000016
#define SYSCALL_WAIT 0x00000017
#define SYSCALL_WRITE 0x00000018

//! Installs a system call routine
void SystemCallInstall(DWORD code, LPVOID proc);

//! Handles system calls
void SystemCallHandler(struct regs *r);

//! Setup system calls
void SetupSystemCalls();

// -- System call list --
void SysCall_DebugMessage(struct regs *r);
void SysCall_ConsolePutch(struct regs *r);
void SysCall_ConsolePuts(struct regs *r);
void SysCall_GetBootHeader(struct regs *r);
void SysCall_TimerGetTime(struct regs *r);
void SysCall_TimerGetTicks(struct regs *r);
void SysCall_Nop(struct regs *r);

#endif /* __SYSCALLS__H */
