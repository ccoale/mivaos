/*
** Provides an API for timing.
**
*/
#include "timer.h"
#include "video.h"

// The global "tick count".
DWORD _tick_count = 0;

void TimerHandler(struct regs *r) 
{
	_tick_count++;
}

//! Installs the timer.. (hz = number clocks per second)
void TimerInstall(int hz)
{
ConsolePuts("Registering timer.\n");
	// IRQ0 == timer
	IrqInstallHandler(0, TimerHandler);
	
	// set timer
	int div = 1193180 / hz;
	_outportb(0x43, 0x36); // command
	_outportb(0x40, div & 0xFF); // low byte of div
	_outportb(0x30, div >> 8); // hi byte of div
}

//! Gets the current "tick count".
DWORD GetTickCount()
{
	return _tick_count;
}
