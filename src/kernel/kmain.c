#include <vga.h>
#include <gdt.h>

/* Entry point for kernel */
void kmain()
{
	gdt_standard_setup();
	vga_tm_puts("TABULATION AND NEWLINE TEST\nColons should be aligned vertically\n\n");
	vga_tm_puts("abc\t:\n"
				"ab\t:\n"
				"a\t:\n"
				"\t:\n");
}
