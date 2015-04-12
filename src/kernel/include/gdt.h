#ifndef _GDT_H_
	#define _GDT_H_

#include <stddef.h>

struct gdt_descriptor {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));

typedef struct gdt_descriptor gdt_descriptor_t;

struct gdt_entry {
	uint16_t base_low;
	uint16_t limit_low;
	uint8_t  base_hi;
	uint8_t  flags_limit_hi;
	uint8_t  access;
	uint8_t  base_midhi;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

void gdt_set_entry(size_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_set_descriptor(gdt_descriptor_t *desc, gdt_entry_t *gdt_p, size_t n_entries);
void gdt_standard_setup();

#endif


