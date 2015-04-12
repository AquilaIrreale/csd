
#include <gdt.h>

/* Entry point for kernel */
void kmain()
{
	gdt_standard_setup();
}
