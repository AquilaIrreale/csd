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

#define VGA_BLACK			0x00
#define VGA_BLUE			0x01
#define VGA_GREEN			0x02
#define VGA_CYAN			0x03
#define VGA_RED				0x04
#define VGA_PURPLE			0x05
#define VGA_ORANGE			0x06
#define VGA_LIGHT_GREY		0x07
#define VGA_DARK_GREY		0x08
#define VGA_BRIGHT_BLUE		0x09
#define VGA_BRIGHT_GREEN	0x0A
#define VGA_BRIGHT_CYAN		0x0B
#define VGA_BRIGTH_RED		0x0C
#define VGA_BRIGHT_PURPLE	0x0D
#define VGA_YELLOW			0x0E
#define VGA_WHITE			0x0F

void vga_tm_init();
void vga_tm_setcursor(uint8_t r, uint8_t c);
void vga_tm_putc(char c);
void vga_tm_puts(char *s);
void vga_tm_putx(uintmax_t n);
void vga_tm_putd(uintmax_t n);
void vga_tm_clear();
void vga_tm_setfg(uint8_t fg);
void vga_tm_setbg(uint8_t bg);

// DEBUG
void vga_tm_scroll();
// END OF DEBUG

#endif
