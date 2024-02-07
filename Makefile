all: os-image

os-image: boot.bin
	cat boot.bin > os-image 
boot.bin : boot.asm
	nasm -w-number-overflow boot.asm -f bin -o boot.bin
run : all
	qemu-system-i386 -fda os-image

clean :
	rm *.bin
	rm os-image
