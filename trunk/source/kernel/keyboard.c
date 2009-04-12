#include "keyboard.h"
#include "irq.h"
#include "video.h"
#include "memory.h"

#define SCANCODETOCHAR(x) ( (US_SC[x]) )

BYTE g_nKeyStates[256] = {0};

BYTE US_SC[237]=
{
0,'1','2','3','4','5','6','7','8','9','0','-','\b',
'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
0,'a','s','d','f','g','h','j','k','l',';''\'','`',0,'\\',
'z','x','c','v','b','n','m',',','.','/',0,
'*',0,' ',
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,
0,0,0,0
0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,':','_',0,
0,0,0,0,0,0,0,0,0,0,0,0,0,','''/',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,'\b'
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
	}
}

//! Returns the state of the specified scan code.
BOOLGetKeyState(UINT key)
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
BYTE TranslateScanCode(UINT code)
{
BYTE sc=NULL;
int asc=0;
if ((g_nKeyStates[KEY_LSHIFT])||(g_nKeyStates[KEY_RSHIFT]))
{
asc=(int)sc;
if ((asc>=97)&&(asc<=122))
{
asc-=32;
}
switch(asc)
{
case 35:
case 36:
case 37:
case 38:
asc+=16;
break;
case 49:
asc=33;
break;
case 50:
asc=64;
break;
case 55:
asc=94;
break;
case 56:
asc=42;
break;
case 57:
asc=40;
break;
case 48:
asc=41;
break;
case 59:
asc=58;
break;
case 91:
case 92:
case 93:
asc+=32;
break;
}
return (BYTE)asc;
}

void KeyboardInstall()
{
	ConsolePuts("Registering Keyboard.\n");
	IrqInstallHandler(1,KeyboardHandler);
}