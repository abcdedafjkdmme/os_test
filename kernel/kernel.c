#include "idt.h"
#include <print.h>

void kmain() {

  init_idt();

  clear_screen(char_attrib_color_black);
  enable_cursor();
  print_char_at(
      'X', get_char_attrib(char_attrib_color_gray, char_attrib_color_black), 15,
      40);

  char hello_str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                     "Suspendisse bibendum lectus ligula, quis molestie quam "
                     "ornare eu. Vestibulum arcu sem, facilisis sit ";
  print_string_at(
      hello_str,
      get_char_attrib(char_attrib_color_light_cyan, char_attrib_color_black), 0,
      0);
  char str_2[] = " OS OS OS OS OS OS";
  print_string_at(
      str_2,
      get_char_attrib(char_attrib_color_light_green, char_attrib_color_black),
      10, 10);
  print_hex_byte(
      0xD3, get_char_attrib(char_attrib_color_gray, char_attrib_color_black),
      char_lower_case, 5, 5);
  update_cursor(3, 1);
  uint16_t cursor_pos = get_cursor_position();
  print_hex_word(cursor_pos, GRAY_ON_BLACK, char_lower_case, 6, 5);

  asm volatile("int $0x4");
  for (;;)
    (void)0;
}
