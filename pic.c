#include <stdint.h>
#include "x86utils.h"

#define MASTER_CMD	0x20
#define MASTER_DATA	0x21
#define SLAVE_CMD	0xA0
#define SLAVE_DATA	0xA1

#define ICW1_ICW4	0x01	//tells pic to expect icw4
#define ICW1_INIT	0x10	//trigger initalization

#define ICW4_8086	0x01	//set 80x86 mode

/*
The 8259 pic is configured by sending a series of 4 "control words".
Because the 8259 is a generic chip, most of the bits in these control
words relate to features that are not relavent to the x86 platform.
To avoid spurious and confusing documentation, only the function of
relevant bits will be described. Please bear this in mind.
*/
void remap_pic(uint8_t masteroffset, uint8_t slaveoffset)
{
	/*
	This code may require short delays between outb
	calls in order to give old systems enough time
	to process commands.
	*/

	/*
	step 1.
	Begin initalizing both pics while also letting
	them know to expect a 4th control word.
	Note that this word goes to the command port.
	The others will be sent to the data port.
	*/
	outb(MASTER_CMD, ICW1_ICW4 | ICW1_INIT);
	io_wait();
	outb(SLAVE_CMD,  ICW1_ICW4 | ICW1_INIT);
	io_wait();

	/*
	step 2.
	Send the interupt vector offsets for both pics
	*/
	outb(MASTER_DATA, masteroffset);
	io_wait();
	outb(SLAVE_DATA, slaveoffset);
	io_wait();

	/*
	step 3.
	Tell master that the slave is connected on IRQ2.
	Tell slave that it connects to master on IRQ2.
	*/
	outb(MASTER_DATA, 4);
	io_wait();
	outb(SLAVE_DATA, 2);
	io_wait();

	/*
	step 4.
	tell both pics to run in 80x86 mode.
	This is the 4th and final control word
	*/
	outb(MASTER_DATA, ICW4_8086);
	io_wait();
	outb(SLAVE_DATA, ICW4_8086);
	io_wait();

	/*
	step 5.
	Write new irq masks.
	0x00= all irqs unmasked
	0xFF= all irqs masked
	*/
	outb(MASTER_DATA, 0x0);
	io_wait();
	outb(SLAVE_DATA, 0x0);
	io_wait();
}

void disable_pic()
{
	outb(MASTER_DATA, 0xFF);
	outb(SLAVE_DATA, 0xFF);
}
