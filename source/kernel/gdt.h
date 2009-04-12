#ifndef __GDT_H
#define __GDT_H
#include "types.h"

//! Sets a specific GDT gate
void GdtSetGgate(int num, DWORD base, DWORD limit, BYTE access, BYTE gran);

//! Installs the base GDT
void GdtInstall();

//! Reloads new segment registers
extern void GdtFlush(void);

#endif /* __GDT_H */
