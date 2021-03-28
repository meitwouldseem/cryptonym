#ifndef X86UTILS
#define X86UTILS

#include <stdint.h>

void set_gdt(uint32_t gdt, uint16_t size);

void set_idt(uint32_t idt, uint16_t size);

void flush_code_seg(uint16_t selector);

void flush_data_seg(uint16_t selector);

void test_int();

void div_zero();

void halt_system();

//inline functions do not have external linkage and must be kept here.
static inline void outb(uint16_t port, uint8_t value)
{
	asm volatile ("outb %0, %1"::"a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t value;
	asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

static inline void io_wait()
{
	asm volatile ( "jmp 1f\n\t"
	               "1:jmp 2f\n\t"
		       "2:" );
}

static inline void hlt()
{
	asm volatile ("hlt");
}

#endif
