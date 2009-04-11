/*
Main video API
Contains functions for directly working with the video
*/
#include "types.h"
#include "video.h" 
#include "memory.h"
void cls() 
{ 
unsigned short filler=(0x20|(0x0f<<8)); 
int x=0; 
int y=0; 
//we run two nested loops 
//this is the easiest solution for now: 
for (y=0;y<25;y++) 
{ 
memSet((void*)offsetPx(0,y),filler,80);
} 
}  
