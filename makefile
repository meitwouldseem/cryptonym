export PATH:=$(HOME)/opt/cross/bin/:$(PATH)

ASM_SRCS := $(wildcard *.asm)
C_SRCS := $(wildcard *.c)
ASM_OBJS := $(patsubst %.asm, %.o, $(ASM_SRCS))
C_OBJS := $(patsubst %.c, %.o, $(C_SRCS))

QEMU=qemu-system-i386
ASM=nasm
CC=i686-elf-gcc
LD=i686-elf-ld
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINKFLAGS=-ffreestanding -O2 -nostdlib -lgcc
ASMFLAGS=-f elf -F dwarf -g

.PHONY: all clean run

all: bootloader.flp

bootloader.flp: bootloader.o
	objcopy -O binary bootloader.o bootloader.flp

bootloader.o: $(C_OBJS) $(ASM_OBJS)
	$(CC) -T linker.ld -o bootloader.o $(LINKFLAGS) $(C_OBJS) $(ASM_OBJS)
#stageone.o kernel.o bootsec.o
clean:
	rm -f $(wildcard *.o) $(wildcard *.flp)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.asm
	$(ASM) $< $(ASMFLAGS) -o $@

run:
	$(QEMU) -fda bootloader.flp
