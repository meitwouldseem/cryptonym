#include <stdint.h>
#include <stddef.h>

static const size_t DISP_WIDTH = 80;
static const size_t DISP_HEIGHT = 25;

enum vga_colour_val {
	VGA_BLACK=0,
	VGA_BLUE=1,
	VGA_GREEN=2,
	VGA_CYAN=3,
	VGA_RED=4,
	VGA_MAGENTA=5,
	VGA_BROWN=6,
	VGA_LIGHT_GREY=7,
	VGA_DARK_GREY=8,
	VGA_LIGHT_BLUE=9,
	VGA_LIGHT_GREEN=10,
	VGA_LIGHT_CYAN=11,
	VGA_LIGHT_RED=12,
	VGA_LIGHT_MAGENTA=13,
	VGA_YELLOW=14,
	VGA_WHITE=15,
};

size_t cursor;
uint8_t default_colour;
uint8_t highlight_colour;
uint8_t warn_colour;
uint16_t* screen_buffer;

inline uint8_t vga_colour(enum vga_colour_val fg, enum vga_colour_val bg)
{
	return fg | bg << 4;
}

inline uint16_t vga_character(unsigned char c, uint8_t colour)
{
	return (uint16_t) c | (uint16_t) colour << 8;
}

//I don't like this function. It should be more readable
void term_newline()
{
	cursor = ((cursor / DISP_WIDTH) * DISP_WIDTH) + DISP_WIDTH;
}

void term_setup()
{
	screen_buffer = (uint16_t*) 0xB8000;
	cursor = 0;
	default_colour = vga_colour(VGA_WHITE, VGA_BLACK);
	highlight_colour = vga_colour(VGA_YELLOW, VGA_BLACK);
	warn_colour = vga_colour(VGA_WHITE, VGA_RED);
}

void term_clear()
{
	const size_t limit = DISP_WIDTH * DISP_HEIGHT;
	for (size_t i=0; i<limit; i++)
	{
		screen_buffer[i] = vga_character(' ', default_colour);
	}
	cursor = 0;
}

void term_putc(const char c, uint8_t colour)
{
	switch (c)
	{
	case '\n':
		term_newline();
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

extern void kernel_main(void)
{
	term_setup();

	term_clear();

	term_print("Cryptonym OS.\nBuilt on ", default_colour);
	term_print(__DATE__, highlight_colour);
	term_putc(' ', default_colour);
	term_print(__TIME__, highlight_colour);
	term_print("\nEvery\nword\non\na\nnew\nline", default_colour);
	
loop:
goto loop;
	return;
}
