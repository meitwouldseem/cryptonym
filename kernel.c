#include <stdint.h>
#include <stddef.h>
#include "gdt.h"
#include "kernelglobals.h"
#include "idt.h"
#include "pic.h"
#include "terminal.h"
#include "keyboard.h"
#include "shell.h"
#include "syscall.h"
#include "x86utils.h"

extern void kernel_main(void)
{
	term_setup();

	term_clear(default_colour);

	//print startup message
	term_print("Cryptonym OS.\nBuilt on ", default_colour);
	term_print(__DATE__, highlight_colour);
	term_putc(' ', default_colour);
	term_print(__TIME__, highlight_colour);

	//begin GDT init
	term_print("\nInstalling GDT: ", default_colour);

	install_gdt();

	term_print("Done!", success_colour);

	term_print("\nkernel code seg: ", default_colour);
	term_print_hex(kg_ker_code_seg, highlight_colour);
	
	term_print("\nkernel data seg: ", default_colour);
	term_print_hex(kg_ker_data_seg, highlight_colour);

	term_print("\nuser code seg: ", default_colour);
	term_print_hex(kg_usr_code_seg, highlight_colour);

	term_print("\nuser data seg: ", default_colour);
	term_print_hex(kg_usr_data_seg, highlight_colour);

	//begin IDT init
	term_print("\nInstalling IDT: ", default_colour);

	install_idt();

	term_print("Done!", success_colour);

	//div_zero();

	//begin PIC init
	term_print("\nRemapping PIC: ", default_colour);
	remap_pic(0x20, 0x28);
	term_print("Done!", success_colour);
	//disable_pic();

	//begin syscall init
	term_print("\nconfiguring syscall entrypoint: ", default_colour);
	prep_sysenter(0x3000, (uint32_t) syscall_wrapper);
	term_print("Done!", success_colour);

	term_print("\nInitialization done! Press any key to start the shell...", default_colour);

	k_getc();

	//while(1)
	//	term_putc(getc(), default_colour);

	enter_usermode((uint32_t) main);

	halt_system();
	
loop:
goto loop;
	return;
}
