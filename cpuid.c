#include <cpuid.h>
#include <stdint.h>

const char * get_vendor()
{
	static char str[13] = "BadCpuidrequ\n";
	unsigned int eax, ebx, ecx, edx;
	eax = ebx = ecx = edx = 0;

	__get_cpuid(0, &eax, &ebx, &ecx, &edx);

	uint32_t* strptr = (uint32_t*) str;

	strptr[0] = ebx;
	strptr[1] = edx;
	strptr[2] = ecx;

	return str;
}
