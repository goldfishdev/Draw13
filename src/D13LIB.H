#ifndef D13LIB_H
#define D13LIB_H

typedef enum { false, true } bool;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

struct Vector2 {
    int x;
    int y;
};

typedef struct {
	unsigned char r, g, b;
} RGB;

typedef struct {
    unsigned char* data;
    int width;
    int height;
    RGB palette[256];
} Image;

typedef struct {
    unsigned char manufacturer;
    unsigned char version;
    unsigned char encoding;
    unsigned char bits_per_pixel;
    unsigned short xmin, ymin;
    unsigned short xmax, ymax;
    unsigned short hres, vres;
    unsigned char palette16[48];
    unsigned char reserved;
    unsigned char nplanes;
    unsigned short bytes_per_line;
    unsigned short palette_info;
    unsigned short hscreen_size;
    unsigned short vscreen_size;
    unsigned char filler[54];
} PCXHeader;

// default font info
#define BYTES_PER_CHAR 6
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 6
#define KERNING 6

#define KEY_A 30
#define KEY_B 48
#define KEY_C 46
#define KEY_D 32
#define KEY_E 18
#define KEY_F 33
#define KEY_G 34
#define KEY_H 35
#define KEY_I 23
#define KEY_J 36
#define KEY_K 37
#define KEY_L 38
#define KEY_M 50
#define KEY_N 49
#define KEY_O 24
#define KEY_P 25
#define KEY_Q 16
#define KEY_R 19
#define KEY_S 31
#define KEY_T 20
#define KEY_U 22
#define KEY_V 47
#define KEY_W 17
#define KEY_X 45
#define KEY_Y 21
#define KEY_Z 44

#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 54
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_0 11

#define KEY_MINUS 12
#define KEY_EQUAL 13
#define KEY_COMMA 51
#define KEY_PERIOD 52
#define KEY_SLASH 53
#define KEY_APOSTROPHE 40
#define KEY_SEMICOLON 39
#define KEY_OPEN_BRACKET 27
#define KEY_BACKSLASH 43
#define KEY_CLOSE_BRACKET 26
#define KEY_GRAVE 41
#define KEY_DELETE 111
#define KEY_ESC 1
#define KEY_BACKSPACE 14
#define KEY_TAB 15
#define KEY_ENTER 28
#define KEY_SPACE 57
#define KEY_HOME 102
#define KEY_INSERT 110
#define KEY_END 107
#define KEY_PAGEUP 104
#define KEY_PAGEDOWN 109
#define KEY_CAPSLOCK

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10  68
#define KEY_F11 87
#define KEY_F12 88

extern const unsigned char DefaultFont[256 * BYTES_PER_CHAR];

void set_vga_mode(void);
void set_text_mode(void);
void clear_buffer(void);
void copy_buffer(void);
void put_pixel(int x, int y, unsigned char color);

int isqrt(int num);

void initKeyboard();
void deinitKeyboard();
int isKeyDown(int scanCode);

void draw_polygon(struct Vector2 vertices[], int num_vertices, unsigned char color);
void draw_rect(int x1, int y1, int x2, int y2, bool filled, unsigned char color);
void draw_rectangle(Rectangle rect, bool filled, unsigned char color);
void draw_line(int x1, int y1, int x2, int y2, unsigned char color);
void draw_circle(int centerX, int centerY, int radius, unsigned char color);
void draw_char(unsigned char ascii, int x, int y, unsigned char color);
void draw_string(const char* txt, int x, int y, unsigned char color);
void draw_ellipse(int cx, int cy, int width, int height, unsigned char color);

Image* load_pcx(const char* filename);
void free_image(Image* image);
void draw_image(Image* image, int x, int y);
void draw_image_scaled(Image* image, int x, int y, int new_width, int new_height);
void set_image_palette(Image* image);


#endif
