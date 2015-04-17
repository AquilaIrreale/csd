#ifndef _VGA_H_
	#define _VGA_H_

#include <stdint.h>

#define TM_FB_W 80
#define TM_FB_H 25
#define TM_TAB_WIDTH 8

#define VGA_COMM 0x3D4
#define VGA_DATA 0x3D5

#define VGA_COMM_SET_CURSOR_MSB 0x0E
#define VGA_COMM_SET_CURSOR_LSB 0x0F

void vga_tm_init();
void vga_tm_setcursor(uint8_t r, uint8_t c);
void vga_tm_putc(char c);
void vga_tm_puts(char *s);
void vga_tm_putx(uintmax_t n);
void vga_tm_clear();
void vga_tm_setfg(uint8_t fg);
void vga_tm_setbg(uint8_t bg);

#endif
