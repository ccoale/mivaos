#include "keyboard.h"
#include "irq.h"
#include "video.h"
#include "memory.h"

#define SCANCODETOCHAR(x) ( (US_SC[x]) )

BYTE g_nKeyStates[256] = {0};

BYTE US_SC[128]=
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',				/* Backspace */
  '\t',							/* Tab */
  'q', 'w', 'e', 'r',					/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,							/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,					/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,							/* Alt */
  ' ',							/* Space bar */
    0,							/* Caps lock */
    0,							/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,							/* < ... F10 */
    0,							/* 69 - Num lock*/
    0,							/* Scroll Lock */
    0,							/* Home key */
    0,							/* Up Arrow */
    0,							/* Page Up */
  '-',
    0,							/* Left Arrow */
    0,
    0,							/* Right Arrow */
  '+',
    0,							/* 79 - End key*/
    0,							/* Down Arrow */
    0,							/* Page Down */
    0,							/* Insert Key */
    0,							/* Delete Key */
    0,   0,   0,
    0,							/* F11 Key */
    0,							/* F12 Key */
    0,							/* All other keys are undefined */
};

void KeyboardHandler(struct regs *r)
{
	BYTE sc = _inportb(0x60);
	if ((sc & 0x80))
	{
		g_nKeyStates[sc & ~0x80] = 0;
	}
	else
	{
		g_nKeyStates[sc] = 1;
	}
}

void KeyboardInstall()
{
	ConsolePuts("Registering Keyboard.\n");
	IrqInstallHandler(1,KeyboardHandler);
}

//! Returns the state of the specified scan code.
UINT GetKeyState(UINT key)
{
	return g_nKeyStates[key];
}

//! Returns the state of the every key in a 256-byte buffer.
void GetKeyboardState(BYTE *buff)
{
	// copy the keyboard state buffer...
	_memcpy((void *)buff, (void *)&g_nKeyStates, 256);
}
