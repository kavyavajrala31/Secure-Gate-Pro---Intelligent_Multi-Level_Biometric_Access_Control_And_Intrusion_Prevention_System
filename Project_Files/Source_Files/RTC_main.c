#include<LPC21xx.h>
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "defines.h"
#include "RTC.h"
#define SW 4
#include<stdlib.h>
#include<stdio.h>
int main()
{
	RTC_Init();
	Date_Init();
	Init_KPM();
	InitLCD();
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	while(1)
	{
		while(1)
		{

			display_main();
			if(((IOPIN0>>SW)&1)==0)
			{
				while(!((IOPIN0>>SW)&1));

				break;
			}
		}
		while(1)
		{
			display_menu();

			//while(((IOPIN0>>SW)&1));
			break;
		}
	}

}
