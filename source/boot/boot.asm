; Miva OS boot-loader
; --------------------
; * Enable 32-bit addressing
; * Enter Protected Mode
; * Setup a temporary GDT (will be replaced with kernel's)
; * Setup 32-bit stack
; * Jump to kernel's entry point
; --------------------
BITS 16 ; 16-bits until protected mode
ORG 0x7C00 ; BIOS loads to this address

JMP BootMain

msg db "Miva OS Boot Loader 0.1", 0

Print:
	LODSB
	OR al, al
	JZ PrintDone
	MOV ah, 0x0E
	INT 0x10
	JMP Print
PrintDone:
	RET

BootMain:
	XOR ax, ax
	MOV ds, ax
	MOV es, ax
	
	; print hello message
	MOV si, msg
	CALL Print
	
	cli
	hlt
	
; Make sure we are exactly 512 bytes in size
; This fills an entire sector
TIMES 510-($-$$) DB 0 ; Fill rest of space with NULLs

; Add signature
SIGNATURE DW 0xAA55