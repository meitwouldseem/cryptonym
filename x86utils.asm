[bits 32]

gdt_descriptor:
	dw 0x0000
	dd 0x00000000

jump_target:
	dw 0

global set_gdt
global flush_code_seg
global flush_data_seg

set_gdt:
	;push ebp
	;mov ebp, esp

	mov eax, [esp + 4];gdt offset
	mov [gdt_descriptor + 2], eax

	mov ax, [esp + 8];gdt limit
	mov [gdt_descriptor], ax

	lgdt [gdt_descriptor]

	;pop ebp
	ret

flush_code_seg:
	;push ebp
	;mov ebp, esp

	;mov ax, [esp + 4]
	;mov [jump_target], ax

	jmp  0x08:.do_cs_flush
.do_cs_flush:
	;pop ebp
	ret
	;This function is hardcoded to use gdt entry 1 for the code
	;segment regardless of input. This is due to the fact that
	;x86 is very picky about doing far jumps on anything other
	;than immediate data. I will fix this at a later date because
	;I want the system to be as adaptable as possible. For now
	;this is a minor inconvenience.

flush_data_seg:
	;push ebp
	;mov ebp, esp

	mov ax, [esp + 4]
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	;pop ebp
	ret
