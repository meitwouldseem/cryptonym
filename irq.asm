global irq0
global irq1
;global irq2 never raised
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

extern irq0_handler
extern irq1_handler
extern irq3_handler
extern irq4_handler
extern irq5_handler
extern irq6_handler
extern irq7_handler
extern irq8_handler
extern irq9_handler
extern irq10_handler
extern irq11_handler
extern irq12_handler
extern irq13_handler
extern irq14_handler
extern irq15_handler

;programmable interupt timer
irq0:
	pusha
	call irq0_handler
	popa
	iret

;keyboard
irq1:
	pusha
	call irq1_handler
	popa
	iret

;COM2
irq3:
	pusha
	call irq3_handler
	popa
	iret

;COM1
irq4:
	pusha
	call irq4_handler
	popa
	iret

;LPT2
irq5:
	pusha
	call irq5_handler
	popa
	iret

;floppy disk
irq6:
	pusha
	call irq6_handler
	popa
	iret

;LPT1/spurious interupt
irq7:
	pusha
	call irq7_handler
	popa
	iret

;CMOS clock
irq8:
	pusha
	call irq8_handler
	popa
	iret

;free
irq9:
	pusha
	call irq9_handler
	popa
	iret

;free
irq10:
	pusha
	call irq10_handler
	popa
	iret

;free
irq11:
	pusha
	call irq11_handler
	popa
	iret

;PS/2 mouse
irq12:
	pusha
	call irq12_handler
	popa
	iret

;FPU/coprocessor
irq13:
	pusha
	call irq13_handler
	popa
	iret

;primary ATA hard disk
irq14:
	pusha
	call irq14_handler
	popa
	iret

;secondary ATA hard disk
irq15:
	pusha
	call irq15_handler
	popa
	iret
