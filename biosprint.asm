;prints a null terminated string.
;Expects a null terminated string pointer to be pushed to the stack
;Only sutable for 16-bit real mode.

biosprint:
	push bp
	mov bp, sp
	
	;protect state of registers that we need to use.
	push ax
	push bx
	
	mov ah, 0x0e	;selects teletype subfunction
	mov bx, [bp+4]	;fetch argument

	.loop:
		cmp [bx], byte 0
		je .exit
		mov al, [bx]
		int 0x10
		inc bx
		jmp .loop
	.exit:
	
	pop ax
	pop bx
	
	pop bp;restore base pointer
	
	ret 2;two bytes need unwinding
	