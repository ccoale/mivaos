CC= gcc
CFLAGS= -Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs
AS=nasm
A_FLAGS= -f elf
L_FLAGS=
OUTPUT =../bin/kernel.bin
O_FILES	= console/console.o kernel/kernel.o
O_FILES_L = console.o kernel.o
A_FILES= boot/boot.o
all:	$(O_FILES) $(A_FILES)
	@rm -f $(OUTPUT)
	@echo `date '+%H:%M:%S:'` Linking
	@ld -t -T linker.ld -o $(OUTPUT) $(A_FILES) $(O_FILES_L)
$(A_FILES): %.o:%.asm
	 @echo `date '+%H:%M:%S:'` Compiling $<.
	 @$(AS) $(A_FLAGS) $<
$(O_FILES): %.o : %.c
	@echo `date '+%H:%M:%S:'` Compiling $<.
	@$(CC) -c $(C_FLAGS) $<
clean:
	@echo `date '+%H:%M:%S:'` Deleting $(OUTPUT) and all associated object files...
	@rm -f *.o
	@rm -f $(OUTPUT)
