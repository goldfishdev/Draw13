
# Draw13

A simple DOS graphics library. 

Everything is made exclusively using programs in DOS created before 1994. 

Unfortunately, I don't have a DOS PC (they're expensive now!), so I've been developing this in DOSBOX. I have no idea if this is working on actual DOS systems, but it should :P

Expect documentation soon!

## This is VERY EXPERIMENTAL!!!
This is a very, very, very early version of this library. Don't expect anything to be functional.

I'm also a beginner at C, and this is using C89.


## Building and Installation

### REQUIREMENTS:
- [Turbo C++ 3.0](https://winworldpc.com/product/turbo-c/3x)
    - Must be installed at `C:\TC`!
- PATH must be set up for C:\TC\BIN
    - If using DOSBOX, add this to dosbox.conf:
        ```
            [autoexec]
            SET PATH=C:\TC\BIN;%PATH%
            SET INCLUDE=C:\TC\INCLUDE
            SET LIB=C:\TC\LIB
        ```

### BUILDING:

The makefile is meant for development. It builds the library then MAIN.C that I use to test it. 

To build the library, run:
```
tcc -IC:\TC\INCLUDE -LC:\TC\LIB -c -ml D13LIB.C
tlib D13LIB.lib +D13LIB.obj
```
To build your program, replace MAIN.C with your file, then run:
```
tcc -IC:\TC\INCLUDE -LC:\TC\LIB -ml MAIN.C D13LIB.lib
```
## Contributing

Contributions are always welcome!

If possible, I'd like for you to do all of your programming and development in DOS. That's my challenge for this project. 

If you have a DOS PC, testing is greatly appreciated! 
