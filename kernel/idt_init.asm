[GLOBAL idt_init_asm]

idt_init_asm:
  mov eax, [esp + 4] ;the pointer to idt passed as a param
                     ;size is 32 bit ( 4 bytes)
  lidt [eax]
  ret

