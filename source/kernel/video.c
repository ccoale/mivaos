/*
Main video API
Contains functions for directly working with the video
*/
#include "video.h" 
int whatPx(int x, int y) 
{ 
return (y*80)+x; 
} 
void cls() 
{ 
unsigned short filler=(0x20|(0x0f<<8)); 
int x=0; 
int y=0; 
//we run two nested loops 
//this is the easiest solution for now: 
for (y=0;y<25;y++) 
{ 
for (x=0;x<80;x++) 
{ 
*(unsigned char*)(whatPx(x,y)+VIDEO_BASE)=filler; 
} 
} 
}  
