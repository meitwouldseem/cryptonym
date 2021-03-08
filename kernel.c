#include <stdint.h>
#include <stddef.h>
#include "gdt.h"
#include "kernelglobals.h"
#include "idt.h"
#include "pic.h"
#include "terminal.h"

#include "x86utils.h"

uint8_t success_colour;
//uint8_t default_colour;
uint8_t highlight_colour;
uint8_t warn_colour;

extern void kernel_main(void)
{
	term_setup();

	success_colour = vga_colour(VGA_GREEN, VGA_BLACK);
	//default_colour = vga_colour(VGA_WHITE, VGA_BLACK);
	highlight_colour = vga_colour(VGA_YELLOW, VGA_BLACK);
	warn_colour = vga_colour(VGA_WHITE, VGA_RED);

	term_clear(default_colour);

	term_print("Cryptonym OS.\nBuilt on ", default_colour);
	term_print(__DATE__, highlight_colour);
	term_putc(' ', default_colour);
	term_print(__TIME__, highlight_colour);

	term_print("\nInstalling GDT: ", default_colour);

	install_gdt_simple_flat();

	term_print("Done!", success_colour);

	term_print("\ncode seg: ", default_colour);
	term_print_hex(kg_code_seg, highlight_colour);
	
	term_print("\ndata seg: ", default_colour);
	term_print_hex(kg_data_seg, highlight_colour);

	term_print("\nInstalling IDT: ", default_colour);

	install_idt();

	term_print("Done!", success_colour);

	//div_zero();

	//halt_system();

	remap_pic(0x20, 0x28);
	//disable_pic();

loop:
goto loop;
	return;
}
