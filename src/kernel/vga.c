#include <stddef.h>
#include <stdint.h>
#include <iobus.h>
#include <vga.h>

struct vga_tm_char {
	uint8_t value;
	uint8_t color;
} __attribute__((packed));
typedef struct vga_tm_char vga_tm_char_t;

static void vga_tm_update_cursor();
static void vga_tm_scroll();

static uint8_t curs_r = 0;
static uint8_t curs_c = 0;
static uint8_t color  = 0;

static vga_tm_char_t *tm_framebuffer = (vga_tm_char_t *) 0xB8000;

void vga_tm_init()
{
	curs_r = 0;
	curs_c = 0;
	color  = 0;

	/* Init routines */
}

void vga_tm_setcursor(uint8_t r, uint8_t c)
{
	if (r > TM_FB_H || c > TM_FB_W) {
		return;
	}

	curs_r = r;
	curs_c = c;
}

void vga_tm_putc(char c)
{
	switch (c) {
		case '\0': return;

		case '\n': {
			curs_r++;
			curs_c = 0;
		} break;

		case '\t': {
			do {
				curs_c++;
			} while (curs_c % TM_TAB_WIDTH != 0);
		} break;

		case '\b': {
			if (curs_c > 0) {
				curs_c--;
			}
		} break;

		case '\r': {
			curs_c = 0;
		} break;

		default: {
			tm_framebuffer[curs_r * TM_FB_W + curs_c].value = c;
			tm_framebuffer[curs_r * TM_FB_W + curs_c].color = color;
			curs_c++;
		} break;
	}

	if (curs_c >= TM_FB_W) {
		curs_c = 0;
		curs_r++;
	} else {
		vga_tm_update_cursor();
		return;
	}

	if (curs_r >= TM_FB_H) {
		curs_r = TM_FB_H -1;
		vga_tm_scroll();
	}
	vga_tm_update_cursor();
}

void vga_tm_puts(char *s)
{
	size_t i;
	for (i = 0; s[i] != '\0'; i++) {
		vga_tm_putc(s[i]);
	}
}

void vga_tm_putx(uintmax_t n)
{
	static const char charset[] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'A', 'B',
		'C', 'D', 'E', 'F'
	};
	unsigned char buf[16];
	size_t i;
	vga_tm_puts("0x");
	if (n == 0) {
		vga_tm_putc('0');
		return;
	}
	for (i = 0; n != 0; i++) {
		buf[i] = n % 16;
		n /= 16;
	}
	for (; i > 0; i--) {
		vga_tm_putc(charset[buf[i - 1]]);
	}
}

void vga_tm_putd(uintmax_t n)
{
	unsigned char buf[32];
	size_t i;
	if (n == 0) {
		vga_tm_putc('0');
		return;
	}
	for (i = 0; n != 0; i++) {
		buf[i] = n % 10;
		n /= 10;
	}
	for (; i > 0; i--) {
		vga_tm_putc('0' + buf[i - 1]);
	}
}

void vga_tm_clear()
{
	uint8_t c;
	uint8_t r;
	for (r = 0; r < TM_FB_H; r++) {
		for (c = 0; c < TM_FB_W; c++) {
			tm_framebuffer[r * TM_FB_W + c].value = ' ';
			tm_framebuffer[r * TM_FB_W + c].color = color;
		}
	}
}

void vga_tm_setfg(uint8_t fg)
{
	color = (color & 0xF0) | (fg & 0x0F);
}

void vga_tm_setbg(uint8_t bg)
{
	color = (color & 0x0F) | ((bg & 0x0F) << 4);
}

static void vga_tm_update_cursor()
{
	uint16_t cur_pos = curs_r * TM_FB_W + curs_c;
	outb(VGA_COMM, VGA_COMM_SET_CURSOR_MSB);
	outb(VGA_DATA, (cur_pos & 0xFF00) >> 8);
	outb(VGA_COMM, VGA_COMM_SET_CURSOR_LSB);
	outb(VGA_DATA, cur_pos & 0x00FF);
}

static void vga_tm_scroll()
{
	uint8_t r;
	uint8_t c;
	for (r = 0; r < (TM_FB_H -1); r++) {
		for (c = 0; c < TM_FB_W; c++) {
			tm_framebuffer[r * TM_FB_W + c] = tm_framebuffer[(r+1) * TM_FB_W + c];
		}
	}

	for (c = 0; c < TM_FB_W; c++) {
		tm_framebuffer[r * TM_FB_W + c].value = ' ';
		tm_framebuffer[r * TM_FB_W + c].color = 0x00;
	}
}


