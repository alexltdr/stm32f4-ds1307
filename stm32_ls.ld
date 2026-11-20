ENTRY(Reset_Handler)

MEMORY {
	FLASH(rx):ORIGIN =0x08000000,LENGTH =512K
	SRAM(rwx):ORIGIN =0x20000000,LENGTH =96K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);
__max_heap_size = 0x200;
__max_stack_size = 0x400;

SECTIONS
{
	.text :
	{
    	. = ALIGN(4);
    	*(.isr_vector_tbl)
    	*(.text*)
    	*(.rodata*)
    	. = ALIGN(4);
    	_etext = .;
	} > FLASH

	.data :
	{
    	. = ALIGN(4);
    	_sdata = .;
    	*(.data*)
    	. = ALIGN(4);
    	_edata = .;
	} > SRAM AT> FLASH

	.bss :
	{
    	_sbss = .;
    	__bss_start__ = _sbss;   /* ajout */
    	*(.bss)
    	*(.bss.*)
    	*(COMMON)
    	. = ALIGN(4);
    	_ebss = .;
    	__bss_end__ = _ebss;     /* ajout */
    	. = ALIGN(4);
    	end = .;                 /* ajout */
    	__end__ = .;             /* ajout */
	} > SRAM
}
