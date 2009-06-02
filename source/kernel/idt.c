/*
Interupt descripter table
*/
#include "idt.h"

struct idt_entry
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
struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

void IdtSetGate(BYTE num, DWORD base, WORD sel, BYTE flags)
{
	idt[num].base_low=(base&0xFFFF);
	idt[num].base_high=(base>>16)&0xFFFF;
	idt[num].sel=sel;
	idt[num].zero=NULL;
	idt[num].flags=flags;
}

void IdtInstall(void)
{
//	ConsolePuts("Loading IDT...");
	idtp.limit=((sizeof(struct idt_entry)*256)-1);
	idtp.base=(UINT)&idt;
	_memset(&idt,0,(sizeof(struct idt_entry)*256));
	IdtLoad();
//	ConsolePuts(" success!\n");
}
