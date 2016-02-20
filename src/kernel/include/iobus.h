#ifndef _IOBUS_H_
	#define _IOBUS_H_

#include <stdint.h>

void hang();

static inline uint8_t inb(uint16_t port)
{
	uint8_t value;
	asm volatile ("inb %[PORT], %[VALUE]"
				  :[VALUE]"=a"(value)
				  : [PORT]"Nd"(port));
	return value;
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t value;
	asm volatile ("inw %[PORT], %[VALUE]"
				  :[VALUE]"=a"(value)
				  : [PORT]"Nd"(port));
	return value;
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t value;
	asm volatile ("inl %[PORT], %[VALUE]"
				  :[VALUE]"=a"(value)
				  : [PORT]"Nd"(port));
	return value;
}

static inline void outb(uint16_t port, uint8_t value)
{
	asm volatile ("outb %[VALUE], %[PORT]"
				  :: [VALUE]"a"(value), [PORT]"Nd"(port));
}

static inline void outw(uint16_t port, uint16_t value)
{
	asm volatile ("outw %[VALUE], %[PORT]"
				  :: [VALUE]"a"(value), [PORT]"Nd"(port));
}

static inline void outl(uint16_t port, uint32_t value)
{
	asm volatile ("outl %[VALUE], %[PORT]"
				  :: [VALUE]"a"(value), [PORT]"Nd"(port));
}

static inline void iowait()
{
	asm volatile ("outb %%al, $0x80" :: "a"(0));
}

static inline void cli()
{
	asm volatile ("cli");
}

static inline void sti()
{
	asm volatile ("sti");
}

#endif
