# System Functions

### `set_vga_mode`
```c
void set_vga_mode()
```
??? Implementation
	
        void set_vga_mode() {
			union REGS regs;
			regs.h.ah = 0x00; 		  // change video mode
			regs.h.al = 0x13; 		  // set it to 13h
			int86(0x10, &regs, &regs);// sets all VGA registers to new mode
		}
`set_vga_mode()` sets the VGA display's mode to Mode 13h. (I will add support for other modes soon!)
Mode 13h has 256 colors and a resolution of 300x200 pixels for 4:3. Each byte represents one pixel.
In Mode 13h, pixels aren't square. Each pixel is stretched vertically with an aspect ratio of 1.6. Most of my shape drawing functions compensate for this automatically.

### `set_text_mode`
```c
void set_text_mode()
```
??? Implementation
	
        void set_text_mode() {
		    union REGS regs;
		    regs.h.ah = 0x00;		   // change video mode
		    regs.h.al = 0x03;		   // sets it to 80x25 text mode
		    int86(0x10, &regs, &regs); // sets all VGA registers to new mode
		}
`set_text_mode()` sets the VGA display's mode to text, the default in DOS command line. By default, this is 80x25 characters. 
If you don't use this at the end of your (graphical) program, the scaling of the command line text will be strange. 

### `clear_buffer`
```c
void clear_buffer(void);
```

??? Implementation

		void clear_buffer() {
			_fmemset(buffer, 0, 320*200);
		}
Clears the buffer in video ram. 

### `copy_buffer`
```c
void copy_buffer(void);
```

??? Implementation

		void copy_buffer() { // sets vga to the buffer all at once
			unsigned char far *vga = (unsigned char far*)0xA0000000L;
			_fmemcpy(vga, buffer, 320*200);
		}
Copies the buffer to the screen.
