CC= gcc
CFLAGS= -nostdlib -nostartfiles -nodefaultlibs
AS=nasm
A_FLAGS= -f elf
L_FLAGS=
OUTPUT = libc.a
O_FILES	= abort.o abs.o atof.o atoi.o atol.o bsearch.o ctype.o div.o getenv.o mblen.o mbstowcs.o mbtowc.o qsort.o rand.o strtod.o strtol.o wcstombs.o wctomb.o errno.o
all:	$(O_FILES) $(A_FILES)
	@rm -f $(OUTPUT)
	@echo `date '+%H:%M:%S:'` Linking
	@ld -t -T linker.ld -o $(OUTPUT) $(O_FILES)
	@echo Compile should be complete. $(OUTPUT) generated!
$(O_FILES): %.o : %.c
	@echo `date '+%H:%M:%S:'` Compiling $<.
	@$(CC) -c $(C_FLAGS) $<
clean:
	@echo `date '+%H:%M:%S:'` Deleting $(OUTPUT) and all associated object files...
	@rm -rf $(O_FILES) $(O_FILES_L) $(A_FILES)
	@rm -rf $(OUTPUT)
