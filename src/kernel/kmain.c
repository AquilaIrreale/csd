#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>

void isrh(uint32_t err, isr_registers_t *regs)
{
	vga_tm_setfg(VGA_GREEN);
	vga_tm_puts("SYSCALL (INT 0x80) received\n");
	vga_tm_puts("Code: ");
	vga_tm_putd(regs->eax);
	vga_tm_setfg(VGA_LIGHT_GREY);
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
	isr_register_handler(0x40, isrh);
	asm volatile ("movl $3, %eax; int $0x40");
}
