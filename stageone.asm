;[org 0x7e00]
;This is the area right after the bootsector.
[bits 16]

global stageone
stageone:
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

%include "biosprint.asmh"
%include "gdt.asmh"
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

[extern kernel_main]

call kernel_main

jmp $
