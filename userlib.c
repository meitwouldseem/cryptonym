#include <stdint.h>
#include "syscall.h"
#include "keyboard.h"

char getc()
{
	return (char) system_enter((uint32_t) k_getc);
}
