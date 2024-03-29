#ifndef PRINT_H
#define PRINT_H

#include <low_level.h>
#include <stdint.h>

#define VGA_MEM_OFFSET 0xb8000
#define VGA_MAX_WIDTH 80
#define VGA_MAX_HEIGHT 25
#define VGA_MAX_COLUMN 80
#define VGA_MAX_ROW 25
#define GRAY_ON_BLACK                                                          \
  (get_char_attrib(char_attrib_color_gray, char_attrib_color_black))

typedef struct {
  uint8_t attrib_byte;
} char_attrib;

typedef enum { char_lower_case, char_captial_case } char_case;

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

static char_attrib get_char_attrib(char_attrib_color foreground,
                                   char_attrib_color background) {
  return (char_attrib){(uint8_t)(background << 4) | foreground};
}

static int get_screen_offset(int row, int column) {
  return VGA_MEM_OFFSET + 2 * (row * 80 + column);
}

static void print_char_at(char c, char_attrib char_attribs, int row,
                          int column) {
  uint8_t *memory = (uint8_t *)get_screen_offset(row, column);
  *(memory) = c;
  *(memory + 1) = char_attribs.attrib_byte;
}
static void print_string_at(char *str, char_attrib char_attribs, int row,
                            int column) {
  int i = 0;
  char ch = str[0];
  while (ch != 0) {

    print_char_at(ch, char_attribs, row, column);

    column++;
    if (column > VGA_MAX_COLUMN) {
      column = 0;
      row++;
    }

    i++;
    ch = str[i];
  }
}

static char hex_digit_to_char(uint8_t digit, char_case c_case) {
  char c = 0;
  if (digit <= 9) {
    c = digit + 48;
  } else if (c_case == char_lower_case) {
    c = digit + 97 - 10;
  } else {
    c = digit + 65 - 10;
  }
  return c;
}
static void hex_byte_to_string(uint8_t byte, char_case c_case,
                               char *string_buffer) {
  uint8_t lower_digit = (byte & 0x0F);
  uint8_t higher_digit = (byte >> 4);

  string_buffer[0] = hex_digit_to_char(higher_digit, c_case);
  string_buffer[1] = hex_digit_to_char(lower_digit, c_case);
}
/*void print_hex_byte_no_prefix(uint8_t byte, char_attrib char_attribs,
                              char_case c_case, int row, int column) {
  char str[3];
  hex_byte_to_string(byte, c_case, &str[0]);
  print_string_at(str, char_attribs, row, column);
}*/

static void print_hex_byte(uint8_t byte, char_attrib char_attribs,
                           char_case c_case, int row, int column) {
  char str[2 + 2 + 1] = "0x";
  hex_byte_to_string(byte, c_case, &str[2]);
  print_string_at(str, char_attribs, row, column);
}

static void print_hex_word(uint16_t word, char_attrib char_attribs,
                           char_case c_case, int row, int column) {
  uint8_t low_byte = (word & 0x00FF);
  uint8_t high_byte = (word >> 8);
  char str[2 + 4 + 1] = "0x";
  hex_byte_to_string(high_byte, c_case, &str[2]);
  hex_byte_to_string(low_byte, c_case, &str[2 + 2]);
  print_string_at(str, char_attribs, row, column);
}
static void enable_cursor_ex(uint8_t cursor_start, uint8_t cursor_end) {
  outb(0x3D4, 0x0A);
  outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

  outb(0x3D4, 0x0B);
  outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

static void enable_cursor(void) { enable_cursor_ex(0, 15); }

static void disable_cursor() {
  outb(0x3D4, 0x0A);
  outb(0x3D5, 0x20);
}
static void update_cursor(int x, int y) {
  uint16_t pos = y * VGA_MAX_WIDTH + x;

  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
static uint16_t get_cursor_position(void) {
  uint16_t pos = 0;
  outb(0x3D4, 0x0F);
  pos |= inb(0x3D5);
  outb(0x3D4, 0x0E);
  pos |= ((uint16_t)inb(0x3D5)) << 8;
  return pos;
}
static void clear_screen(char_attrib_color background) {
  for (int x = 0; x < VGA_MAX_COLUMN; x++) {
    for (int y = 0; y < VGA_MAX_ROW; y++) {
      print_char_at(0, get_char_attrib(background, background), y, x);
    }
  }
}

#endif
