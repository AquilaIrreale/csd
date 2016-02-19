#ifndef _IDT_H_
	#define _IDT_H_

#include <stddef.h>
#include <stdint.h>

struct idt_descriptor {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));
typedef struct idt_descriptor idt_descriptor_t;

struct idt_gate {
	uint16_t offset_lo;
	uint16_t selector;
	uint8_t  unused;
	uint8_t  attributes;
	uint16_t offset_hi;
} __attribute__((packed));
typedef struct idt_gate idt_gate_t;

typedef void (*isr_stub_t)();

void idt_set_gate(size_t n, void *isr, uint16_t selector, uint8_t type, uint8_t attributes);
void idt_set_descriptor(idt_descriptor_t *desc, idt_gate_t *idt, size_t n_gates);
void idt_default_setup();

#endif /* _IDT_H_ */


