#ifndef _GDT_H_
	#define _GDT_H_

#include <stddef.h>
#include <stdint.h>

#define GDT_32_BIT_MODE                   0x4
#define GDT_PAGE_GRANULARITY              0x8

#define GDT_CS_READABLE                   0x02
#define GDT_DS_WRITEABLE                  0x02
#define GDT_DIRECTION_REVERSE             0x04
#define GDT_CONFORMING_RINGLEVEL_ACCEPTED 0x04
#define GDT_EXECUTABLE                    0x08
#define GDT_RINGLEVEL_0                   0x00
#define GDT_RINGLEVEL_1                   0x20
#define GDT_RINGLEVEL_2                   0x40
#define GDT_RINGLEVEL_3                   0x60
#define GDT_PRESENT                       0x80

struct gdt_descriptor {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));

typedef struct gdt_descriptor gdt_descriptor_t;

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_midhi;
	uint8_t  access;
	uint8_t  flags_limit_hi;
	uint8_t  base_hi;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

void gdt_set_entry(size_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_set_descriptor(gdt_descriptor_t *desc, gdt_entry_t *gdt_p, size_t n_entries);
void gdt_default_setup();

#endif


