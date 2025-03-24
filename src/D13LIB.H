#ifndef D13LIB_H
#define D13LIB_H

typedef enum { false, true } bool;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;


// default font info
#define BYTES_PER_CHAR 6
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 6
#define KERNING 6

#define KEY_A 97
#define KEY_B 98
#define KEY_C 99
#define KEY_D 100
#define KEY_E 101
#define KEY_F 102
#define KEY_G 103
#define KEY_H 104
#define KEY_I 105
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_M 109
#define KEY_N 110
#define KEY_O 111
#define KEY_P 112
#define KEY_Q 113
#define KEY_R 114
#define KEY_S 115
#define KEY_T 116
#define KEY_U 117
#define KEY_V 118
#define KEY_W 119
#define KEY_X 120
#define KEY_Y 121
#define KEY_Z 122

#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57
#define KEY_0 48

#define KEY_MINUS 45
#define KEY_EQUAL 61
#define KEY_COMMA 44
#define KEY_PERIOD 46
#define KEY_SLASH 47
#define KEY_SEMICOLON 59
#define KEY_OPEN_BRACKET 91
#define KEY_BACKSLASH 92
#define KEY_CLOSE_BRACKET 93
#define KEY_GRAVE 96

#define KEY_ESC 27
#define KEY_BS 270
#define KEY_TAB 271
#define KEY_ENTER 284
#define KEY_SPACE 32

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

#define KEY_F1 315
#define KEY_F2 316
#define KEY_F3 317
#define KEY_F4 318
#define KEY_F5 319
#define KEY_F6 320
#define KEY_F7 321
#define KEY_F8 322
#define KEY_F9 3

extern const unsigned char DefaultFont[256 * BYTES_PER_CHAR];

void set_vga_mode(void);
void set_text_mode(void);
void clear_buffer(void);
void copy_buffer(void);
void put_pixel(int x, int y, unsigned char color);
void draw_rect(int x1, int y1, int x2, int y2, bool filled, unsigned char color);
void draw_rectangle(Rectangle rect, bool filled, unsigned char color);
void draw_line(int x1, int y1, int x2, int y2, unsigned char color);
void draw_circle(int centerX, int centerY, int radius, unsigned char color);
void draw_char(unsigned char ascii, int x, int y, unsigned char color);
void draw_string(const char* txt, int x, int y, unsigned char color);
void initKeyboard();
void deinitKeyboard();
int isKeyDown(int scanCode);

#endif
