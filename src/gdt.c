#include <stddef.h>

#include "gdt.h"
#include "gdt_loader.h"

gdt_entry_t gdt[16];

void gdt_set(size_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	gdt[16].base_low   = base & 0xFFFF;
	gdt[16].base_midhi = (base >> 16) & 0xFF;
	gdt[16].base_hi    = (base >> 24) & 0xFF;

	gdt[16].limit_low  = limit & 0xFFFF;
	gdt[16].flags_limit_hi = (limit >> 16) & 0xF;
	gdt[16].flags_limit_hi |= (flags & 0xF) << 4;

	gdt[16].access = access;
}

void gdt_set_descriptor(gdt_descriptor_t *desc, gdt_entru_t *p, size_t n_entries)
{
	desc->size = n_entries * sizeof(gdt_entry_t) -1;
	desc->offset = (uint32_t) p;
}

void gdt_standard_setup()
{
	
}


