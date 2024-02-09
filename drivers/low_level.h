#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H
#include <stdint.h>

uint8_t inb(uint8_t port) {
  // A handy C wrapper function that reads a byte from the specified port
  // "= a " ( result ) means : put AL register in variable RESULT when finished
  // " d " ( port ) means : load EDX with port
  uint8_t result;
  __asm__(" in %% dx , %% al " : "=a"(result) : "d"(port));
  return result;
}
void outb(uint8_t port, uint8_t data) {
  // " a " ( data ) means : load EAX with data
  // " d " ( port ) means : load EDX with port
  __asm__(" out %% al , %% dx " : : "a"(data), "d"(port));
}
uint8_t inw(uint8_t port) {
  uint8_t result;
  __asm__(" in %% dx , %% ax " : "=a"(result) : "d"(port));
  return result;
}
void outw(uint8_t port, uint8_t data) {
  __asm__(" out %% ax , %% dx " : : "a"(data), "d"(port));
}

#endif