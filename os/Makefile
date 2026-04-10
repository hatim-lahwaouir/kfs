


all:
	i386-elf-as boot.s -o boot.o
	i386-elf-as gdt.s -o gdts.o
	i386-elf-as idt.s -o idts.o
	i386-elf-gcc -c kernel.c utils.c gdt.c idt.c  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i386-elf-gcc -T linker.ld -o myos -ffreestanding -O2 -nostdlib boot.o kernel.o utils.o gdt.o gdts.o idt.o idts.o -lgcc
