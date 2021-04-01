#include <stddef.h>
#include <stdint.h>
#include "x86utils.h"
#include "gdt.h"
#include "kernelglobals.h"
#include "tss.h"

struct gdt_entry
{
	uint16_t limit_lo;	//limit (0-15)
	uint16_t base_lo;	//base (0-15)
	uint8_t base_hilo;	//base (16-23)
	uint8_t access;		//access flags
	uint8_t flgs_limit;	//flgs + limit (16-19)
	uint8_t base_hihi;	//base (24-31)
} __attribute__((packed));

struct gdt_entry gdt[6];

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
void install_gdt()
{
	gdt[0] = make_gdt_entry(0, 0, 0, 0);//Null desc

	gdt[1] = make_gdt_entry(0x00000000, 0xffff, 0x9a, 0xcf);//kernel code seg
	kg_ker_code_seg = sizeof(gdt[0]) * 1;

	gdt[2] = make_gdt_entry(0x00000000, 0xffff, 0x92, 0xcf);//kernel data seg
	kg_ker_data_seg = sizeof(gdt[0]) * 2;

	gdt[3] = make_gdt_entry(0x00000000, 0xffff, 0xfa, 0xcf);//user code seg
	kg_usr_code_seg = sizeof(gdt[0]) * 3;

	gdt[4] = make_gdt_entry(0x00000000, 0xffff, 0xf2, 0xfc);//user data seg
	kg_usr_data_seg = sizeof(gdt[0]) * 4;

	//here 0x3000 is the value given to esp when entering ring 0. This
	//is just a best guess value for now but it can be changed later.
	uint32_t tss = make_tss(kg_ker_data_seg, 0x3000);
	//tss is always 104 bytes large. limit must be 0x68
	gdt[5] = make_gdt_entry(tss, 0x0006, 0xe9, 0x08);

	set_gdt((uint32_t)gdt, sizeof(gdt));

	flush_code_seg(kg_ker_code_seg);
	flush_data_seg(kg_ker_data_seg);

	flush_tss();

	return;
}

//Changing the segment register values refreshes the cached gdt entry.
//Far jumping will refresh the code segment
