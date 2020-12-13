OUTPUT_FORMAT(elf32-i386)

ENTRY(boot)

SECTIONS
{
	. = 0x7c00;
	
	.text : ALIGN(1K)
	{
		*(.boot)
		*(.text)
	}
	.data : ALIGN(1K)
	{
		*(.data)
	}
	.rodata : ALIGN(1K)
	{
		*(.rodata)
	}
	.bss : ALIGN(1K)
	{
		*(.bss)
	}
}