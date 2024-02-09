#include <print.h>

void kmain() {

  clear_screen(char_attrib_color_black);

  print_char_at(
      'X', get_char_attrib(char_attrib_color_gray, char_attrib_color_black), 15,
      40);

  char hello_str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                     "Suspendisse bibendum lectus ligula, quis molestie quam "
                     "ornare eu. Vestibulum arcu sem, facilisis sit ";
  print_string_at(
      hello_str,
      get_char_attrib(char_attrib_color_gray, char_attrib_color_black), 0, 0);
  print_hex_byte_no_prefix(
      0xD3, get_char_attrib(char_attrib_color_gray, char_attrib_color_black),
      char_lower_case, 5, 5);
  update_cursor(5, 10);
  int cursor_pos = get_cursor_position();

  for (;;)
    (void)0;
}
