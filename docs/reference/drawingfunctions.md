

# Drawing Functions
Also see [colors reference](colors.md).

### `put_pixel`
```c
void put_pixel(int x, int y, unsigned char color)
```
??? Implementation
	
        void put_pixel(int x, int y, unsigned char color) {
			unsigned char far *vga = (unsigned char far*)0xA0000000L;
			if (x >= 0 && x < 320 && y >= 0 && y < 200) {
				vga[y*320+x] = color;
			}
		}
This is the function that all Draw13 graphics use. `put_pixel` takes a position and color. It creates a far pointer `*vga` that points to the beginning of the video memory then sets the correct byte to the given color by calculating the offset (since each row in Mode 13h is 320 pixels).

## Shapes - Basic

### `draw_rect`
```c
void draw_rect(int x1, int y1, int x2, int y2, bool filled, unsigned char color)
```
??? Implementation
	
        void draw_rect(int x1, int y1, int x2, int y2, bool filled, unsigned char color) {
            int width = x2 - x1;
            int scaled_width = (width*4)/3;
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
      
  `draw_rect` draws a rectangle depending on the four points you give it. `draw_rectangle` is different, taking a Rectangle and using its properties instead. 

### `draw_rectangle`
```c
void draw_rectangle(Rectangle rect, bool filled, unsigned char color);
```
??? Implementation
	
        void draw_rectangle(Rectangle rect, bool filled, unsigned char color) {
				int scaled_width = (rect.width*4)/3;
				int x1 = rect.x;
				int y1 = rect.y;
				int x2 = x1 + scaled_width;
				int y2 = y1 + rect.height;
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
      
### `draw_line`
```c
void draw_line(int x1, int y1, int x2, int y2, unsigned char color)
```
??? Implementation
	
        void draw_line(int x1, int y1, int x2, int y2, unsigned char color) {
				int dx, dy, sx, sy, err, e2;
				dx = abs(x2 - x1);
				dy = abs(y2 - y1);
				sx = (x1 < x2) ? 1 : -1;
				sy = (y1 < y2) ? 1 : -1;
				err = dx - dy;
				// I think this is infinite. i should fix that
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
