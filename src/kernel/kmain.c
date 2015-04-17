#include <vga.h>
#include <gdt.h>

#include <isr_asm.h>

/* Entry point for kernel */
void kmain()
{
	gdt_standard_setup();
	vga_tm_puts("Setting up GDT... DONE\n");
	vga_tm_puts("ISR LOCATION TEST\nTest ISR address = ");
	vga_tm_putx((uint32_t)isr_test);
	vga_tm_puts("\nkmain address = ");
	vga_tm_putx((uint32_t)kmain);
	vga_tm_puts("\nNUMBER CHECK\n0x13579BDF = ");
	vga_tm_putx(0x13579BDF);
	vga_tm_putc('\n');
}
