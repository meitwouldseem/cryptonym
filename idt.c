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

#define INTERRUPT_GATE 0x8e
#define TRAP_GATE 0x8f

void install_idt()
{
	//0x8e - interupt gate

	//populate exceptions
	idt[0] = make_idt_entry((uint32_t)&EX0, kg_ker_code_seg, TRAP_GATE);
	idt[1] = make_idt_entry((uint32_t)&EX1, kg_ker_code_seg, TRAP_GATE);
	idt[2] = make_idt_entry((uint32_t)&EX2, kg_ker_code_seg, TRAP_GATE);
	idt[3] = make_idt_entry((uint32_t)&EX3, kg_ker_code_seg, TRAP_GATE);
	idt[4] = make_idt_entry((uint32_t)&EX4, kg_ker_code_seg, TRAP_GATE);
	idt[5] = make_idt_entry((uint32_t)&EX5, kg_ker_code_seg, TRAP_GATE);
	idt[6] = make_idt_entry((uint32_t)&EX6, kg_ker_code_seg, TRAP_GATE);
	idt[7] = make_idt_entry((uint32_t)&EX7, kg_ker_code_seg, TRAP_GATE);
	idt[8] = make_idt_entry((uint32_t)&EX8, kg_ker_code_seg, TRAP_GATE);
	idt[9] = make_idt_entry((uint32_t)&EX9, kg_ker_code_seg, TRAP_GATE);
	idt[10] = make_idt_entry((uint32_t)&EX10, kg_ker_code_seg, TRAP_GATE);	
	idt[11] = make_idt_entry((uint32_t)&EX11, kg_ker_code_seg, TRAP_GATE);
	idt[12] = make_idt_entry((uint32_t)&EX12, kg_ker_code_seg, TRAP_GATE);
	idt[13] = make_idt_entry((uint32_t)&EX13, kg_ker_code_seg, TRAP_GATE);
	idt[14] = make_idt_entry((uint32_t)&EX14, kg_ker_code_seg, TRAP_GATE);
	idt[16] = make_idt_entry((uint32_t)&EX16, kg_ker_code_seg, TRAP_GATE);
	idt[17] = make_idt_entry((uint32_t)&EX17, kg_ker_code_seg, TRAP_GATE);
	idt[18] = make_idt_entry((uint32_t)&EX18, kg_ker_code_seg, TRAP_GATE);
	idt[19] = make_idt_entry((uint32_t)&EX19, kg_ker_code_seg, TRAP_GATE);
	idt[20] = make_idt_entry((uint32_t)&EX20, kg_ker_code_seg, TRAP_GATE);
	idt[30] = make_idt_entry((uint32_t)&EX30, kg_ker_code_seg, TRAP_GATE);

	//populate irqs
	idt[32] = make_idt_entry((uint32_t)&irq0, kg_ker_code_seg, INTERRUPT_GATE);
	idt[33] = make_idt_entry((uint32_t)&irq1, kg_ker_code_seg, INTERRUPT_GATE);
	idt[35] = make_idt_entry((uint32_t)&irq3, kg_ker_code_seg, INTERRUPT_GATE);
	idt[36] = make_idt_entry((uint32_t)&irq4, kg_ker_code_seg, INTERRUPT_GATE);
	idt[37] = make_idt_entry((uint32_t)&irq5, kg_ker_code_seg, INTERRUPT_GATE);
	idt[38] = make_idt_entry((uint32_t)&irq6, kg_ker_code_seg, INTERRUPT_GATE);
	idt[39] = make_idt_entry((uint32_t)&irq7, kg_ker_code_seg, INTERRUPT_GATE);
	idt[40] = make_idt_entry((uint32_t)&irq8, kg_ker_code_seg, INTERRUPT_GATE);
	idt[41] = make_idt_entry((uint32_t)&irq9, kg_ker_code_seg, INTERRUPT_GATE);
	idt[42] = make_idt_entry((uint32_t)&irq10, kg_ker_code_seg, INTERRUPT_GATE);
	idt[43] = make_idt_entry((uint32_t)&irq11, kg_ker_code_seg, INTERRUPT_GATE);
	idt[44] = make_idt_entry((uint32_t)&irq12, kg_ker_code_seg, INTERRUPT_GATE);
	idt[45] = make_idt_entry((uint32_t)&irq13, kg_ker_code_seg, INTERRUPT_GATE);
	idt[46] = make_idt_entry((uint32_t)&irq14, kg_ker_code_seg, INTERRUPT_GATE);
	idt[47] = make_idt_entry((uint32_t)&irq15, kg_ker_code_seg, INTERRUPT_GATE);

	set_idt((uint32_t)idt, sizeof(idt));
}
