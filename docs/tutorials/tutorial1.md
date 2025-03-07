
# Tutorial 1: Hello World!

Make sure you've followed the instructions in  [Getting Started](getting_started.md)

Once you have the IDE and library set up, create a new file named `HELLO.C`. 
All programming using Draw13 is done using C89, which has a [few major differences](https://cw.fel.cvut.cz/old/_media/courses/be5b99cpl/lectures/be5b99cpl-lec10-handout-3x3.pdf) from modern C.

Here is a simple Hello World file. Don't worry, I'll explain everything afterwards:
```c
#include "d13lib.h"

int main() {
	set_vga_mode();
	printf("Hello World!");
	getch();
	set_text_mode();
	return 0;
}
```

`#include "d13lib.h"` 

:	includes the library. This is assuming that the `D13LIB.LIB` file is in the same folder as your `HELLO.C`.  

`set_vga_mode()`[^1] 

:	sets the display into [Mode 13h](https://en.wikipedia.org/wiki/Mode_13h).

`getch()`[^2] 

:	waits for any key input. 

`set_text_mode()`[^3] 

:	sets the display back to text mode (the default in DOS).

!!! note

	See [functions reference](/reference/systemfunctions) for more in-depth information.

Compile and run in the IDE by using (`Alt+R->Enter`) or in the command line by running `tcc -IC:\TC\INCLUDE -LC:\TC\LIB -ml HELLO.C D13LIB.lib`. You should see the text "Hello World!" in the top-left of the screen. Press any key to exit. 

By default, `printf()` puts text on the screen as if it were in the command line. I use this primarily for debugging, but it could also be used to show [ASCII art](https://en.wikipedia.org/wiki/ASCII_art). 

Congratulations! You've made a program! Check out [Tutorial 2 - Drawing](tutorial2.md) for drawing pixels and shapes. 

[^1]: [`set_vga_mode()` docs](/reference/systemfunctions#set_vga_mode)
[^2]: [`getch()` docs](/reference/input.md)
[^3]: [`set_text_mode()` docs](reference/systemfunctions.md#set_text_mode)
