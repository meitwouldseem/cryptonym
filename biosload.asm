;Read sectors from boot disc

;This subroutine is dependant on biosprint. Need to investigate header guards for this

STAGE_ONE_TARGET equ 0x7e00

biosload:
	mov ah, 0x02;select read sector subfunction
	mov al, 0x04;read 4 sectors from the start
	mov dh, 0x00;read head 0
	mov dl, [BOOT_DISC];read from the disc that we booted from
	mov ch, 0x00;read cylinder 0
	mov cl, 0x02;start from sector 2. no not sector 1. Sectors arn't counted from 0 for some godforsaken reason.
	
	mov bx, STAGE_ONE_TARGET;load data to the target location
	
	int 0x13;pull the trigger
	
	;carry flag will be set if the read failed.
	
	jc readerror
	
	ret

BOOT_DISC:
	db 0

readerror:
	push errormsg
	call biosprint
	jmp $

errormsg:
	db "Could not read disc",0