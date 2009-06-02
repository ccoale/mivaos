/*
** Provides a GDT API for use with the Miva OS kernel.
**
*/
#include "gdt.h"
#include "video.h"

//! GDT entry structure
struct gdt_entry
{
	WORD limit_low;
	WORD base_low;
	BYTE base_middle;
	BYTE access;
	BYTE granularity;
	BYTE base_high;
} __attribute__((packed));

//! GDT pointer structure
struct gdt_ptr
{
	WORD limit;
	DWORD base;
} __attribute__((packed));

//! Global GDT entries
struct gdt_entry gdt[3];

//! Global GDT pointer
struct gdt_ptr gp;

//! Installs a descriptor in the GDT
void GdtSetGate(int num, DWORD base, DWORD limit, BYTE access, BYTE gran)
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
void GdtInstall()
{
//	ConsolePuts("Loading GDT...");

	/* Setup the GDT pointer and limit */
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = (UINT)&gdt;

	//! null descriptor
	GdtSetGate(0, 0, 0, 0, 0);

	//! Code Segment Descriptor (base = 0, limit = 4GB, gran=4KB, 32-bit opcodes)
	GdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	//! Data Segment Descriptor (base = 0, limit = 4GB, gran=4KB, 32-bit opcodes)
	GdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	// Flush out the old GDT and install the new changes!
	GdtFlush();

//	ConsolePuts(" success!\n");
}

