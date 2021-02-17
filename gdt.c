#include <stddef.h>
#include <stdint.h>
#include "x86utils.h"
#include "gdt.h"
#include "kernelglobals.h"

struct gdt_entry
{
	uint16_t limit_lo;	//limit (0-15)
	uint16_t base_lo;	//base (0-15)
	uint8_t base_hilo;	//base (16-23)
	uint8_t access;		//access flags
	uint8_t flgs_limit;	//flgs + limit (16-19)
	uint8_t base_hihi;	//base (24-31)
} __attribute__((packed));

struct gdt_entry gdt[3];

struct gdt_entry make_gdt_entry(uint32_t base, uint16_t limit_lo, uint8_t access, uint8_t flags)
{
	struct gdt_entry entry;
	
	entry.base_lo = base & 0xffff;
	entry.base_hilo = (base & 0x00ff0000) >> 16;
	entry.base_hihi = (base & 0xff000000) >> 24;

	entry.limit_lo = limit_lo;
	entry.flgs_limit = flags;
	//entry.flgs_limit = (limit & 0x0f00) >> 16;
	//entry.flgs_limit |= flags << 4;

	entry.access = access;

	return entry;
}

//modifies kernel globals
void install_gdt_simple_flat()
{
	gdt[0] = make_gdt_entry(0, 0, 0, 0);//Null desc

	gdt[1] = make_gdt_entry(0x00000000, 0xffff, 0x9a, 0xcf);//code seg
	int code_seg = sizeof(gdt[0]) * 1;

	gdt[2] = make_gdt_entry(0x00000000, 0xffff, 0x92, 0xcf);//data seg
	int data_seg = sizeof(gdt[0]) * 2;

	set_gdt(gdt, sizeof(gdt));

	flush_code_seg(code_seg);
	flush_data_seg(data_seg);

	kg_code_seg = code_seg;
	kg_data_seg = data_seg;

	return;
}

//Changing the segment register values refreshes the cached gdt entry.
//Far jumping will refresh the code segment
