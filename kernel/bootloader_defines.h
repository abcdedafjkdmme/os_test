#include <stdint.h>

uint16_t GDT_CODE_SEGMENT = 0x08;       // see boot/gdt.asm
uint16_t GDT_DATA_SEGMENT = 0x10;       // see boot/gdt.asm
static uint32_t KERNEL_OFFSET = 0x1000; // see boot/boot.asm
