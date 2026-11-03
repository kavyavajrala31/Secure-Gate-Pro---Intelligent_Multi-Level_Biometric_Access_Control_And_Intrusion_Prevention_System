//uart_rx_test.c
#include "uart.h"
#include "types.h"
#include <LPC21xx.h>
#include "defines.h"
#define LED 16//p1.16
u8 rByte __attribute__((at(0x40000010)));
main()
{
	Init_UART0();
	SETBIT(IODIR1,LED);
	while(1)
	{
		rByte=U0_RxChar();
		if(rByte=='A')
			CPLBIT(IOPIN1,LED);
	}
}
