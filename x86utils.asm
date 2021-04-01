[bits 32]

gdt_descriptor:
	dw 0x0000
	dd 0x00000000

idt_descriptor:
	dw 0x0000
	dd 0x00000000

jump_target:
	dw 0

global set_gdt
global set_idt
global flush_code_seg
global flush_data_seg
global flush_tss

global test_int
global div_zero
global halt_system
global enter_usermode

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

enter_usermode:
	mov ax, (4 * 8) | 3;user data seg with RPL 3
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	;iret will set ss

	;must setup the stack in the way iret expects it
	mov eax, esp
	push (4 * 8) | 3
	push eax
	pushf
	push (3 * 8) | 3
	mov eax, [esp + 20];get target address
	push eax
	iret

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

flush_tss:
	mov ax, (5*8) | 3
	ltr ax
	ret
	;This is hardcoded to use entry 6 as the tss with a requested
	;privilege level of 3. This is ok to hardcode as the gdt
	;layout will never change.

set_idt:
	mov eax, [esp + 4];idt offset
	mov [idt_descriptor + 2], eax

	mov ax, [esp + 8];idt size
	mov [idt_descriptor], ax

	lidt [idt_descriptor]

	sti

	ret

test_int:
	int 0
	ret

div_zero:
	xor eax, eax
	div ax
	ret

halt_system:
	cli
	hlt
	ret
