#include <stdint.h>
#include <stdbool.h>
#include "x86utils.h"
#include "terminal.h"

#define KB_DATA 0x60

char buffer;

bool waiting = false;

//scan code set 1. GB layout
const char SC1_GB[256] = {
	 0 ,  0 , '1', '2', '3', '4', '5', '6',
	'7', '8', '9', '0', '-', '=','\b',  0 ,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
	'o', 'p', '[', ']','\n',  0 , 'a', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	'\'', 0 ,  0 ,'\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/',  0 ,  0 ,
	 0 , ' '
};
/*
Some special characters:
8 = backspace
*/

char k_getc()
{
	waiting = true;

	while (1)
	{
		hlt();
		if (waiting == false)
			break;
	}

	return buffer;
}

void process_scan_code()
{
	int code = inb(KB_DATA);

	if (waiting)
	{
		char c = SC1_GB[code];
		if (c != 0)
		{
			buffer = c;
			waiting = false;
		}
	}
}

//TODO: Add state-machine features to driver.
