#ifndef _ISR_H_
	#define _ISR_H_

#include <stdint.h>

#include <isr_asm.h>
#include <iobus.h>

#define PIC1      0x20
#define PIC2      0xA0
#define PIC1_COMM (PIC1)
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMM (PIC2)
#define PIC2_DATA (PIC2 + 2)

#define PIC_EOI         0x20

#define ICW1_ICW4       0x01
#define ICW1_SINGLE     0x02
#define ICW1_INTERVAL4  0x04
#define ICW1_LEVEL      0x08
#define ICW1_INIT       0x10
 
#define ICW4_8086       0x01
#define ICW4_AUTO       0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM       0x10

#define OCW3_IRR        0x0A
#define OCW3_ISR        0x0B

typedef void (*isr_handler_t)(void); /* <--TODO arglist */

void pic_default_seup();
void pic_remap(uint8_t base);
void pic_setmask(uint8_t irq);
void pic_clearall();
void pic_setall();
void pic_clearmask(uint8_t irq);
void pic_eoi(uint8_t irq);
uint16_t pic_get_irr();
uint16_t pic_get_isr();

void isr_setup();
void isr_register_handler(uint8_t isr, isr_handler_t fh);
void isr_clear_handler();

#endif /* _ISR_H_ */
