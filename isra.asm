global isr1

extern isr1_handler

isr1:
	pusha
	call isr1_handler
	popa
	iret
