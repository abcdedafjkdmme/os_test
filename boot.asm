[org 0x7c00]
KERNEL_OFFSET equ 0x1000

;mov bx, string_to_print
;call print_string

;call print_newline

;mov bx, hello_world
;call print_string

;call print_newline

;mov cl, 0x38
;call print_hex_byte
;
;call print_newline

;mov cx, 0x4A8E
;call print_hex_word

mov bx , MSG_REAL_MODE
call print_string

call load_kernel

call switch_to_pm ; Note that we never return from here.

jmp $



%include "print.asm"
%include "switch_to_protected.asm"
%include "gdt.asm"
%include "read_disk.asm"

[bits 16]
load_kernel:
  mov ax, 0x0 
  mov es, ax 

  mov dl, 0x0; dl : drive
  mov ch, 0x0; ch : cylinder
  mov dh, 0x0; dh : head
  mov cl, 0x2; cl : start reading from which sector, starts from 1
  mov al, 0x15; al : read how many sectors from start point
  mov bx, KERNEL_OFFSET; es:bx is where the data will be written to

  call read_disk 
  
  ret
 
[bits 32]
BEGIN_PM:
  
  call KERNEL_OFFSET 

  jmp $

string_to_print:
  db "my char blah",0 
hello_world:
  db "hello world",0
MSG_REAL_MODE: 
  db " Started in 16 - bit Real Mode " , 0

times 510-($-$$) db 0
dw 0xaa55

