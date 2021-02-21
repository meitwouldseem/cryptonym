#ifndef X86UTILS
#define X86UTILS

#include <stdint.h>

void set_gdt(uint32_t gdt, uint16_t size);

void set_idt(uint32_t idt, uint16_t size);

void flush_code_seg(uint16_t selector);

void flush_data_seg(uint16_t selector);

void test_int();

void halt_sys();

#endif
