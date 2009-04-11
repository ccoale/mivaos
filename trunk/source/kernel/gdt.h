#ifndef __GDT_H
#define __GDT_H

//! Sets a specific GDT gate
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)

//! Installs the base GDT
void gdt_install();

//! Reloads new segment registers
extern void gdt_flush(void);

#endif /* __GDT_H */

