#include <lpc21xx.h>

#include "timer_defines.h"

#include "types.h"


void InitTimer0(void)

{

  T0TCR = TIMER0_RST;              //Reset Timer          

  T0MCR = TIMER0_STOP_ON_MR0;//stop Timer Counter upon match

}


void tdelay_us(u32 microseconds) //Using Timer0

{

	T0MR0=microseconds;

	T0PR = 15-1; //PCLK/15=15MHz/15=1MHz,so T0TC increments every 1us	

	T0TC = 0;

	T0TCR = TIMER0_ENABLE; //Enable timer

	while(T0TC!=T0MR0); //wait until timer attains desired delay

}

void tdelay_ms(u32 milliseconds) //Using Timer0

{

	T0MR0=milliseconds;

	T0PR = 15000-1; //PCLK/15000,15MHz/15000=1KHz=1000Hz, so T0TC increments every 1000us/1ms                           

	T0TC = 0;

	T0TCR = TIMER0_ENABLE; //Enable timer

	while(T0TC!=T0MR0); //wait until timer counter reaches the desired delay

}

void tdelay_s(u32 seconds) //Using Timer0

{

	T0MR0=seconds;

	T0PR = 15000000-1; //PCLK/15000000,15MHz/15000000=1Hz, so T0TC increments every 1000ms/1s         

	T0TC = 0;

	T0TCR = TIMER0_ENABLE; //Enable timer

	while(T0TC!=T0MR0); //wait until timer counter reaches the desired delay

}




