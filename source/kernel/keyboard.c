#include "keyboard.h"
#include "irq.h"
#include "video.h"
#include "memory.h"

#define SCANCODETOCHAR(x) ( (US_SC[x]) )

BYTE g_nKeyStates[256] = {0};

BYTE US_SC[256]=
{
	// NULL, KEY_ESCAPE
	0, 0,

	// KEY_1 through KEY_0
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',

	// KEY_MINUS, KEY_EQUALS, KEY_BACK, KEY_TAB
	'-', '=', '\b', '\t',

	// KEY_(qwertyuiop), KEY_LBRACKET
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',

	// KEY_RBRACKET, KEY_RETURN, KEY_LCONTROL, KEY_(asdfghj)
	']','\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',

	// KEY_(kl), KEY_SEMICOLON, KEY_APOSTROPHE, KEY_GRAVE, KEY_LSHIFT, KEY_BACKSLASH
	'k', 'l',';', '\'', '`', 0, '\\', 

	// KEY_(zxcvbnm), KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RSHIFT
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,

	// KEY_MULTIPLY, KEY_LMENU(LALT), KEY_SPACE, KEY_CAPITAL, KEY_F1 - KEY_F10
	'*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	// KEY_NUMLOCK, KEY_SCROLL, KEY_NUMPAD7 - KEY_NUMPAD9, KEY_SUBTRACT, KEY_NUMPAD4 - KEY_NUMPAD6
	0, 0, '7', '8', '9', '-', '4', '5', '6', 

	// KEY_ADD, KEY_NUMPAD1 - KEY_NUMPAD3, KEY_NUMPAD0, KEY_DECIMAL, KEY_OEM_102
	'+', '1', '2', '3', '0', '.', 0, 

	// KEY_F11 - KEY_F15, KEY_KANA (JAP), KEY_ABNT_C1, KEY_CONVERT, KEY_NOCONVERT
	0, 0, 0, 0, 0, 0, 0, 0, 0,

	// KEY_YEN, KEY_ABNT_C2, KEY_NUMPADEQUALS, KEY_PREVTRACK, KEY_AT, KEY_COLON
	0, 0, '=', 0, '@', ':', 

	// KEY_UNDERLINE, KEY_KANJI, KEY_STOP, KEY_AX, KEY_UNLABELED	
	'_', 0, 0, 0, 0,

	// KEY_NEXTTRACK, KEY_NUMPADENTER, KEY_RCONTROL, KEY_MUTE, KEY_CALCULATOR
	0, '\n', 0, 0, 0, 

	// KEY_PLAYPAUSE, KEY_MEDIASTOP, KEY_VOLUMEDOWN, KEY_VOLUMEUP, KEY_WEBHOME, KEY_NUMPADCOMMA
	0, 0, 0, 0, 0, ',',

	// KEY_DIVIDE, KEY_SYSRQ, KEY_RMENU, KEY_PAUSE, KEY_HOME, KEY_UP, KEY_PRIOR
	'/', 0, 0, 0, 0, 0, 0, 

	// KEY_LEFT, KEY_RIGHT, KEY_END, KEY_DOWN, KEY_NEXT
	0, 0, 0, 0, 0,

	// KEY_INSERT, KEY_DELETE, KEY_LWIN, KEY_RWIN, KEY_APPS, KEY_POWER, KEY_SLEEP 
	0, 0, 0, 0, 0, 0, 0, 

	// KEY_WAKE, KEY_WEBSEARCH, KEY_WEBFAVORITES, KEY_WEBREFRESH, KEY_WEBSTOP, KEY_WEBFORWARD
	0, 0, 0, 0, 0, 0,

	// KEY_WEBBACK, KEY_MYCOMPUTER, KEY_MAIL, KEY_MEDIASELECT
	0, 0, 0, 0
};

volatile BYTE LastChar=NULL;

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
if ((g_nKeyStates[KEY_LWIN])||(g_nKeyStates[KEY_RWIN])) ConsolePuts("Windows? WTF do you think this is!\n");
	}
}

//! Returns the state of the specified scan code.
BOOL GetKeyState(UINT key)
{
	return g_nKeyStates[key];
}

//! Returns the state of the every key in a 256-byte buffer.
void GetKeyboardState(BYTE *buff)
{
	// copy the keyboard state buffer...
	_memcpy((void *)buff, (void *)&g_nKeyStates, 256);
}

//scancode translation:
BYTE TranslateScancode(UINT code)
{
	BYTE sc = code;
	int asc = US_SC[(int)sc];
	if ( (g_nKeyStates[KEY_LSHIFT]) || (g_nKeyStates[KEY_RSHIFT]) )
	{
		if ((asc>=97)&&(asc<=122))
		{
			return asc - 32;
		}
		else
		{
			switch(asc)
			{
				case '0':
					asc = ')';
					break;
				case '1':
					asc = '!';
					break;
				case '2':
					asc = '@';
					break;
				case '3':
					asc = '#';
					break;
				case '4':
					asc = '$';
					break;
				case '5':
					asc = '%';
					break;
				case '6':
					asc = '^';
					break;
				case '7':
					asc = '&';
					break;
				case '8':
					asc = '*';
					break;
				case '9':
					asc = '(';
					break;
				case '-':
					asc = '_';
					break;
				case '=':
					asc = '+';
					break;
				case '`':
					asc = '~';
					break;
				case ',':
					asc = '<';
					break;
				case '.':
					asc = '>';
					break;
				case '/':
					asc = '?';
					break;
				case '\'':
					asc = '"';
					break;
				case ';':
					asc = ':';
					break;
				case '[':
					asc = '{';
					break;
				case ']':
					asc = '}';
					break;
				case '\\':
					asc = '|';
					break;
			}

			return asc;
		}
	}

	return (BYTE)asc;
}

void KeyboardInstall()
{
//	ConsolePuts("Loading default keyboard driver...");
	IrqInstallHandler(1,KeyboardHandler);
//	ConsolePuts(" success!\n");
}
