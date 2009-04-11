/*
Interupt descripter table
*/
#include "idt.h"
#include "types.h"

struct idt_node
{
WORD base_low;
WORD sel; //kernel segment
BYTE zero;
BYTE flags;
WORD base_high;
} __attribute__((packed));

struct idt_ptr
{
WORD limit;
UINT base;
} __attribute__((packed));

//global IDTs:
struct idt_node idt[256];
struct idt_ptr idtp;

extern void idt_load();

void idt_set_gate(BYTE num,DWORD base,WORD sel,BYTE flags)
{
idt[num].base_low=(base&0xFFFF);
idt[num].base_high=(base>>16)&0xFFFF;
idt[num].sel=sel;
idt[num].zero=NULL;
idt[num].flags=flags;
}

void idt_install(void)
{
idtp.limit=((sizeof(struct idt_node)*256)-1);
idtp.base=&idt;
_memset(&idt,NULL,(sizeof(struct idt_node)*256));
idt_load();
}
