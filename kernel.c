#include <stdint.h>
#include <stddef.h>

static const size_t DISP_WIDTH = 80;
static const size_t DISP_HEIGHT = 25;

enum vga_colour {
	VGA_BLACK=0,
	VGA_BLUE=2,
	VGA_GREEN=3,
	VGA_CYAN=4,
	VGA_MAGENTA=5,
	VGA_BROWN=6,
	VGA_LIGHT_GREY=7,
	VGA_DARK_GREY=8,
	VGA_LIGHT_BLUE=9,
	VGA_LIGHT_GREEN=10,
	VGA_LIGHT_CYAN=11,
	VGA_LIGHT_RED=12,
	VGA_LIGHT_MAGENTA=13,
	VGA_LIGHT_BROWN=14,
	VGA_WHITE=15,
};

inline uint8_t vga_color(enum vga_colour fg, enum vga_colour bg)
{
	return fg | bg << 4;
}

inline uint16_t vga_character(unsigned char c, uint8_t color)
{
	return (uint16_t) c | (uint16_t) color << 8;
}

size_t cursor_x;
size_t cursor_y;
uint8_t default_colour; 

uint16_t* screen_buffer;

void term_setup()
{
	screen_buffer = (uint16_t*) 0xB8000;
	cursor_x = 0;
	cursor_y = 0;
	default_colour = vga_color(VGA_WHITE, VGA_BLACK);
}

void term_clear()
{
	const size_t limit = DISP_WIDTH * DISP_HEIGHT;
	for (size_t i=0; i<limit; i++)
	{
		screen_buffer[i] = vga_character('!', default_colour);
	}
}

extern void kernel_main(void)
{
	term_setup();

	term_clear();

	//*(uint8_t*) 0xB8002 = '!';
	//for (int i=0; i<10; i++)
	//{
	//	screen_buffer[i*2] = '!';
	//}
	
loop:
goto loop;
	return;
}
