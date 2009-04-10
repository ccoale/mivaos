; Miva OS boot-loader
; --------------------
; * Enable 32-bit addressing
; * Enter Protected Mode
; * Setup a temporary GDT (will be replaced with kernel's)
; * Setup 32-bit stack
; * Jump to kernel's entry point
; --------------------
ORG 0x7C00 ; BIOS loads to this address


; Make sure we are exactly 512 bytes in size
; This fills an entire sector
TIMES 510-($-$$) DB 0 ; Fill rest of space with NULLs

; Add signature
SIGNATURE DW 0xAA55