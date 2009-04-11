#ifndef __VIDEO_H
#define __VIDEO_H
/*
video API header
*/
#define VIDEO_BASE 0xb8000 //the location in memory where our video buffer starts

//whatPx
//returns the element in the node where the specified pixil is
//should be added to the VIDEO_ADDR to get the exact location in memory
#define whatPx(x,y)((y*80)+x)
//offsetPx
//Returns the exact location in memory where the pixil can be changed
//adds the element from whatPx, then adds the base address
#define offsetPx(x,y)(whatPx(x,y)+VIDEO_BASE)
//cls:
//will clear the screen
void cls();
#endif