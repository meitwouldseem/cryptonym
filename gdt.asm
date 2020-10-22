;This GDT reprocudes the "basic flat model" as described by intel.
;this model defines two segments both covering the full 4GB memory
;range. One for code and one for data.

gdt_start:

;All GDTs have to start with a null descriptor. This is to catch
;mistakes where segment registers are not set or not set correctly.
;This descriptor simply has to contain 8 bytes all set to 0.
gdt_null:
	dd 0x0
	dd 0x0

gdt_code:
	dw 0xffff	;limit	(0-15)
	dw 0x0000	;base	(0-15)
	db 0x00		;base	(16-23)
	db 10011010b;Access Flags
	db 11001111b;Flags + limit (16:19)
	db 0x00		;base	(24-31)

gdt_data:
	dw 0xffff	;limit	(0-15)
	dw 0x0000	;base	(0-15)
	db 0x00		;base	(16-23)
	db 10010010b;Access Flags
	db 11001111b;Flags + limit (16:19)
	db 0x00		;base	(24-31)

gdt_end:

gdt_desc:
	dw gdt_end - gdt_start - 1;
	dd gdt_start

;These will be used later to select the desired segment to use
;when accessing memory.
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start