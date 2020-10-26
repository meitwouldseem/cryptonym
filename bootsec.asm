[org 0x7c00];bootsector gets copied to this address by the BIOS

mov bp, 0x7bff	;set base pointer
mov sp, bp		;set stack pointer
;Stack should have a clear run until 0x0500.

mov [BOOT_DISC], dl;remember what disc we booted from

push message
call biosprint

mov ah, 0x0e
mov al, [BOOT_DISC]
add al, '0'
int 0x10

call biosload
jmp STAGE_ONE_TARGET

message: 
	db "Loaded from disk: ",0

%include "biosprint.asm"
%include "biosload.asm"

times 510 - ($ - $$) db 0
dw  0xaa55
