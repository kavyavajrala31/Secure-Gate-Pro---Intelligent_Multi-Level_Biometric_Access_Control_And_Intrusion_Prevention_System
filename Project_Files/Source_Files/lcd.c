//lcd.c
#include "defines.h"
#include "delay.h"
#include "types.h"
#include "lcd_defines.h"
#include "lcd.h"
#include <LPC21xx.h>

void writeLCD(u8 Data)
{
	WRITEBYTE(IOPIN0,LCD_DATA,Data);
	SSETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN);
	delay_ms(2);
}

void CmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,LCD_RS);
	writeLCD(cmd);
}

void CharLCD(u8 asciival)
{
	SSETBIT(IOSET0,LCD_RS);
	writeLCD(asciival);
}

void InitLCD(void)
{
	IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_EN));
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(5);
	CmdLCD(0x30);
	delay_ms(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}

void StrLCD(u8 *p)
{
	while(*p)
		CharLCD(*p++);
}

void u32LCD(u32 data)
{
	s32 i=0;
	u8 a[10];
	if(data == 0)
		CharLCD('0');
	else
	{
		while(data!=0)
		{
			a[i++]=(data%10+48);
			data/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}
	}
}

void s32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	u32LCD(n);
}

void f32LCD(f32 n,u32 nDP)
{
	u32 data,i;
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	data=n;
	u32LCD(data);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		n=(n-data)*10;
		data=n;
		CharLCD(data+48);
	}
}

void HexLCD(u32 n)
{
	s32 i=0;
	u8 a[8],t;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n!=0)
		{
			t=(n%16);
			t=((t>9)?((t-10)+'A'):(t+48));
			a[i++]=t;
			n/=16;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}
	}
}


void BuildCGRAM(u8 *p,u32 nBytes)
{
	s32 i;
	CmdLCD(GOTO_CGRAM_START);
	for(i=0;i<nBytes;i++)
	{
		CharLCD(p[i]);
	}
	CmdLCD(GOTO_LINE1_POS0);
}
