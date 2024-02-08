[bits 32]
[extern kmain]
kernel_entry:
  call kmain
  jmp $
