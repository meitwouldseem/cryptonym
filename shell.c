#include "terminal.h"
#include "keyboard.h"

const char* splash =
"     ___\n"
"    /\\  \\\n" 
"   /::\\  \\\n"
"  /:/\\:\\  \\\n"
" /:/  \\:\\  \\\n"
"/:/__/ \\:\\__\\\n"
"\\:\\  \\  \\/__/\n"
" \\:\\  \\\n"
"  \\:\\  \\\n"
"   \\:\\__\\\n"
"    \\/__/\n";

static void zero_buffer(char* buffer, int size)
{
	for (int i=0; i<=size; i++)
		buffer[i] = 0x0;
}

void main()
{
	term_clear(default_colour);
	term_print(splash, default_colour);
	term_putc('\n', default_colour);

	while (1)
	{
		char inpbuf[50];
		char* inpbufptr = inpbuf;

		term_print("|:> ", highlight_colour);

		while (1)
		{
			char c = getc();
			
			if (c == '\n')
				break;

			*inpbufptr = c;
			inpbufptr++;

			term_putc(c, default_colour);
		}

		term_putc('\n', default_colour);
		term_print(inpbuf, default_colour);
		term_putc('\n', default_colour);

		zero_buffer(inpbuf, sizeof(inpbuf));
	}
}
