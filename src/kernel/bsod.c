#include <bsod.h>
#include <vga.h>

void bsod(char *title, char *message)
{
	vga_tm_setfg(VGA_WHITE);
	vga_tm_setbg(VGA_BLUE);
	vga_tm_clear();
	vga_tm_setcursor(1, 2);
	vga_tm_puts("* ");
	vga_tm_puts(title);
	vga_tm_puts(" *\n\n  ");
	vga_tm_puts(message);

	/* Hanging code TODO */
	for (;;);
}


