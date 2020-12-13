export PATH:=$(HOME)/opt/cross/bin/:$(PATH)

ASM_SRCS := $(wildcard *.asm)
C_SRCS := $(wildcard *.c)
ASM_OBJS := $(patsubst %.asm, %.o, $(ASM_SRCS))
C_OBJS := $(patsubst %.c, %.o, $(C_SRCS))

ASM=nasm
CC=i686-elf-gcc
LD=i686-elf-ld
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINKFLAGS=-ffreestanding -O2 -nostdlib -lgcc
ASMFLAGS=-f elf

.PHONY: all clean

all: bootloader.flp

bootloader.flp: bootloader.o
	objcopy -O binary bootloader.o bootloader.flp

bootsec.o:
	$(ASM) bootsec.asm $(ASMFLAGS) -o bootsec.o

bootloader.o: stageone.o kernel.o bootsec.o
	$(CC) -T linker.ld -o bootloader.o $(LINKFLAGS) stageone.o kernel.o bootsec.o

stageone.o:
	$(ASM) stageone.asm $(ASMFLAGS) -o stageone.o

kernel.o:
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

clean:
	rm -f bootloader.flp bootsec.o stageone.bin stageone.o kernel.o bootloader.o

