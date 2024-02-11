#include "idt.h"
#include "bootloader_defines.h"
#include <string.h>

idt_entry_t idt_entries[NUM_OF_IDT_ENTRIES];
idt_ptr_t idt_ptr;

void init_idt_ptr() {
  idt_ptr.limit = sizeof(idt_entry_t) * NUM_OF_IDT_ENTRIES - 1;
  idt_ptr.first_idt_entry_ptr = (uint32_t)&idt_entries;
}
void set_idt_entry_struct(uint8_t which_entry, uint32_t base_ptr,
                          uint16_t kerenel_segment_selector, uint8_t flags) {
  idt_entries[which_entry].base_ptr_low = base_ptr & 0xFFFF;
  idt_entries[which_entry].base_ptr_high = (base_ptr >> 16) & 0xFFFF;
  idt_entries[which_entry].kerenel_segment_selector = kerenel_segment_selector;
  idt_entries[which_entry].always_0 = 0;

  // We must uncomment the OR below when we get to using user-mode.
  // It sets the interrupt gate's privilege level to 3.
  idt_entries[which_entry].flags = flags;
}
void init_idt() {
  init_idt_ptr();
  memset(&idt_entries, 0, sizeof(idt_entry_t) * NUM_OF_IDT_ENTRIES);

  set_idt_entry_struct(0, (uint32_t)isr0, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(1, (uint32_t)isr1, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(2, (uint32_t)isr2, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(3, (uint32_t)isr3, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(4, (uint32_t)isr4, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(5, (uint32_t)isr5, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(6, (uint32_t)isr6, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(7, (uint32_t)isr7, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(8, (uint32_t)isr8, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(9, (uint32_t)isr9, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(10, (uint32_t)isr10, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(11, (uint32_t)isr11, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(12, (uint32_t)isr12, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(13, (uint32_t)isr13, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(14, (uint32_t)isr14, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(15, (uint32_t)isr15, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(16, (uint32_t)isr16, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(17, (uint32_t)isr17, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(18, (uint32_t)isr18, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(19, (uint32_t)isr19, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(20, (uint32_t)isr20, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(21, (uint32_t)isr21, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(22, (uint32_t)isr22, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(23, (uint32_t)isr23, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(24, (uint32_t)isr24, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(25, (uint32_t)isr25, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(26, (uint32_t)isr26, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(27, (uint32_t)isr27, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(28, (uint32_t)isr28, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(29, (uint32_t)isr29, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(30, (uint32_t)isr30, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);
  set_idt_entry_struct(31, (uint32_t)isr31, GDT_CODE_SEGMENT,
                       DEFAULT_IDT_ENTRY_FLAG);

  idt_init_asm((uint32_t)&idt_ptr);
}
