/*
** Provides a GDT API for use with the Miva OS kernel.
**
*/
#include "gdt.h"

//! GDT entry structure
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((__packed__));

//! GDT pointer structure
struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((__packed__));

//! Global GDT entries
struct gdt_entry gdt[3];

//! Global GDT pointer
struct gdt_ptr gp;

//! Installs a descriptor in the GDT
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

//! Sets up our basic GDT by installing 3 entries in the GDT, and flushing the GDT.
void gdt_install(void)
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = &gdt;

    //! null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);

    //! Code Segment Descriptor (base = 0, limit = 4GB, gran=4KB, 32-bit opcodes)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    //! Data Segment Descriptor (base = 0, limit = 4GB, gran=4KB, 32-bit opcodes)
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Flush out the old GDT and install the new changes!
    gdt_flush();
}

