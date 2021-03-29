#include <stddef.h>
#include <stdint.h>
#include "terminal.h"

static const size_t DISP_WIDTH = 80;
static const size_t DISP_HEIGHT = 25;

size_t cursor;
uint16_t* screen_buffer;

//I don't like this function. It should be more readable
static void term_newline(uint8_t colour)
{
	cursor = ((cursor / DISP_WIDTH) * DISP_WIDTH) + DISP_WIDTH;
	if (cursor > DISP_WIDTH * DISP_HEIGHT)
	{
		cursor = 0;
		term_clear(colour);
	}
}

void term_setup()
{
	screen_buffer = (uint16_t*) 0xB8000;
	cursor = 0;
}

void term_clear(uint8_t colour)
{
	const size_t limit = DISP_WIDTH * DISP_HEIGHT;
	for (size_t i=0; i<limit; i++)
	{
		screen_buffer[i] = vga_character(' ', colour);
	}
	cursor = 0;
}

void term_putc(const char c, uint8_t colour)
{
	switch (c)
	{
	case '\n':
		term_newline(colour);
		break;
	case '\b':
		cursor--;
		screen_buffer[cursor] = 0x0000;
		break;
	default:
		screen_buffer[cursor] = vga_character(c, colour);
		cursor++;
	}
}

void term_print(const char* str, uint8_t colour)
{
	for (size_t i=0; str[i]; i++)
		term_putc(str[i], colour);
}

void term_print_hex(int i, uint8_t colour)
{
	//this function uses recursive calling in order to print digits in the correct order
	if (i == 0x0)
		return;

	char c;
	c = i & 0xF;//mask one hex digit

	if (c > 9)
		c += 55;//shift c to ascii values representing capital letters
	else
		c += 48;//otherwise shift c to ascii values representing integers

	term_print_hex(i >> 4, colour);

	term_putc(c, colour);
}
