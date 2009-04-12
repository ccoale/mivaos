/*
interupt descripter table API
*/
#ifndef __IDT_H
#define __IDT_H
#include "types.h"

void idt_set_gate(BYTE num, DWORD base, WORD sel, BYTE flags);
void idt_install(void);

#endif
