set_tele_type_mode:
  mov ah, 0x0e
  ret

;cl: the char to be printed
print_char:
  pusha

  call set_tele_type_mode
  mov al, cl
  int 0x10

  popa
  ret

print_newline:
  pusha

  mov cl, 0x0a ;newline char
  call print_char
  mov cl, 0x0d ;carriage return
  call print_char
  
  popa
  ret
;bx: pointer to the start of string
print_string:
  pusha
  
  jmp print_string_loop

print_string_loop:
  mov cx, [bx]
  call print_char
  inc bx
  cmp cl, 0
  jne print_string_loop
  
  popa
  ret

print_hex_prefix:
  pusha
  
  mov cl, '0'
  call print_char

  mov cl, 'x'
  call print_char

  popa
  ret 

;cx the word to print in hex
print_hex_word:
  pusha

  call print_hex_prefix

  call print_hex_word_no_prefix

  popa
  ret

;cx the word to print in hex
print_hex_word_no_prefix:
  pusha
  
  mov ax, cx ;temporarilyh store cx

  mov cl, ah ;mov cl, ch
  call print_hex_byte_no_prefix; high byte

  mov cl, al ;mov cl, cl
  call print_hex_byte_no_prefix; low byte

  popa
  ret

;cl: the byte to print in hex
print_hex_byte:
  pusha

  call print_hex_prefix
  call print_hex_byte_no_prefix

  popa
  ret

;cl: the byte to print in hex
print_hex_byte_no_prefix:
  pusha
  
  mov al, cl
  shr al, 4 ; the second digit
  call print_digit

  mov al, cl
  and al, 0x0f ; the first digit
  call print_digit

  popa
  ret

;al: the digit
print_digit:
  pusha

  cmp al, 10
  jb digit_less_than_10

digit_greater_than_9:
  call print_digit_greater_than_9_in_cap
  jmp endif

digit_less_than_10:
  call print_digit_less_than_10
  jmp endif

endif:
  
  popa 
  ret

;al: the digit
print_digit_greater_than_9_in_cap:
  pusha 

  add al, 55
  mov cl, al
  call print_char

  popa 
  ret

;al: the digit
print_digit_less_than_10:
  pusha

  add al, 48
  mov cl, al
  call print_char

  popa 
  ret 

