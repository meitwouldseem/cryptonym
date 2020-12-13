#include <stdint.h>

//uint16_t* screen_buffer;


extern void kernel_main(void)
{
	//screen_buffer = (uint16_t*) 0xB8000;
	
	//screen_buffer[0] = '!';
	*(uint8_t*) 0xB8002 = '!';
	
loop:
goto loop;
	return;
}