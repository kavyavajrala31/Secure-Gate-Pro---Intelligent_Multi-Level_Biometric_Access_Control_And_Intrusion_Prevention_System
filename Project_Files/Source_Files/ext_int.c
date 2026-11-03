                 /* external_interrupt_test.c */
#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"
#include "ext_int.h"
#include "lcd.h"
#include"lcd_defines.h"
#include"kpm.h"
#include "spi_eeprom.h"
#include "delay.h"
#include "uart0.h"
#include "R305.h" 
#include "spi.h"
#include<string.h>

unsigned char a;


void Enable_EINT2(void)
{
	CFGPIN(PINSEL0,7,FUNC4);
	PINSEL0|=0x0000C000;
	SSETBIT(VICIntEnable,16);
	VICVectCntl1=0x20|16;
	VICVectAddr1=(unsigned)eint2_isr;
	
	//Enable EINT1 
	//SCLRBIT(EXTINT,0) //default
	//EXTINT=1<<0;
	//EXTMODE=1<<0;
	//EINT1 as EDGE_TRIG
  SETBIT(EXTMODE,2);
	//EINT1 as REDGE
  CLRBIT(EXTPOLAR,2);	
}	

void eint2_isr(void) __irq
{
	a=1;
	SCLRBIT(EXTINT,2);//clear flag
	VICVectAddr=0;
	/*InitUART0();
	a='1';
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("MENU: ");
	StrLCD("1)Edit pass");
	CmdLCD(GOTO_LINE2_POS0+6);
	StrLCD("2)Edit FP");
	//choose=KeyScan();
	//while(ColScan());
	if(KeyScan()=='1')
	{
		edit_pass();
	}	
	if(KeyScan()=='2')
	{
		edit_fp();
	}
	SCLRBIT(EXTINT,1);//clear flag
	VICVectAddr=0;//dummy write;
	  */
	//delay_ms(50);
}	

