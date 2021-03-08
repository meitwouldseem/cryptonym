target remote localhost:1234
file bootloader.o
b kernel_main
set disassembly-flavor intel

define b_excpetions
	b EX0
	b EX1
	b EX2
	b EX3
	b EX4
	b EX5
	b EX6
	b EX7
	b EX8
	b EX9
	b EX10
	b EX11
	b EX12
	b EX13
	b EX14
	b EX16
	b EX17
	b EX18
	b EX19
	b EX20
	b EX30
end

define b_irqs
	b irq0
	b irq1
	b irq3
	b irq4
	b irq5
	b irq6
	b irq7
	b irq8
	b irq9
	b irq10
	b irq11
	b irq12
	b irq13
	b irq14
	b irq15
end
