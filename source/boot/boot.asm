extern gp
extern idtp
extern kmain

global gdt_flush
global idt_load

global loader:

	MODULEALIGN equ 1<<0
	MEMINFO equ 1<<1
	FLAGS equ MODULEALIGN|MEMINFO
	MAGIC equ 0x1BADB002
	CHECKSUM EQU -(MAGIC+FLAGS)
SECTION .text
	ALIGN 4

MultiBootHeader:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	STACKSIZE equ 0x4000

loader:
	mov esp,stack+STACKSIZE
	push eax
	push ebx
	call kmain
	cli

gdt_flush:
	lgdt [gp]
	mov ax, 0x10 ;Load GDT using our "global gdt pointer"
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret ;return from function

idt_load:
lidt[idtp]
ret
	
hang:
	hlt
jmp hang
section .bss
align 32
stack:
resb STACKSIZE
