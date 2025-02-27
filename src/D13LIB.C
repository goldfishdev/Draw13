#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <alloc.h>
#include "d13lib.h"

// WORKING:
//	- Rectangles
//	- Lines
// WIP:
//	- Circles
// 	- Text
//	- Drawing shapes using Vectors
// TODO:
//	- Image loading (PPM)
//	- Create Shape 'objects' and move them
//	- Attach color codes to names

// sets mode to 13h. might work for other modes. idk
void set_vga_mode() {
	union REGS regs;
	regs.h.ah = 0x00;
	regs.h.al = 0x13;
	int86(0x10, &regs, &regs);
}

// sets mode back to text. This makes it so that the scaling doesn't get weird.
void set_text_mode() {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = 0x03;  // 80x25 text mode
    int86(0x10, &regs, &regs);
}

// sets screen to all black. Will add different colors soon
void clear_screen() {
	unsigned char far *vga = (unsigned char far*)0xA0000000L;
	_fmemset(vga, 0, 320 * 200);
}

// puts a pixel at a position
void put_pixel(int x, int y, unsigned char color) {
	unsigned char far *vga = (unsigned char far*)0xA0000000L;
	if (x >= 0 && x < 320 && y >= 0 && y < 200) {
		vga[y*320+x] = color;
	}
}

// draw rectangle with set corners
void draw_rect(int x1, int y1, int x2, int y2, bool filled, unsigned char color) {
	// holy shit, scaling sucks!!!
	int width = x2 - x1;
	int scaled_width = (width*4)/3; // mode13h is stretched vertically. This should make up for it
	int x, y;
	if (filled == true) {
		for (y = y1; y <= y2; y++) {
			for (x = x1; x <= x1 + scaled_width; x++) {
				put_pixel(x, y, color);
			}
		}
	}
	else {
		for (x = x1; x <= x1 + scaled_width; x++) {
			put_pixel(x, y1, color);
			put_pixel(x, y2, color);
		}
		for (y = y1; y <= y2; y++) {
			put_pixel(x1, y, color);
			put_pixel(x1 + scaled_width, y, color);
		}
	}
}

// draws rectangle using Rectangle. WIP
void draw_rectangle(Rectangle rect, bool filled, unsigned char color) {
	int scaled_width = (rect.width*4)/3;
	int x1 = rect.x;
	int y1 = rect.y;
	int x2 = x1 + scaled_width;
	int y2 = y1 + rect.height;
	// use vectors for drawing?
	//Vector2 topLeft = (Vector2){ x, y };
	//Vector2 topRight = (Vector2){ x + rect.width, y };
	//Vector2 bottomLeft = (Vector2){ x, y + rect.height };
	//Vector2 bottomRight = (Vector2){ x + rect.width, y + rect.height};
	int xc, yc;
	if (filled == true) {
		for (yc = y1; yc <= y2; yc++) {
			for (xc = x1; xc <= x2; xc++) {
				put_pixel(xc, yc, color);
			}
		}
	}
	else {
		for (xc = x1; xc <= x2; xc++) {
			put_pixel(xc, y1, color);
			put_pixel(xc, y2, color);
		}
		for (yc = y1; yc <= y2; yc++) {
			put_pixel(x1, yc, color);
			put_pixel(x2, yc, color);
		}
	}
}

// draws a line
void draw_line(int x1, int y1, int x2, int y2, unsigned char color) {
	int dx, dy, sx, sy, err, e2;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;
	while (1) {
		put_pixel(x1, y1, color);
		if (x1 == x2 && y1 == y2) break;
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

// fucked up circle. no scaling. weird corners.
void draw_circle(int centerX, int centerY, int radius, unsigned char color) {
	int x = 0;
	int y = radius;
	int d = 1 - radius;
	int deltaE, deltaSE;
	int scaled_y;
	while (x <= y) {
		scaled_y = (y * 4) / 4;
		put_pixel(centerX + x, centerY + scaled_y, color);
		put_pixel(centerX - x, centerY + scaled_y, color);
		put_pixel(centerX + x, centerY - scaled_y, color);
		put_pixel(centerX - x, centerY - scaled_y, color);
		put_pixel(centerX + scaled_y, centerY + x, color);
		put_pixel(centerX - scaled_y, centerY + x, color);
		put_pixel(centerX + scaled_y, centerY - x, color);
		put_pixel(centerX - scaled_y, centerY - x, color);
		if (d < 0) {
			deltaE = 2 * x + 3;
			d += deltaE;
		}
		else {
			deltaSE = 2 * (x - y) + 5;
			d += deltaSE;
			y--;
		}
		x++;
	}
}

// more to come!

