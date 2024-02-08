AS := nasm
CC := i686-elf-gcc
LD := i686-elf-ld
BUILD_DIR := build
SRC_DIR := ./

all: $(BUILD_DIR)/os-image

$(BUILD_DIR)/os-image: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin
	cat $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin > $(BUILD_DIR)/os-image 
$(BUILD_DIR)/boot.bin : boot.asm
	$(AS) -w-number-overflow boot.asm -f bin -o $(BUILD_DIR)/boot.bin
$(BUILD_DIR)/kernel.bin : $(BUILD_DIR)/kernel.o $(BUILD_DIR)/kernel_entry.o 
	$(LD) -o $(BUILD_DIR)/kernel.bin -Ttext 0x1000 $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o --oformat binary
$(BUILD_DIR)/kernel.o : kernel.c 
	$(CC) -ffreestanding -o $(BUILD_DIR)/kernel.o -c kernel.c 
$(BUILD_DIR)/kernel_entry.o : kernel_entry.asm 
	$(AS) kernel_entry.asm -f elf -o $(BUILD_DIR)/kernel_entry.o 
run : all
	qemu-system-i386 -fda $(BUILD_DIR)/os-image

clean :
	rm $(BUILD_DIR)/*
