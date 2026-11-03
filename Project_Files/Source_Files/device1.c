#include"lcd.h"
#include"lcd_defines.h"
#include"defines.h"
#include"delay.h"
#include<LPC21xx.h>
#define OP1 24
int flag;
void motor_open(void)
{
	int  k,l;
	flag=1;
	WNIBBLE(IODIR1,OP1,15);
	CmdLCD(0x01);
	StrLCD("DOOR OPENING....");

	delay_ms(5000);
	for(k=0;k<5;k++)
	{
			IOPIN1^=1<<24;
			delay_ms(1000);	
		
	}
	CmdLCD(0x01);

	StrLCD("DOOR OPENED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("Press Sw to close");
}

void motor_close(void)
{

	int k,l;
	flag=0;
	CmdLCD(0X01);

	StrLCD("DOOR CLOSEING..");

	delay_ms(5000);
	for(k=0;k<5;k++)
	{
			IOPIN1^=1<<24;
			delay_ms(1000);	
	}
	CmdLCD(0x01);

	StrLCD("DOOR CLOSED");

	delay_ms(500);

}

