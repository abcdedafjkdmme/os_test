#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>

#define VGA_MEM_OFFSET 0xb8000
#define VGA_MAX_COLUMN 80
#define VGA_MAX_ROW 25

typedef struct {
  uint8_t attrib_byte;
} char_attrib;

// the colors are in order
typedef enum {
  char_attrib_color_black,
  char_attrib_color_blue,
  char_attrib_color_green,
  char_attrib_color_cyan,
  char_attrib_color_red,
  char_attrib_color_purple,
  char_attrib_color_brown,
  char_attrib_color_gray,
  char_attrib_color_dark_gray,
  char_attrib_color_light_blue,
  char_attrib_color_light_green,
  char_attrib_color_light_cyan,
  char_attrib_color_light_red,
  char_attrib_color_light_purple,
  char_attrib_color_yellow,
  char_attrib_color_white
} char_attrib_color;

char_attrib get_char_attrib(char_attrib_color foreground,
                            char_attrib_color background) {
  return (char_attrib){(uint8_t)(background << 4) | foreground};
}

int get_screen_offset(int row, int column) {
  return VGA_MEM_OFFSET + 2 * (row * 80 + column);
};

void print_char_at(char c, char_attrib char_attribs, int row, int column) {
  uint8_t *memory = (uint8_t *)get_screen_offset(row, column);
  *(memory) = c;
  *(memory + 1) = char_attribs.attrib_byte;
}

void clear_screen(char_attrib_color background) {
  for (int x = 0; x < VGA_MAX_ROW; x++) {
    for (int y = 0; y < VGA_MAX_COLUMN; y++) {
      print_char_at(0, get_char_attrib(background, background), x, y);
    }
  }
}
#endif
