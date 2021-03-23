#include <stddef.h>
#include <stdint.h>
#include "irq.h"
#include "exception.h"
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

struct idt_entry idt[256];

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

void install_idt()
{
	//0x8e - interupt gate

	//populate exceptions
	idt[0] = make_idt_entry((uint32_t)&EX0, kg_code_seg, 0x8e);
	idt[1] = make_idt_entry((uint32_t)&EX1, kg_code_seg, 0x8e);
	idt[2] = make_idt_entry((uint32_t)&EX2, kg_code_seg, 0x8e);
	idt[3] = make_idt_entry((uint32_t)&EX3, kg_code_seg, 0x8e);
	idt[4] = make_idt_entry((uint32_t)&EX4, kg_code_seg, 0x8e);
	idt[5] = make_idt_entry((uint32_t)&EX5, kg_code_seg, 0x8e);
	idt[6] = make_idt_entry((uint32_t)&EX6, kg_code_seg, 0x8e);
	idt[7] = make_idt_entry((uint32_t)&EX7, kg_code_seg, 0x8e);
	idt[8] = make_idt_entry((uint32_t)&EX8, kg_code_seg, 0x8e);
	idt[9] = make_idt_entry((uint32_t)&EX9, kg_code_seg, 0x8e);
	idt[10] = make_idt_entry((uint32_t)&EX10, kg_code_seg, 0x8e);	
	idt[11] = make_idt_entry((uint32_t)&EX11, kg_code_seg, 0x8e);
	idt[12] = make_idt_entry((uint32_t)&EX12, kg_code_seg, 0x8e);
	idt[13] = make_idt_entry((uint32_t)&EX13, kg_code_seg, 0x8e);
	idt[14] = make_idt_entry((uint32_t)&EX14, kg_code_seg, 0x8e);
	idt[16] = make_idt_entry((uint32_t)&EX16, kg_code_seg, 0x8e);
	idt[17] = make_idt_entry((uint32_t)&EX17, kg_code_seg, 0x8e);
	idt[18] = make_idt_entry((uint32_t)&EX18, kg_code_seg, 0x8e);
	idt[19] = make_idt_entry((uint32_t)&EX19, kg_code_seg, 0x8e);
	idt[20] = make_idt_entry((uint32_t)&EX20, kg_code_seg, 0x8e);
	idt[30] = make_idt_entry((uint32_t)&EX30, kg_code_seg, 0x8e);

	//populate irqs
	idt[32] = make_idt_entry((uint32_t)&irq0, kg_code_seg, 0x8e);
	idt[33] = make_idt_entry((uint32_t)&irq1, kg_code_seg, 0x8e);
	idt[35] = make_idt_entry((uint32_t)&irq3, kg_code_seg, 0x8e);
	idt[36] = make_idt_entry((uint32_t)&irq4, kg_code_seg, 0x8e);
	idt[37] = make_idt_entry((uint32_t)&irq5, kg_code_seg, 0x8e);
	idt[38] = make_idt_entry((uint32_t)&irq6, kg_code_seg, 0x8e);
	idt[39] = make_idt_entry((uint32_t)&irq7, kg_code_seg, 0x8e);
	idt[40] = make_idt_entry((uint32_t)&irq8, kg_code_seg, 0x8e);
	idt[41] = make_idt_entry((uint32_t)&irq9, kg_code_seg, 0x8e);
	idt[42] = make_idt_entry((uint32_t)&irq10, kg_code_seg, 0x8e);
	idt[43] = make_idt_entry((uint32_t)&irq11, kg_code_seg, 0x8e);
	idt[44] = make_idt_entry((uint32_t)&irq12, kg_code_seg, 0x8e);
	idt[45] = make_idt_entry((uint32_t)&irq13, kg_code_seg, 0x8e);
	idt[46] = make_idt_entry((uint32_t)&irq14, kg_code_seg, 0x8e);
	idt[47] = make_idt_entry((uint32_t)&irq15, kg_code_seg, 0x8e);

	set_idt((uint32_t)idt, sizeof(idt));
}
