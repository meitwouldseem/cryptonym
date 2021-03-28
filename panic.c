#include "terminal.h"
#include "x86utils.h"

void panic(char* reason)
{
	term_clear(warn_colour);

	term_print("Something has gone wrong!\nreason: ", warn_colour);

	term_print(reason, warn_colour);

	halt_system();
}
