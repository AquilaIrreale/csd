#include <stdint.h>
#include <string.h>

#include <gdt.h>
#include <gdt_asm.h>

gdt_entry_t gdt[16];
gdt_descriptor_t desc;

void gdt_set_entry(size_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	gdt[n].base_low   = base & 0xFFFF;
	gdt[n].base_midhi = (base >> 16) & 0xFF;
	gdt[n].base_hi    = (base >> 24) & 0xFF;

	gdt[n].limit_low  = limit & 0xFFFF;
	gdt[n].flags_limit_hi = (limit >> 16) & 0xF;
	gdt[n].flags_limit_hi |= (flags & 0x0C) << 4;

	gdt[n].access = (access & 0xFE) | GDT_PRESENT | 0x10;
}

void gdt_set_descriptor(gdt_descriptor_t *desc, gdt_entry_t *p, size_t n_entries)
{
	desc->size = n_entries * sizeof(gdt_entry_t) -1;
	desc->offset = (uint32_t) p;
}

void gdt_default_setup()
{
	memset(gdt, 0, sizeof gdt);

	gdt_set_entry(0, 0, 0, 0, 0);
	gdt_set_entry(1, 0, 0xFFFFFFFF,
	              GDT_CS_READABLE | GDT_EXECUTABLE | GDT_RINGLEVEL_0,
	              GDT_32_BIT_MODE | GDT_PAGE_GRANULARITY);
	gdt_set_entry(2, 0, 0xFFFFFFFF,
	              GDT_DS_WRITEABLE | GDT_RINGLEVEL_0,
	              GDT_32_BIT_MODE | GDT_PAGE_GRANULARITY);

	gdt_set_descriptor(&desc, gdt, 3);
	load_gdt(&desc);
}


