[org 0x7e00]
;This is the area right after the bootsector.

;newline
mov ah, 0x0e
mov al, 13
int 0x10
mov al, 10
int 0x10

push sucess
call biosprint

;Start protected mode

;mask interupts
cli

;load gdt
lgdt [gdt_desc]

;flip the switch
mov eax, cr0 
or al, 1
mov cr0, eax

;We need to do a far jump here to flush the
;processor pipeline after switching to 32 bit
jmp CODE_SEG:long_mode_start

sucess:
	db "Stage 1 bootloader launched",0

%include "biosprint.asm"
%include "gdt.asm"

[bits 32]

long_mode_start:

;now we are in protected mode all of our segment registers point
;to the null descriptor. we need to update them with our data descriptor
mov ax, DATA_SEG
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

mov ebx, 0xb8000
clear:
	mov [ebx], byte '!'
	inc ebx
	mov [ebx], byte 0x2a
	inc ebx
	cmp ebx, 0xb8fa0
	jne clear

;mov [0xb8000], byte 'H'
;mov [0xb8002], byte 'e'
;mov [0xb8004], byte 'l'
;mov [0xb8006], byte 'l'
;mov [0xb8008], byte 'o'
;mov [0xb800a], byte ' '
;mov [0xb800c], byte 'W'
;mov [0xb800e], byte 'o'
;mov [0xb8010], byte 'r'
;mov [0xb8012], byte 'l'
;mov [0xb8014], byte 'd'

jmp $

;times 512 - ($ - $$) db 0
;It seems that the bootable image needs to be aligned in size to
;the nearest sector (512 bytes) when booting on virtualbox or it
;will complain that its "inaccessable". qemu does not produce
;this behaviour.
