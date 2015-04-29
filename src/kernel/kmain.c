#include <vga.h>
#include <gdt.h>
#include <idt.h>


/* Entry point for kernel */
void kmain()
{
	gdt_default_setup();
	vga_tm_puts("Setting up GDT... DONE\n");
	vga_tm_puts("Setting up IDT... ");
	idt_default_setup();
	vga_tm_puts("DONE\n");
	vga_tm_putc('\n');
	vga_tm_puts("* EXCEPTION TEST *\nInducing a division by zero\n\n");
	int i;
	for (i = 9; i > -1; i--) {
		vga_tm_puts("2520 / ");
		vga_tm_putd(i);
		vga_tm_puts(" = ");
		int res = 2520 / i;
		vga_tm_putd(res);
		vga_tm_putc('\n');
	}
}
