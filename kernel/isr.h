#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct {
  uint32_t ds;                                     // data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
  uint32_t interrupt_no, err_code;                 // pushed by isr_handler.asm
  uint32_t eip, cs, eflags, useresp, ss; // pushed by cpu automatically
} asm_register_t;

#endif
