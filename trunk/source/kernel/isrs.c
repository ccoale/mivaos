/*
** ISR API
**
*/
#include "isrs.h"
#include "video.h"
#include "syscalls.h"

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/* These are function prototypes for all of the exception
**  handlers: The first 32 entries in the IDT are reserved
**  by Intel, and are designed to service exceptions! 
*/
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();
extern void _isr128(); // system call

//! Installs all of the first 32 ISRs. + system call ISR
void IsrsInstall()
{
//	ConsolePuts("Loading ISRs...");

	IdtSetGate(0, (unsigned)_isr0, 0x08, 0x8E);
	IdtSetGate(1, (unsigned)_isr1, 0x08, 0x8E);
	IdtSetGate(2, (unsigned)_isr2, 0x08, 0x8E);
	IdtSetGate(3, (unsigned)_isr3, 0x08, 0x8E);
	IdtSetGate(4, (unsigned)_isr4, 0x08, 0x8E);
	IdtSetGate(5, (unsigned)_isr5, 0x08, 0x8E);
	IdtSetGate(6, (unsigned)_isr6, 0x08, 0x8E);
	IdtSetGate(7, (unsigned)_isr7, 0x08, 0x8E);
	IdtSetGate(8, (unsigned)_isr8, 0x08, 0x8E);
	IdtSetGate(9, (unsigned)_isr9, 0x08, 0x8E);
	IdtSetGate(10, (unsigned)_isr10, 0x08, 0x8E);
	IdtSetGate(11, (unsigned)_isr11, 0x08, 0x8E);
	IdtSetGate(12, (unsigned)_isr12, 0x08, 0x8E);
	IdtSetGate(13, (unsigned)_isr13, 0x08, 0x8E);
	IdtSetGate(14, (unsigned)_isr14, 0x08, 0x8E);
	IdtSetGate(15, (unsigned)_isr15, 0x08, 0x8E);

	IdtSetGate(16, (unsigned)_isr16, 0x08, 0x8E);
	IdtSetGate(17, (unsigned)_isr17, 0x08, 0x8E);
	IdtSetGate(18, (unsigned)_isr18, 0x08, 0x8E);
	IdtSetGate(19, (unsigned)_isr19, 0x08, 0x8E);
	IdtSetGate(20, (unsigned)_isr20, 0x08, 0x8E);
	IdtSetGate(21, (unsigned)_isr21, 0x08, 0x8E);
	IdtSetGate(22, (unsigned)_isr22, 0x08, 0x8E);
	IdtSetGate(23, (unsigned)_isr23, 0x08, 0x8E);

	IdtSetGate(24, (unsigned)_isr24, 0x08, 0x8E);
	IdtSetGate(25, (unsigned)_isr25, 0x08, 0x8E);
	IdtSetGate(26, (unsigned)_isr26, 0x08, 0x8E);
	IdtSetGate(27, (unsigned)_isr27, 0x08, 0x8E);
	IdtSetGate(28, (unsigned)_isr28, 0x08, 0x8E);
	IdtSetGate(29, (unsigned)_isr29, 0x08, 0x8E);
	IdtSetGate(30, (unsigned)_isr30, 0x08, 0x8E);
	IdtSetGate(31, (unsigned)_isr31, 0x08, 0x8E);

	// system call interrupt
	IdtSetGate(128, (unsigned)_isr128, 0x08, 0x08E);
	
//	ConsolePuts(" success!\n");
}

/*
** ISRs point to this function for now.
**
*/
void FaultHandler(struct regs *r)
{
	if (r->int_no < 32)
	{
		ConsolePuts(exception_messages[r->int_no]);
		ConsolePuts(" Exception. System Halted!\n");
		for (;;);
	}
	else if (r->int_no == 128)
	{
		SystemCallHandler(r);
	}
}

