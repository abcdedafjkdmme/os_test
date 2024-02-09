[bits 16]

; dl : drive
; ch : cylinder
; dh : head
; cl : start reading from which sector, starts from 1
; al : read how many sectors from start point
; es:bx is where the data will be written to
read_disk:

  mov ah, 0x02 ;BIOS READ function

  int 0x13 ;the actual read 

  jc disk_error ;carry flag will be set if the read fails
   

  ret 

disk_error:
  call print_newline 

  mov bx, disk_error_msg
  call print_string
  
  mov cl, al ; al is the amount of sectors actually read
  call print_hex_byte

  mov bx, disk_error_msg2
  call print_string

  jmp $

disk_error_msg db "error reading disk, could only read ",0
disk_error_msg2 db " sectors",0
