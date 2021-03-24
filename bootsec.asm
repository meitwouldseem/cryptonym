;[org 0x7c00];bootsector gets copied to this address by the BIOS

section .boot
[bits 16]
global boot
boot:

jmp main
TIMES 3-($-$$) DB 0x90

db "mkfs.fat"
dw 512
db 1
dw 1
db 2
dw 224
dw 2880
db 0xf0
dw 9
dw 18
dw 2
dd 0
dd 0
db 0
db 0
db 0x29
dd 0x2d7e5a1a
db "NO NAME    "
db "FAT12   "

main:

xor ax, ax
mov ds, ax
mov ss, ax
;mov bp, 0x7bff	;set base pointer
mov sp, boot	;set stack pointer
mov bp, sp
;Stack should have a clear run until 0x0500.

mov ah, 0x0e
mov al, '!'
int 0x10;show some signs of life

mov [BOOT_DISC], dl;remember what disc we booted from

;push message
;call biosprint

;mov ah, 0x0e
mov al, [BOOT_DISC]
;add al, '0';fun little trick to convert integer to ascii representation
;int 0x10

call biosload

mov ah, 0x0e
mov al, '!'
int 0x10;prove that we made it past biosload

extern stageone

jmp stageone

;message: 
;	db "Loaded from disk: ",0

;%include "biosprint.asmh"
%include "biosload.asmh"

times 510 - ($ - $$) db 0
dw  0xaa55
