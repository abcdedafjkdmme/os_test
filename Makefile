ASM_SOURCES = $(wildcard kernel/*.asm)
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cstdlib/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cstdlib/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}
ASM_OBJ = ${ASM_SOURCES:.asm=.o}

# Change this if your cross-compiler is somewhere else
CC = i686-elf-gcc
GDB =i686-elf-gdb
LD = i686-elf-ld
# -g: Use debugging symbols in gcc
CFLAGS = -ffreestanding -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wconversion -Wunreachable-code -Wswitch-enum -Wswitch-default -Wcast-qual -Wwrite-strings -Wstrict-overflow=5 -I./drivers -I./kernel -I./cstdlib

# First rule is run by default
os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ} ${ASM_OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ} ${ASM_OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin -d guest_errors,int &
	#${GDB} -ex "target remote localhost:1234" -ex "file os-image.bin" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o
