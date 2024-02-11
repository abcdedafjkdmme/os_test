#include "isr.h"
#include "print.h"

void isr_handler(asm_register_t registers) {
  const char *interrupt_error_message = "received interrupt: ";
  print_string_at(interrupt_error_message, GRAY_ON_BLACK, 0, 0);
  for (;;)
    (void)0;
}
