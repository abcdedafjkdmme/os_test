#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H
#include <stdint.h>

static uint8_t inb(uint16_t port) {
  // A handy C wrapper function that reads a byte from the specified port
  // "= a " ( result ) means : put AL register in variable RESULT when finished
  // " d " ( port ) means : load EDX with port
  uint8_t result;
  __asm__(" in %% dx , %% al " : "=a"(result) : "d"(port));
  return result;
}
static void outb(uint16_t port, uint8_t data) {
  // " a " ( data ) means : load EAX with data
  // " d " ( port ) means : load EDX with port
  __asm__(" out %% al , %% dx " : : "a"(data), "d"(port));
}
static uint16_t inw(uint16_t port) {
  uint16_t result;
  __asm__(" in %% dx , %% ax " : "=a"(result) : "d"(port));
  return result;
}
static void outw(uint16_t port, uint16_t data) {
  __asm__(" out %% ax , %% dx " : : "a"(data), "d"(port));
}

#endif
