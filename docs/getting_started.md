
# Getting Started

This tutorial is for Linux, so not all instructions will apply to other systems.

## Requirements:

- DOS/DOSBox[^1]
- [Turbo C++ 3.0](https://winworldpc.com/product/turbo-c/3x)

## Installing Turbo C++

!!! note

	Despite the IDE being named "Turbo C++", Draw13 is meant to be used with C.
 
 DOSBox

:	[Follow the official wiki instructions.](https://www.dosbox.com/wiki/Basic_Setup_and_Installation_of_DosBox)

Turbo C++ 3.0
:	1. [Download the floppy.](https://winworldpc.com/product/turbo-c/3x)
	2. Extract the files to one folder. They should all be .img files.
	3. Install `mtools` using your package manager of choice.
	4. Make a folder where you extracted your .img files named `turboc`.
	5. Run `for i in *.img; do echo $i; mcopy -m -i $i :: turboc; done`. This will extract the program files to the `floppy` folder.
	6. Move the program's installation files to your DOS drive.
	7. Run `INSTALL.EXE` and follow the instructions. Install to C:\TC. 
	8. Open your DOSBox config (`~/.config/dosbox/dosbox.conf` or `AUTOEXEC.BAT` on DOS) and add these lines at the end of the file:
		```
		SET PATH=C:\TC\BIN;%PATH%
		SET INCLUDE=C:\TC\INCLUDE
		SET LIB=C:\TC\LIB
		```
	You can now run programs from `C:\TC\BIN` anywhere. 
## Installing Draw13

To use Draw13, you can either download the prebuilt library in [Releases](https://github.com/goldfishdev/Draw13/releases) or build from source. 

### Building From Source

1. Download the source from [the github repo](https://github.com/goldfishdev/Draw13) and move it to your DOS drive.
2. Navigate to its folder and run:
	```bash
	tcc -IC:\TC\INCLUDE -LC:\TC\LIB -c -ml D13LIB.C
	tlib D13LIB.lib +D13LIB.obj
	```

	
## USAGE WARNING

Sometimes running in the IDE works using the projects function. Sometimes it doesn't. I genuinely don't know why. I recommend just saving your file (F2) then leaving TC (Alt+F -> Q) then building your project manually. See [Tutorial 1's compile instructions.](tutorials/tutorial1.md).
	
## Usage
See [Tutorial 1 - Basic Program](tutorials/tutorial1.md) for a simple example.
1. Use `#include "d13lib.h"`
2. Go to Directories (Alt+O -> D) and set the Output and Source directories to your project.
3. Use `set_vga_mode();`[^2] to start the graphical mode. 
4. Use `set_text_mode();`[^3] to exit Mode 13h. 
=======

### Using with Turbo C++ 3.0
As mentioned before, this sometimes works.
1. Use Alt+O then D to open the Directories menu. 
2. Make sure that Include is `C:\TC\INCLUDE` and Library is `C:\TC\LIB`.
3. Set Output and Source to your project directory. 

You can now run the program from inside of the IDE (Alt+R). Maybe. 

See [Tutorial 1 - Basic Program](tutorials/tutorial1.md) for your first program.

 [^1]: I have not tested anything on an actual DOS system. Testers are appreciated.
 [^2]: [`set_vga_mode()` docs](reference/systemfunctions.md#set_vga_mode)
 [^3]: [`set_text_mode()` docs](reference/systemfunctions.md#set_text_mode)
