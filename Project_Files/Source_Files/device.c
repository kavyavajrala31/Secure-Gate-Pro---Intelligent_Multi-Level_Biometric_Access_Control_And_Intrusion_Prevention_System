#include"lcd.h"
#include"lcd_defines.h"
#include"defines.h"
#include"delay.h"
#include<LPC21xx.h>
#define OP1 24
#define OP2 25			   
#define EN1_2 28
//int flag;
void motor_open(void)

{

	//flag=1;
	WNIBBLE(IODIR1,OP1,15);

	SETBIT(IOPIN1,EN1_2);

	CmdLCD(0x01);

	StrLCD("DOOR OPENING....");

	delay_ms(1000);

	SETBIT(IOPIN1,OP2);

	CLRBIT(IOPIN1,OP1);

	delay_ms(1000);

	CLRBIT(IOPIN1,OP1);

	CLRBIT(IOPIN1,OP2);

	CmdLCD(0x01);

	StrLCD("DOOR OPENED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("PRESS SW TO CLOSE");
}

void motor_close(void)
{

	//flag=0;
	CmdLCD(0X01);

	StrLCD("DOOR CLOSING..");

	delay_ms(1000);

	SETBIT(IOPIN1,OP1);

	CLRBIT(IOPIN1,OP2);

	delay_ms(1000);

	CLRBIT(IOPIN1,OP1);

	CLRBIT(IOPIN1,OP2);

	CmdLCD(0x01);

	StrLCD("DOOR CLOSED");

	delay_ms(500);

}

