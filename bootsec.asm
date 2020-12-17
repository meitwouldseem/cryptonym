;[org 0x7c00];bootsector gets copied to this address by the BIOS

section .boot
[bits 16]
global boot
boot:
mov bp, 0x7bff	;set base pointer
mov sp, bp		;set stack pointer
;Stack should have a clear run until 0x0500.

mov [BOOT_DISC], dl;remember what disc we booted from

push message
call biosprint

mov ah, 0x0e
mov al, [BOOT_DISC]
add al, '0';fun little trick to convert integer to ascii representation
int 0x10

call biosload

extern stageone

jmp stageone

message: 
	db "Loaded from disk: ",0

%include "biosprint.asmh"
%include "biosload.asmh"

times 510 - ($ - $$) db 0
dw  0xaa55
