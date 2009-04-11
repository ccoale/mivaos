/*
Interupt descripter table
*/
#include "idt.h"
#include "types.h"

struct idt_node
{
ushort base_low;
ushort sel; //kernel segment
UBYTE zero;
UBYTE flags;
ushort base_high;
} __attribute__((packed));

struct idt_ptr
{
ushort limit;
uint base;
} __attribute__((packed));

//global IDTs:
struct idt_node idt[256];
struct idt_ptr idtp;

extern void idt_load();

void idt_set_gate(UBYTE num,ulong base,ushort sel,UBYTE flags)
{
idt[num].base_low=(base&0xFFFF);
idt[num].base_high=(base>>16)&0xFFFF;
idt[num].sel=sel;
idt[num].zero=0;
idt[num].flags=flags;
}

void idt_install(void)
{
idtp.limit=((sizeof(struct idt_node)*256)-1);
idtp.base=&idt;
memZero(&idt,(sizeof(struct idt_node)*256));
idt_load();
}
