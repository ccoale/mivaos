#ifndef __IRQ_H
#define __IRQ_H
#include "memory.h"
#include "isrs.h"

// Device IRQ constants
#define PIC_IRQ_TIMER		0x00
#define PIC_IRQ_KEYBOARD	0x01
#define PIC_IRQ_SERIAL2		0x03
#define PIC_IRQ_SERIAL1		0x04
#define PIC_IRQ_PARALLEL2	0x05
#define PIC_IRQ_DISKETTE	0x06
#define PIC_IRQ_PARALLEL1	0x07

#define PIC_IRQ_CMOSTIMER	0x00
#define PIC_IRQ_CGARETRACE	0x01
#define PIC_IRQ_AUXILLIARY	0x04
#define PIC_IRQ_FPU		0x05
#define PIC_IRQ_HDC		0x06

// Installs a handler for the given IRQ number.
void IrqInstallHandler(int irq, void (*handler)(struct regs *r));

// Uninstalls a handler for the given IRQ number.
void IrqUninstallHandler(int irq);

// Remaps the IRQs
void IrqRemap(void);

// Installs our IRQs
void IrqInstall();

#endif /* __IRQ_H */
