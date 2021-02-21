#include <stddef.h>
#include <stdint.h>
#include "isr.h"
#include "kernelglobals.h"
#include "x86utils.h"

struct idt_entry
{
	uint16_t offset_lo;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_hi;
} __attribute__((packed));

struct idt_entry idt[10];

struct idt_entry make_idt_entry(uint32_t offset, uint16_t selector, uint8_t type_attr)
{
	struct idt_entry entry;
	
	entry.offset_lo = offset & 0xffff;
	entry.selector = selector;
	entry.zero = 0x0;
	entry.type_attr = type_attr;
	entry.offset_hi = (offset & 0xffff0000) >> 16;

	return entry;
}

int size;

void install_idt()
{
	//0x8e - interupt gate

	idt[0] = make_idt_entry(&isr1, kg_code_seg, 0x8e);

	size = sizeof(idt);

	set_idt(idt, size);
}
