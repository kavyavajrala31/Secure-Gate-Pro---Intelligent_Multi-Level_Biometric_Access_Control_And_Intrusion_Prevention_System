#include <lpc21xx.h>

#include "types.h"
#ifndef __TIMER_H__
#define	__TIMER_H__
void InitTimer0(void);
void tdelay_us(u32 microseconds);
void tdelay_ms(u32 milliseconds);
void tdelay_s(u32 seconds);
#endif
