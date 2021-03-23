#include "x86utils.h"
#include "keyboard.h"

void irq0_handler()
{
	outb(0x20, 0x20);
	return;
}
void irq1_handler()
{
	process_scan_code();
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
