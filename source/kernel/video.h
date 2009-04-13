/*
** Provides basic functionality for outputting text to the console.
**
*/
#ifndef __VIDEO_H
#define __VIDEO_H

// Console Colors
#define COLOR_BLACK 	0x00
#define COLOR_BLUE 	0x10
#define COLOR_GREEN 	0x20
#define COLOR_CYAN 	0x30
#define COLOR_RED 	0x40
#define COLOR_MAGENTA 	0x50
#define COLOR_BROWN	0x60
#define COLOR_LGREY 	0x70
#define COLOR_DGREY 	0x80
#define COLOR_LBLUE 	0x90
#define COLOR_LGREEN 	0xA0
#define COLOR_LCYAN 	0xB0
#define COLOR_LRED 	0xC0
#define COLOR_LMAGENTA 	0xD0
#define COLOR_LBROWN 	0xE0
#define COLOR_WHITE 	0xF0

//! Scrolls the console by 1 row
void ConsoleScroll(void);

//! Updates the hardware cursor
void ConsoleUpdate(void);

//! Clears the console using the current attributes
void ConsoleClear(void);

//! Prints a character to the console using current text attributes
void ConsolePutch(unsigned char c);

//! Prints a string to the console using current text attributes
void ConsolePuts(const char *str);

//! Sets the text attributes for the console
void ConsoleSetcolor(unsigned char fore, unsigned char back);

/* the integer D to a string and save the string in BUF. If
        BASE is equal to 'd', interpret that D is decimal, and if BASE is
        equal to 'x', interpret that D is hexadecimal. */
void kitoa (char *buf, int base, int d);

     /* Format a string and print it on the screen, just like the libc
        function printf. */
void kprintf (const char *format, ...);

#endif /* __VIDEO_H */

