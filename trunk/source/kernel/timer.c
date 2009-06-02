/*
** Provides an API for timing.
**
*/
#include "timer.h"
#include "video.h"

//! Date and time string representations
static const char *g_szMonths[] =
{
	"January", "February", "March", "April", "May",
	"June", "July", "August", "September", "October",
	"November", "December"
};

static const char *g_szDays[] =
{
	"Monday", "Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday", "Sunday"
};

// The global "tick count".
DWORD _tick_count = 0;

#define BCD2BIN(bcd) ((((bcd)&15) + ((bcd)>>4)*10))

BYTE ReadCMOS(BYTE addr)
{
	BYTE ret;
	_outportb(0x70,addr);	
	__asm__ __volatile__ ("jmp 1f; 1: jmp 1f;1:");
	ret = _inportb(0x71);
	__asm__ __volatile__ ("jmp 1f; 1: jmp 1f;1:");
   
	return ret;
}

void WriteCMOS(BYTE addr, BYTE value)
{
	_outportb(0x70, addr);
	__asm__ __volatile__ ("jmp 1f; 1: jmp 1f;1:");
	_outportb(0x71, value);
	__asm__ __volatile__ ("jmp 1f; 1: jmp 1f;1:");
}

struct DATE_TIME* TimerGetTime(struct DATE_TIME *tm)
{
	if (tm == NULL) return NULL;

	tm->sec = BCD2BIN(ReadCMOS(0x00));
	tm->min = BCD2BIN(ReadCMOS(0x02));
	tm->hour = BCD2BIN(ReadCMOS(0x04));
	tm->day = BCD2BIN(ReadCMOS(0x07));
	tm->month = BCD2BIN(ReadCMOS(0x08));
	tm->year = BCD2BIN(ReadCMOS(0x09));

	return tm;
}


void TimerHandler(struct regs *r) 
{
	_tick_count++;
}

//! Installs the timer.. (hz = number clocks per second)
void TimerInstall(int hz)
{
//	ConsolePuts("Loading system timer...");
	// IRQ0 == timer
	IrqInstallHandler(0, TimerHandler);
	
	// set timer
	int div = 1193180 / hz;
	_outportb(0x43, 0x36); // command
	_outportb(0x40, div & 0xFF); // low byte of div
	_outportb(0x30, div >> 8); // hi byte of div
	
//	ConsolePuts(" success!\n");
}

//! Gets the current "tick count".
DWORD TimerGetTicks()
{
	return _tick_count;
}
