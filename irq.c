#include "x86utils.h"
#include "terminal.h"

void irq0_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq1_handler()
{
	int code = inb(0x60);//must read scan code
	term_print("\nKeyboard input received!\n", default_colour);
	term_print_hex(code, default_colour);
	outb(0x20, 0x20);
	return;
}
void irq3_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq4_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq5_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq6_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq7_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq8_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq9_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq10_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq11_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq12_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq13_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq14_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
void irq15_handler()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	return;
}
