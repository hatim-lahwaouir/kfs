


all:
	rm -f *.o 
	rm -f kernel.iso
	i386-elf-as boot.s -o boot.o
	i386-elf-as gdt.s -o gdts.o
	i386-elf-as idt.s -o idts.o
	i386-elf-gcc -c kernel.c keyboard.c utils.c gdt.c idt.c -O2 -std=gnu99 -ffreestanding -Wall -Wextra
	i386-elf-gcc -T linker.ld -o myos -O2 -ffreestanding -nostdlib boot.o kernel.o utils.o gdt.o gdts.o keyboard.o idt.o idts.o -lgcc
	rm -f /home/mk/os/isodir/boot/kernel
	cp myos /home/mk/os/isodir/boot/kernel
	grub-mkrescue  -o kernel.iso  /home/mk/os/isodir/ 

