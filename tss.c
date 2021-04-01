#include <stdint.h>

struct tss_entry {
	uint32_t prev_tss;//points to previous tss. used for hardware task switching
	uint32_t esp0;//stack pointer to load when switching to ring 0
	uint32_t ss0;//stack segment to load when switching to ring 0
	//everything after here will be unused
	uint32_t esp1;//like esp0 but for ring 1. We don't use ring 1
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap_base;
} __attribute__((packed));

struct tss_entry tss;

uint32_t make_tss(uint32_t ker_data_seg, uint32_t ker_stack_ptr)
{
	//tss might need zeroing.

	tss.ss0 = ker_data_seg;
	tss.esp0 = ker_stack_ptr;

	return (uint32_t) &tss;
}
