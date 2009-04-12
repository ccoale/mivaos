#ifndef __TIMER_H
#define __TIMER_H
#include "memory.h"
#include "irq.h"

//! Installs the timer.. (hz = number clocks per second)
void timer_install(int hz);

//! Gets the current "tick count"
DWORD GetTickCount();

#endif /* __TIMER_H */
