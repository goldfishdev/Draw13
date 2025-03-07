#ifndef D13LIB_H
#define D13LIB_H

#include <conio.h>
#include <stdio.h>
#include <dos.h>

// add bools to C89
typedef enum { false, true } bool;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

void set_vga_mode(void);
void set_text_mode(void);
void clear_screen(void);
void put_pixel(int x, int y, unsigned char color);
void draw_rect(int x1, int y1, int x2, int y2, bool filled, unsigned char color);
void draw_rectangle(Rectangle rect, bool filled, unsigned char color);
void draw_line(int x1, int y1, int x2, int y2, unsigned char color);
void draw_circle(int centerX, int centerY, int radius, unsigned char color);

#endif
