#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <iobus.h>

void isrh(uint32_t err, isr_eregs_t *eregs, isr_regs_t *regs)
{
	vga_tm_setfg(VGA_GREEN);
	vga_tm_puts("SYSCALL (INT 0x80) received\n");
	vga_tm_puts("Code: ");
	vga_tm_putd(regs->eax);
	vga_tm_putc('\n');
	vga_tm_puts("From: ");
	vga_tm_putx(eregs->eip);
	vga_tm_putc('\n');
	vga_tm_setfg(VGA_LIGHT_GREY);
}

uint32_t cycles = 0;
void pith(uint32_t err, isr_eregs_t *eregs, isr_regs_t *regs)
{
	cycles++;
}

void divh(uint32_t err, isr_eregs_t *eregs, isr_regs_t *regs)
{
	vga_tm_puts("Division by zero on %eip = ");
	vga_tm_putx(eregs->eip);
	vga_tm_putc('\n');
}

/* Entry point for kernel */
void kmain()
{
	vga_tm_init();
	vga_tm_puts("Setting up GDT... ");
	gdt_default_setup();
	vga_tm_puts("DONE\n");
	vga_tm_puts("Setting up IDT... ");
	idt_default_setup();
	vga_tm_puts("DONE\n");
	vga_tm_puts("Setting up PIC... ");
	isr_setup();
	vga_tm_puts("DONE\n");
	vga_tm_puts("ISR handler manager online\n");
	isr_register_handler(0x00, divh);
	isr_register_handler(0x80, isrh);
	isr_register_handler(IRQ0, pith);
	vga_tm_puts("Interrupt handlers ready\n");
	pic_clearmask(0);
	vga_tm_puts("PIT channel 0 unmasked\n");
	outb(0x61, 0);
	vga_tm_puts("PC speaker reset\n");
	sti();
	vga_tm_puts("IRQs enabled\n\n");
	for (;;) {
		vga_tm_puts("\rCounting PIT cycles: ");
		vga_tm_putd(cycles);
		if (cycles % 25 == 0) {
			outb(0x61, 0xFD);
		} else if (cycles % 25 == 5) {
			outb(0x61, 0);
		}
		hlt();
	}
	hang();
}


