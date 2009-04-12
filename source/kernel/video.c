/*
Main video/console API
Contains functions for directly working with the video/console
*/
#include "video.h" 
#include "memory.h"

// Active console attributes
int _console_attrib = 0x0F;

// Current cursor positions
int _console_x = 0;
int _console_y = 0;

// The global video memory pointer
unsigned short *_videomem = (unsigned short *)0xb8000;

//! Scrolls the console if it needs to be scrolled.
void ConsoleScroll(void)
{
	unsigned short blank;
	unsigned short temp;
	blank = 0x20 | (_console_attrib << 8); // space with current attributes

	if (_console_y >= 25)
	{
		temp = _console_y - 25 + 1;
		_memcpy(_videomem, _videomem + temp * 80, (25 - temp) * 80 * 2);
		_memsetw (_videomem + (25 - temp) * 80, blank, 80);
		_console_y = 24;
	}
}

//! Updates the hardware cursor
void ConsoleUpdate(void)
{
	unsigned short temp;
	temp = _console_y * 80 + _console_x; // get last position

	// Sends command to the VGA port.
	_outportb(0x3D4, 14);
	_outportb(0x3D5, temp >> 8);
	_outportb(0x3D4, 15);
	_outportb(0x3D5, temp);
}

//! Clears the console using the current attribute.
void ConsoleCls(void)
{
	unsigned short blank = 0x20 | (_console_attrib << 8); // space character
	_memsetw(_videomem, blank, 25 * 80); // set all characters to space.
	_console_x = 0;
	_console_y = 0;
	ConsoleUpdate(); // reset cursor position
}

//! Prints a character to the console using current text attributes
void ConsolePutch(unsigned char c)
{
	if (c == 0x80) { // backspace
		if (_console_x != 0) _console_x--;
	} else if (c == 0x09) { // tab
		_console_x = (_console_x + 8) & ~(8 - 1);
	} else if (c == '\r') { // carriage return
		_console_x = 0;
	} else if (c == '\n') { // new line / line feed
		_console_x = 0;
		_console_y++;
	} else if (c >= ' ') { // normal character
		unsigned short *where = _videomem + (_console_y * 80 + _console_x);
		*where = c | (_console_attrib << 8);
		_console_x++;
	}
	if (_console_x >= 80)
	{
		_console_x = 0;
		_console_y++;
	}

	// update scroll and console
	ConsoleScroll();
	ConsoleUpdate();
}

//! Prints a string to the console using current text attributes
void ConsolePuts(const char *str)
{
	while (*str != 0) {
		ConsolePutch(*str);
		str++;
	}
}

//! Sets the text attributes for the console
void ConsoleSetcolor(unsigned char fore, unsigned char back)
{
	_console_attrib = (back << 4) | (fore & 0x0F);
}
