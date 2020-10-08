[org 0x7e00]
;program will be 4 sectors long for now.

push sucess
call biosprint

jmp $

sucess:
	db "Stage 1 bootloader launched",0

%include "biosprint.asm"

times 2048 - ($ - $$) db 0