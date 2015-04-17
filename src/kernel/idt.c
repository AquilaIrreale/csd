#include <stddef.h>
#include <stdint.h>

#include <idt.h>

idt_gate_t idt[256];
idt_descriptor_t desc;

void idt_set_gate(uint8_t type, uint8_t attributes, uint16_t segment, idt_handler_t handler)
{
	uint32_t offset = (uint32_t)handler;
	idt[n].offset_lo = offset & 0xFFFF;
	idt[n].offset_hi = (offset >> 16) & 0xFFFF;
	idt[n].attributes = type & 0x0F;
	idt[n].attributes |= ((attributes << 4) & 0xF0);
	idt[n].
}


