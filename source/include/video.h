#ifndef __VIDEO_H
#define __VIDEO_H
/*
video API header
*/
#define VIDEO_BASE 0xb8000 //the location in memory where our video buffer starts

//whatPx
//returns the element in the node where the specified pixil is
//should be added to the VIDEO_ADDR to get the exact location in memory
int whatPx(int x, int y);
//cls:
//will clear the screen
void cls();
#endif