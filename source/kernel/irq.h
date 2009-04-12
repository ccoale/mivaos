#ifndef __IRQ_H
#define __IRQ_H
#include "memory.h"
#include "isrs.h"

// Installs a handler for the given IRQ number.
void irq_install_handler(int irq, void (*handler)(struct regs *r));

// Uninstalls a handler for the given IRQ number.
void irq_uninstall_handler(int irq);

// Remaps the IRQs
void irq_remap(void);

// Installs our IRQs
void irq_install();

#endif /* __IRQ_H */
