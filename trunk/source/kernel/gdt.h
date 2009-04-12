#ifndef __GDT_H
#define __GDT_H
#include "types.h"

//! Sets a specific GDT gate
void gdt_set_gate(int num, DWORD base, DWORD limit, BYTE access, BYTE gran);

//! Installs the base GDT
void gdt_install();

//! Reloads new segment registers
extern void gdt_flush(void);

#endif /* __GDT_H */

