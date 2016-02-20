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

void bsod_isr(uint8_t isr)
{
	uint8_t irq;
	if (isr >= 0x20 && isr < 0x30) {
		irq = isr - 0x20;
	} else {
		irq = 0x10;
	}
	
	vga_tm_setfg(VGA_WHITE);
	vga_tm_setbg(VGA_BLUE);
	vga_tm_clear();
	vga_tm_setcursor(1, 2);
	vga_tm_puts("* INTERRUPT HANDLER MANAGER: FATAL ERROR *\n\n  ");
	vga_tm_puts("Handler missing for INT ");
	vga_tm_putx(isr);
	
	if (irq < 0x10) {
		vga_tm_puts(" (IRQ");
		vga_tm_putd(irq);
		vga_tm_puts(")\n");
	}

	/* Hanging code TODO */
	for (;;);
}


