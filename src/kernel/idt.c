#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <idt.h>
#include <idt_asm.h>
#include <isr_asm.h>

idt_gate_t idt[256];
idt_descriptor_t desc;

extern isr_stub_t isr_stubs[];

void idt_set_gate(size_t n, void *isr, uint16_t selector, uint8_t type, uint8_t attributes)
{
	uint32_t offset = (uint32_t)isr;
	idt[n].offset_lo = offset & 0xFFFF;
	idt[n].offset_hi = (offset >> 16) & 0xFFFF;
	idt[n].attributes = type & 0x0F;
	idt[n].attributes |= ((attributes << 4) & 0xF0);
	idt[n].selector = selector;
	idt[n].unused = 0x00;
}

void idt_set_descriptor(idt_descriptor_t *desc, idt_gate_t *idt, size_t n_gates)
{
	desc->size = n_gates * sizeof(idt_gate_t) -1;
	desc->offset = (uint32_t) idt;
}

void idt_default_setup()
{
	memset(idt, 0, sizeof idt);
	//idt_set_gate(0, isr0test, 0x08, 0xE, 0x8);
	size_t i;
	for (i = 0; i < 0x80; i++) {
		idt_set_gate(i, isr_stubs[i], 0x08, 0xE, 0x8);
	}
	/* INT 0x80 (128) can be raised from userspace (0xE) */
	idt_set_gate(0x80, isr_stubs[i], 0x08, 0xE, 0xE);
	for (i = 0x81; i <= 0xFF; i++) {
		idt_set_gate(i, isr_stubs[i], 0x08, 0xE, 0x8);
	}
	idt_set_descriptor(&desc, idt, 256);
	load_idt(&desc);
}


