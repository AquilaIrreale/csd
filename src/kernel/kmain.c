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

char ticktock[2][7] = {"Tick!\n", "Tock!\n"};
uint8_t ttc = 0;
void rtch(uint32_t err, isr_eregs_t *eregs, isr_regs_t *regs)
{
	vga_tm_puts(ticktock[ttc]);
	ttc = ttc ? 0 : 1;
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
	vga_tm_puts("Setting up PIC & ISRs... ");
	isr_setup();
	vga_tm_puts("DONE\n");
	//isr_register_handler(0x00, divh);
	//isr_register_handler(0x80, isrh);
	//isr_register_handler(IRQ0, rtch);
	//asm volatile ("movl $3, %eax; int $0x80");
	//vga_tm_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nLol\n");
	/*
	cli();
	outb(0x70, 0x8B);
	uint8_t prev = inb(0x71);
	outb(0x70, 0x8B);
	outb(0x71, prev | 0x40);
	uint8_t rate = 15;
	outb(0x70, 0x8A);
	prev = inb(0x71);
	outb(0x70, 0x8A);
	outb(0x71, (prev & 0xF0) | rate);
	//pic_clearall();
	//sti();
	*/
	hang();
}
