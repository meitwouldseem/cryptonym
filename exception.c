#include "panic.h"

void EX0_handler()
{
	panic("Tried to divide by zero");
}
void EX1_handler()
{
	panic("debug");
}
void EX2_handler()
{
	panic("non-maskable interupt");
}
void EX3_handler()
{
	panic("breakpoint");
}
void EX4_handler()
{
	panic("overflow");
}
void EX5_handler()
{
	panic("bound range exceeded");
}
void EX6_handler()
{
	panic("invalid opcode");
}
void EX7_handler()
{
	panic("device not available");
}
void EX8_handler()
{
	panic("double fault");
}
void EX9_handler()
{
	panic("coprocessor overrun");
}
void EX10_handler()
{
	panic("invalid TSS");
}
void EX11_handler()
{
	panic("segment not present");
}
void EX12_handler()
{
	panic("stack segment fault");
}
void EX13_handler()
{
	panic("General protection fault");
}
void EX14_handler()
{
	panic("page fault");
}
void EX16_handler()
{
	panic("x87 floating point exception");
}
void EX17_handler()
{
	panic("alignment check");
}
void EX18_handler()
{
	panic("machine check");
}
void EX19_handler()
{
	panic("SIMD floating point exception");
}
void EX20_handler()
{
	panic("virtualization exception");
}
void EX30_handler()
{
	panic("security exception");
}
