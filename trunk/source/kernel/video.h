#ifndef __VIDEO_H
#define __VIDEO_H
#include "types.h"
/*
video API header
*/
#define VIDEO_BASE 0xb8000 //the location in memory where our video buffer starts
//our base colors
//defined so we can and them with our character
//background colors:
#define B_BLACK 0x0000
#define B_BLUE 0x0010
#define B_GREEN 0x0020
#define B_CYAN 0x0030
#define B_RED 0x0040
#define B_MAGENTA 0x0050
#define B_BROWN0x0060
#define B_LGREY 0x0070
#define B_DGREY 0x0080
#define B_LBLUE 0x0090
#define B_LGREEN 0x00A0
#define B_LCYAN 0x00B0
#define B_LRED 0x00C0
#define B_LMAGENTA 0x00D0
#define B_LBROWN 0x00E0
#define B_WHITE 0x00F0
//foreground colors:
#define F_BLACK 0x0000
#define F_BLUE 0x0001
#define F_GREEN 0x0002
#define F_CYAN 0x0003
#define F_RED 0x0004
#define F_MAGENTA 0x0005
#define F_BROWN0x0006
#define F_LGREY 0x0007
#define F_DGREY 0x0008
#define F_LBLUE 0x0009
#define F_LGREEN 0x000A
#define F_LCYAN 0x000B
#define F_LRED 0x000C
#define F_LMAGENTA 0x000D
#define F_LBROWN 0x000E
#define F_WHITE 0x000F

//whatPx
//returns the element in the node where the specified pixil is
//should be added to the VIDEO_ADDR to get the exact location in memory
#define whatPx(x,y)((y*80)+x)
//offsetPx
//Returns the exact location in memory where the pixil can be changed
//adds the element from whatPx, then adds the base address
#define offsetPx(x,y)(whatPx(x,y)+VIDEO_BASE)
//makeDefChar
//will return a short with the char ready to print, with black on white.
#define makeDefChar(char)(char|((B_BLACK<<4)|(F_WHITE&0x0F))<<8)
//makeChar
//will return a short with the forground and background colors added in
#define makeChar(char,b,f)(((BYTE)char&b)&f)
//cls:
//will clear the screen
void cls();
#endif