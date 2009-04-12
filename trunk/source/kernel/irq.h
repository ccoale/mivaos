#ifndef __IRQ_H
#define __IRQ_H
#include "memory.h"
#include "isrs.h"

// Installs a handler for the given IRQ number.
void IrqInstallHandler(int irq, void (*handler)(struct regs *r));

// Uninstalls a handler for the given IRQ number.
void IrqUninstallHandler(int irq);

// Remaps the IRQs
void IrqRemap(void);

// Installs our IRQs
void IrqInstall();

#endif /* __IRQ_H */
