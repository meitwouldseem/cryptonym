global EX0
global EX1
global EX2
global EX3
global EX4
global EX5
global EX6
global EX7
global EX8
global EX9
global EX10
global EX11
global EX12
global EX13
global EX14
;global EX15 reserved
global EX16
global EX17
global EX18
global EX19
global EX20
;vectors 21 to 29 are reserved
global EX30
;global EX31 reserved

extern EX0_handler
extern EX1_handler
extern EX2_handler
extern EX3_handler
extern EX4_handler
extern EX5_handler
extern EX6_handler
extern EX7_handler
extern EX8_handler
extern EX9_handler
extern EX10_handler
extern EX11_handler
extern EX12_handler
extern EX13_handler
extern EX14_handler
extern EX16_handler
extern EX17_handler
extern EX18_handler
extern EX19_handler
extern EX20_handler
extern EX30_handler

;divide by zero
EX0:
	pusha
	call EX0_handler
	popa
	iret
;debug
EX1:
	pusha
	call EX1_handler
	popa
	iret
;non-maskable interupt
EX2:
	pusha
	call EX2_handler
	popa
	iret
;breakpoint
EX3:
	pusha
	call EX3_handler
	popa
	iret
;overflow
EX4:
	pusha
	call EX4_handler
	popa
	iret
;bound range exceeded
EX5:
	pusha
	call EX5_handler
	popa
	iret
;invalid opcode
EX6:
	pusha
	call EX6_handler
	popa
	iret
;device not available
EX7:
	pusha
	call EX7_handler
	popa
	iret
;double fault
EX8:
	pusha
	call EX8_handler
	popa
	iret
;coprocessor segment overrun
EX9:
	pusha
	call EX9_handler
	popa
	iret
;invalid TTS
EX10:
	pusha
	call EX10_handler
	popa
	iret
;segment not present
EX11:
	pusha
	call EX11_handler
	popa
	iret
;stack segment fault
EX12:
	pusha
	call EX12_handler
	popa
	iret
;general protection fault
EX13:
	pusha
	call EX13_handler
	popa
	iret
;page fault
EX14:
	pusha
	call EX14_handler
	popa
	iret
;x87 floating-point exception
EX16:
	pusha
	call EX16_handler
	popa
	iret
;alignment check
EX17:
	pusha
	call EX17_handler
	popa
	iret
;machine check
EX18:
	pusha
	call EX18_handler
	popa
	iret
;SIMD floating point exception
EX19:
	pusha
	call EX19_handler
	popa
	iret
;virtualization exception
EX20:
	pusha
	call EX20_handler
	popa
	iret
;security exception
EX30:
	pusha
	call EX30_handler
	popa
	iret
