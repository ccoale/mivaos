#ifndef __TIMER_H
#define __TIMER_H
#include "memory.h"
#include "irq.h"

//! Structure which holds a date and time
struct DATE_TIME
{
	BYTE sec;
	BYTE min;
	BYTE hour;
	
	BYTE day;
	BYTE month;
	BYTE year;
};

//! Installs the timer.. (hz = number clocks per second)
//! This also installs the cmos timer
void TimerInstall(int hz);

//! Gets the current "tick count"
DWORD TimerGetTicks();

//! Gets the current time!
struct DATE_TIME* TimerGetTime(struct DATE_TIME *tm);

BYTE TimerGetYear();

#endif /* __TIMER_H */
