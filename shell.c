#include "terminal.h"
#include "userlib.h"
#include "x86utils.h"
#include "cpuid.h"

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

#define INPSIZE 50

char inpbuf[INPSIZE];

//This isn't the right place to put a strcmp implementation
//however implementing a 'propper' lib for this would be
//a big task that must wait until another day
int strcmp(const char *a, const char *b)
{
	while (1)
	{
		if (*a == *b)
		{
			if (*a == 0) {return 1;}
		}
		else
		{
			return 0;
		}
		a++;
		b++;
	}
}

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
		char* inpbufptr = inpbuf;

		zero_buffer(inpbuf, sizeof(inpbuf));//We can get some garbage data on real machines if we don't clear the buffer
		term_print("|:> ", highlight_colour);

		while (1)
		{
			char c = getc();
			
			if (c == '\n')//enter
				break;
			else if (c == '\b')//backspace
			{
				if (inpbufptr == inpbuf) continue;

				inpbufptr--;
				*inpbufptr = 0;
				term_putc(c, default_colour);
				continue;
			}

			if (inpbufptr == (inpbuf+INPSIZE)) continue;

			*inpbufptr = c;
			inpbufptr++;

			term_putc(c, default_colour);
		}


		term_putc('\n', default_colour);
		//term_print(inpbuf, default_colour);

		if (strcmp(inpbuf, "vendor"))
		{
			term_print(get_vendor(), highlight_colour);
		}
	}
}
