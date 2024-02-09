#include <print.h>

void kmain() {
  clear_screen(char_attrib_color_black);
  print_char_at('X',
                get_char_attrib(char_attrib_color_red, char_attrib_color_black),
                0, 2);
  for (;;)
    (void)0;
}
