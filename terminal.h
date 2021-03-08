#ifndef TERMINAL_H
#define TERMINAL_H

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

void term_setup();
void term_clear(uint8_t colour);
void term_print(const char* str, uint8_t colour);
void term_putc(const char c, uint8_t colour);
void term_print_hex(int i, uint8_t colour);

static inline uint8_t vga_colour(enum vga_colour_val fg, enum vga_colour_val bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_character(unsigned char c, uint8_t colour)
{
	return (uint16_t) c | (uint16_t) colour << 8;
}

#define default_colour 0x0F

#endif
