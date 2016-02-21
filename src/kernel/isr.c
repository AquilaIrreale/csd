#include <isr.h>
#include <vga.h>
#include <bsod.h>

#include <string.h>

uint32_t pic_spurious = 0;
isr_handler_t isr_handler_table[256];

void pic_remap(uint8_t base)
{
	uint8_t off1 = base;
	uint8_t off2 = base+8;
	
	/* Save masks */
	uint8_t m1 = inb(PIC1_DATA);
	uint8_t m2 = inb(PIC2_DATA);
	
	/* Start init */
	outb(PIC1_COMM, ICW1_INIT|ICW1_ICW4);
	iowait();
	outb(PIC2_COMM, ICW1_INIT|ICW1_ICW4);
	iowait();
	
	/* Set offsets */
	outb(PIC1_DATA, off1);
	iowait();
	outb(PIC2_DATA, off2);
	iowait();
	
	/* Set master-slave interface */
	outb(PIC1_DATA, 4);
	iowait();
	outb(PIC2_DATA, 2);
	iowait();
	
	/* Set 8086 mode */
	outb(PIC1_DATA, ICW4_8086);
	iowait();
	outb(PIC2_DATA, ICW4_8086);
	iowait();
	
	/* Restore saved masks */
	outb(PIC1_DATA, m1);
	outb(PIC2_DATA, m2);
}

void pic_setmask(uint8_t irq)
{
	uint16_t port;
	uint8_t  bit;
	uint8_t  tmp;
	
	if (irq < 8) {
		port = PIC1_DATA;
		bit  = irq;
	} else {
		port = PIC2_DATA;
		bit  = irq - 8;
	}
	
	tmp  = inb(port);
	tmp |= 1 << bit;
	outb(port, tmp);
}

void pic_clearmask(uint8_t irq)
{
	uint16_t port;
	uint8_t  bit;
	uint8_t  tmp;
	
	if (irq < 8) {
		port = PIC1_DATA;
		bit  = irq;
	} else {
		port = PIC2_DATA;
		bit  = irq - 8;
	}
	
	tmp  = inb(port);
	tmp &= ~(1 << bit);
	outb(port, tmp);
}

void pic_clearall()
{
	outb(PIC1_DATA, 0x00);
	outb(PIC2_DATA, 0x00);
}

void pic_setall()
{
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}

void pic_eoi(uint8_t irq)
{
	if (irq >= 8) {
		outb(PIC2_COMM, PIC_EOI);
	}
	
	outb(PIC1_COMM, PIC_EOI);
}

uint16_t pic_get_irr()
{
	outb(PIC1_COMM, OCW3_IRR);
	outb(PIC2_COMM, OCW3_IRR);
	return inb(PIC2_COMM) << 8 | inb(PIC1_COMM);
}

uint16_t pic_get_isr()
{
	outb(PIC1_COMM, OCW3_ISR);
	outb(PIC2_COMM, OCW3_ISR);
	return inb(PIC2_COMM) << 8 | inb(PIC1_COMM);
}

void isr_setup()
{
	pic_remap(0x20);
	pic_setall();
	memset(isr_handler_table, 0, sizeof(isr_handler_t));
}

void isr_handler_manager(uint32_t isr, uint32_t err, isr_eregs_t *eregs, isr_regs_t *regs)
{
	/* Check for spurious IRQs (7, 15 (2)) */
	uint8_t irq;
	if (isr >= 32 && isr < 48) {
		irq = isr - 32;
	} else {
		irq = 16;
	}
	
	if (irq == 7 || irq == 15) {
		uint16_t inservice = pic_get_isr();
		if (irq == 7 && !(inservice & 1 << 7)) {
			pic_spurious++;
			return;
		} else if (!(inservice & 1 << 15)) {
			pic_spurious++;
			pic_eoi(2);
			return;
		}
	}

	/* Run handler */
	if (isr_handler_table[isr]) {
		isr_handler_table[isr](err, eregs, regs);
	} else {
		//bsod_isr(isr);
		vga_tm_putx(isr);
		vga_tm_putc('\n');
	}
	
	/* Send EOI */
	if (irq < 16) {
		pic_eoi(irq);
	}
}

void isr_register_handler(uint8_t isr, isr_handler_t fh)
{
	isr_handler_table[isr] = fh;
}

void isr_clear_handler()
{
	/* Shorthand for register(NULL) */
}

