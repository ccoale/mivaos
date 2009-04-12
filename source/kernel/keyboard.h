/*
keyboard scancodes
Only supports US so far, more will be added.
*/
#ifndef __KEYBOARD_H
#define __KEYBOARD_H
#include "types.h"

#define SCANCODETOCHAR(code)(US_SC[code])
#define KEY_RELEASE 0x80

void KeyboardInstall();
#endif
