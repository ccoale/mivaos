CC= gcc
CFLAGS= -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-stack-protector
AS=nasm
A_FLAGS= -f elf
L_FLAGS=
OUTPUT =../bin/kernel.bin
O_FILES	= kernel/keyboard.o kernel/memory.o kernel/video.o kernel/idt.o kernel/gdt.o kernel/kernel.o kernel/isrs.o kernel/irq.o kernel/timer.o kernel/syscalls.o kernel/boot.o kernel/mm.o kernel/paging.o
O_FILES_L = keyboard.o memory.o video.o gdt.o kernel.o idt.o isrs.o irq.o timer.o syscalls.o boot.o mm.o paging.o
A_FILES= boot/boot.o
all:	$(O_FILES) $(A_FILES)
	@rm -f $(OUTPUT)
	@echo `date '+%H:%M:%S:'` Linking
	@ld -t -T linker.ld -o $(OUTPUT) $(A_FILES) $(O_FILES_L)
	@echo Compile should be complete. $(OUTPUT) generated!
	@echo generating iso:
	@cd ../;./build.sh
$(A_FILES): %.o:%.asm
	 @echo `date '+%H:%M:%S:'` Compiling $<.
	 @$(AS) $(A_FLAGS) $<
$(O_FILES): %.o : %.c
	@echo `date '+%H:%M:%S:'` Compiling $<.
	@$(CC) -c $(CFLAGS) $<
clean:
	@echo `date '+%H:%M:%S:'` Deleting $(OUTPUT) and all associated object files...
	@rm -rf $(O_FILES) $(O_FILES_L) $(A_FILES)
	@rm -rf $(OUTPUT)
