/*
interupt descripter table API
*/
#ifndef __IDT_H
#define __IDT_H
#include "types.h"
#include "memory.h"

void IdtSetGate(BYTE num, DWORD base, WORD sel, BYTE flags);
void IdtInstall(void);

#endif
