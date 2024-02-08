all: os-image

os-image: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image 
boot.bin : boot.asm
	nasm -w-number-overflow boot.asm -f bin -o boot.bin
kernel.bin : kernel.o kernel_entry.o 
	i686-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary
kernel.o : kernel.c 
	i686-elf-gcc -ffreestanding -o kernel.o -c kernel.c 
kernel_entry.o : kernel_entry.asm 
	nasm kernel_entry.asm -f elf -o kernel_entry.o 
run : all
	qemu-system-i386 -fda os-image

clean :
	rm *.o
	rm *.bin
	rm os-image
