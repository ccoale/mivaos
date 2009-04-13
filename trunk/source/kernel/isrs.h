#ifndef __ISRS_H
#define __ISRS_H
#include "idt.h"

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    DWORD gs, fs, es, ds;      /* pushed the segs last */
    DWORD edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    BYTE int_no, err_code;    /* our 'push byte #' and ecodes do this */
    DWORD eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

//! Installs all of the first 32 ISRs.
void IsrsInstall();

#endif /* __ISRS_H */

