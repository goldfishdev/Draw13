#include "d13lib.h"

int main() {
	set_vga_mode(); // starts mode 13h
	printf("Hello World!");
	getch(); // waits for any input before leaving
	set_text_mode(); // leaves mode 13h
	return 0;
}
