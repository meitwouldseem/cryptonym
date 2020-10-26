ASM=nasm
ASMFLAGS=-f bin

bootloader.flp: bootsec.bin stageone.bin
	cat bootsec.bin stageone.bin > bootloader.flp

bootsec.bin:
	$(ASM) bootsec.asm $(ASMFLAGS) -o bootsec.bin

stageone.bin:
	$(ASM) stageone.asm $(ASMFLAGS) -o stageone.bin