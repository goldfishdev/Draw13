


# Drawing Functions
Also see [colors reference](colors.md).

### `put_pixel`
```c
void put_pixel(int x, int y, unsigned char color)
```
??? Implementation
	
        void put_pixel(int x, int y, unsigned char color) {
			if (x >= 0 && x < 320 && y >= 0 && y < 200) {
				buffer[y * 320 + x] = color; // set pixel in buffer
			}
		}
This is the function that all Draw13 graphics use. `put_pixel` takes a position and color. It creates a far pointer `*vga` that points to the beginning of the video memory then sets the correct byte to the given color by calculating the offset (since each row in Mode 13h is 320 pixels).

## Shapes

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
		
		### `draw_ellipse`
```c
void draw_ellipse(int cx, int cy, int width, int height, unsigned char color)
```
??? Implementation
	
		void draw_ellipse(int cx, int cy, int width, int height, unsigned char color)
		{
			int rx = width / 2;
			int ry = height / 2;
			int ry2 = ry * ry;
			int x, y, dx, start, end, py;
			float ratio, p;
			for (y = -ry; y < ry; y++) {
				x = (rx * isqrt(ry2 - y * y)) / ry;

				for (dx = -x; dx < x; dx++) {
					put_pixel(cx + dx, cy + y, color);
				}
			}
		}
      
  Currently only draws filled ellipses. Called by `draw_circle`.
  
### `draw_circle`

```c
void draw_circle(int cx, int cy, int radius, unsigned char color)
```
??? Implementation
	
        
		void draw_circle(int cx, int cy, int radius, unsigned char color)
		{
			int scaled = (radius * 4 / 3);
			draw_ellipse(cx, cy, scaled, radius, color);
		}
      
  Calls `draw_ellipse` with proper-ish scaling.

### `draw_polygon`
```c
void draw_polygon(struct Vector2 vertices[], int num_vertices, unsigned char color)
```
??? Implementation
	
        void draw_polygon(struct Vector2 vertices[], int num_vertices, unsigned char color)
		{
				int i;
				if (num_vertices < 2) return;
				for (i = 0; i < num_vertices - 1; i++) {
					draw_line(vertices[i].x, vertices[i].y,
							vertices[i+1].x, vertices[i+1].y, color);
			}
			draw_line(vertices[num_vertices-1].x, vertices[num_vertices-1].y,
					  vertices[0].x, vertices[0].y, color);
		}
Draws a polygon. 

## Text

### `draw_char`
```c
void draw_char(unsigned char ascii, int x, int y, unsigned char color)
```
??? Implementation
	
        void draw_char(unsigned char ascii, int x, int y, unsigned char color)
		{
			unsigned char byte;
			unsigned char bit;
			int font_offset;
			int row, col;
			font_offset = ascii * BYTES_PER_CHAR;
			for (row = 0; row < CHAR_HEIGHT; row++) {
				byte = DefaultFont[font_offset + row];
				for (col = 0; col < CHAR_WIDTH; col++) {
					bit = (byte >> (7 - col)) & 0x01;
					if (bit) {
						put_pixel(x + col, y + row, color);
					}
				}
			}
		}
      
  Draws a single character. Called by `draw_string`.
  
### `draw_string`
```c
void draw_string(const char* txt, int x, int y, unsigned char color)
```
??? Implementation
	
        
		void draw_string(const char* txt, int x, int y, unsigned char color)
		{
			int i = 0;
			int current_x = x;
			while (txt[i] != '\0') {
				if (current_x + CHAR_WIDTH >= 320) break;
				draw_char(txt[i], current_x, y, color);
				current_x += KERNING;
				i++;
		}	
		}
      
  Draws a string.
