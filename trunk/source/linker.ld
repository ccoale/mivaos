ENTRY (loader)

SECTIONS
{
    . = 0x00100000;
    kernelBegin = .;

    .text :{
	stext = .;
        *(.text)
	etext = .;
    }

    .rodata ALIGN (0x1000) : {
        *(.rodata)
    }

    .data ALIGN (0x1000) : {
	sdata = .;
        *(.data)
	edata = .;
    }

    .bss : {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }
    kernelEnd = .;
}

