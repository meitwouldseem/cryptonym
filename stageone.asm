[org 0x7e00]
;program will be 4 sectors long for now.

;newline
mov ah, 0x0e
mov al, 13
int 0x10
mov al, 10
int 0x10

push sucess
call biosprint

jmp $

sucess:
	db "Stage 1 bootloader launched",0

%include "biosprint.asm"

times 2048 - ($ - $$) db 0