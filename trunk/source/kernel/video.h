#ifndef __VIDEO_H
#define __VIDEO_H
#include "types.h"
/*
video API header
*/
#define VIDEO_BASE 0xb8000 //the location in memory where our video buffer starts
//our base colors
#define COL_BLACK 0x0000
#define COL_BLUE 0x0010
#define COL_GREEN 0x0020
#define COL_CYAN 0x0030
#define COL_RED 0x0040
#define COL_MAGENTA 0x0050
#define COL_BROWN0x0060
#define COL_LGREY 0x0070
#define COL_DGREY 0x0080
#define COL_LBLUE 0x0090
#define COL_LGREEN 0x00A0
#define COL_LCYAN 0x00B0
#define COL_LRED 0x00C0
#define COL_LMAGENTA 0x00D0
#define COL_LBROWN 0x00E0
#define COL_WHITE 0x00F0
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
#define makeDefChar(char)(char|((COL_BLACK<<4)|(COL_WHITE&0x0F))<<8)
//makeChar
//will return a short with the forground and background colors added in
#define makeChar(char,b,f)(char|((b<<4)|(f&0x0F))<<8)
//cls:
//will clear the screen
void cls();
#endif

