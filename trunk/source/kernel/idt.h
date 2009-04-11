#ifndef __IDT_H
#define __IDT_H
/*
interupt descripter table API
*/
#include "types.h"

void idt_set_gate(UBYTE num,ulong base,ushort sel,UBYTE flags);
void idt_install(void);
#endif
