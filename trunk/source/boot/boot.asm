global loader:
extern kmain

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

_gdt_flush:
	lgdt [_gp]
	mov ax, 0x10 ;Load GDT using our "global gdt pointer"
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret ;return from function
	
hang:
	hlt
jmp hang
section .bss
align 32
stack:
resb STACKSIZE
