#include <stdint.h>

uint8_t* screen_buffer;


extern void kernel_main(void)
{
	screen_buffer = (uint8_t*) 0xB8000;
	
	screen_buffer[0] = '!';
	//*(uint8_t*) 0xB8002 = '!';
	for (int i=0; i<10; i++)
	{
		screen_buffer[i*2] = '!';
	}
	
loop:
goto loop;
	return;
}