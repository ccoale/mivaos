/*
** IRQ api
*/
#include "irq.h"
#include "video.h"

// Custom IRQs
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

// Array of IRQ function pointers
void *IrqRoutines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

// Installs a handler for the given IRQ number.
void IrqInstallHandler(int irq, void (*handler)(struct regs *r))
{
    IrqRoutines[irq] = handler;
}

// Uninstalls a handler for the given IRQ number.
void IrqUninstallHandler(int irq)
{
    IrqRoutines[irq] = 0;
}

// Remaps the IRQs
void IrqRemap(void)
{
    _outportb(0x20, 0x11);
    _outportb(0xA0, 0x11);
    _outportb(0x21, 0x20);
    _outportb(0xA1, 0x28);
    _outportb(0x21, 0x04);
    _outportb(0xA1, 0x02);
    _outportb(0x21, 0x01);
    _outportb(0xA1, 0x01);
    _outportb(0x21, 0x0);
    _outportb(0xA1, 0x0);
}

// Installs our IRQs
void IrqInstall()
{
ConsolePuts("Installing IRQ.\n");
    IrqRemap();

    IdtSetGate(32, (unsigned)_irq0, 0x08, 0x8E);
    IdtSetGate(33, (unsigned)_irq1, 0x08, 0x8E);
    IdtSetGate(34, (unsigned)_irq2, 0x08, 0x8E);
    IdtSetGate(35, (unsigned)_irq3, 0x08, 0x8E);
    IdtSetGate(36, (unsigned)_irq4, 0x08, 0x8E);
    IdtSetGate(37, (unsigned)_irq5, 0x08, 0x8E);
    IdtSetGate(38, (unsigned)_irq6, 0x08, 0x8E);
    IdtSetGate(39, (unsigned)_irq7, 0x08, 0x8E);

    IdtSetGate(40, (unsigned)_irq8, 0x08, 0x8E);
    IdtSetGate(41, (unsigned)_irq9, 0x08, 0x8E);
    IdtSetGate(42, (unsigned)_irq10, 0x08, 0x8E);
    IdtSetGate(43, (unsigned)_irq11, 0x08, 0x8E);
    IdtSetGate(44, (unsigned)_irq12, 0x08, 0x8E);
    IdtSetGate(45, (unsigned)_irq13, 0x08, 0x8E);
    IdtSetGate(46, (unsigned)_irq14, 0x08, 0x8E);
    IdtSetGate(47, (unsigned)_irq15, 0x08, 0x8E);
}

// Process an INTERRUPT REQUEST. When finished, sends an EOI (end of interrupt) command to 0x20.
void IrqHandler(struct regs *r)
{
    // handler function
    void (*handler)(struct regs*);
    
    // do we have a handler to run?
    handler = IrqRoutines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    // EOI to the slave
    if (r->int_no >= 40)
    {
        _outportb(0xA0, 0x20);
    }

    // EOI to the master
    _outportb(0x20, 0x20);
}
