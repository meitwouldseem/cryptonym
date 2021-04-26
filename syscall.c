#include <stdint.h>
#include "x86utils.h"
#include "kernelglobals.h"

void prep_sysenter(uint32_t esp, uint32_t eip)
{
	//0x174 - IA32_SYSENTER_CS
	//Provides value for kernel code segment.
	//kernel data segment value is taken to be
	//value + 8
	wrmsr(0x174, kg_ker_code_seg);

	//0x175 - IA32_SYSENTER_ESP
	//value given to ESP after SYSENTER is invoked
	//This presumably overrides the value in the TSS
	wrmsr(0x175, esp);

	//0x176 - IA32_SYSENTER_EIP
	//value given to EIP after SYSENTER is invoked
	//basically this is our entrypoint into the kernel
	wrmsr(0x176, eip);
}


