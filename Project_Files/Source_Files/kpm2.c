//kpm2.c

#include <LPC21xx.h>

#include "types.h"

#include "defines.h"
#include"delay.h"

#include "kpm_defines.h"
#include "kpm.h"

#include "lcd.h"
#include "lcd_defines.h"

u8 kpmLUT[4][4]=

{

	{'1','2','3','A'},

	{'4','5','6','B'},

	{'7','8','9','C'},

	{'*','0','=','D'}

};

u32 ColScan(void)

{

	u32 t;

	t=(READNIBBLE(IOPIN1,COL0) < 15) ? 0 : 1;

	return t;

}


u32 RowCheck(void)

{

	u32 rNo;

	for(rNo=0;rNo<4;rNo++)

	{

		//grounding 0th to 3rd row iterative

    WRITENIBBLE(IOPIN1,ROW0,~(1<<rNo));	

    if(ColScan()==0)

       break;			

	}

	WRITENIBBLE(IOPIN1,ROW0,0);

	return rNo;

}


u32 ColCheck(void)

{

	u32 cNo;

	for(cNo=0;cNo<=3;cNo++)

	{

		if(READBIT(IOPIN1,COL0+cNo)==0) 

       break;			

	}

	return cNo;

}


void Init_KPM(void)

{

	WRITENIBBLE(IODIR1,ROW0,15);

	//ground all rows

	

	//let all columns be high

	//default column lines are input high

}


u8 KeyScan(void)

{

	u32 rNo,cNo;

  //wait to detect any key press

	while(ColScan()==1);

	//if any key pressed was detected & 

	//while key is in pressed state

	//proceed to identify row in which key was 

	//pressed

	rNo=RowCheck();

	//proceed to identify col in which key was

	//presed

	cNo=ColCheck();
	delay_ms(100);
	//extract key value from LUT for key pressed

	return kpmLUT[rNo][cNo];

}


void Read(u8 *val)
{
	u8 keyV;
	u32 i=0;
	while(1)								  
	{
		keyV=KeyScan();
		while(ColScan()==0);
		
		if(keyV>='0' && keyV<='9')
		{
			CmdLCD(0xc0+i);
			CharLCD(keyV);
			delay_ms(200);
			CmdLCD(0xc0+i);
			CharLCD('*');
			val[i++]=keyV;
		
		}
		else if(keyV=='B')
		{
		 	i--;
			//CmdLCD(GOTO_LINE2_POS0+i);
			CmdLCD(0x10);
			CharLCD(' ');
			CmdLCD(0x10);
			//StrLCD("                ");
			//CmdLCD(GOTO_LINE2_POS0);
			//StrLCD(val);
		}
		else if(keyV=='D')
		{
		 	val[i]='\0';
			break;
		}
	}
	 	//return val;
}
u32 ReadNum(void)
{
	u8 keyV;
	u32 sum=0;
	while(1)
	{
		keyV=KeyScan();
		while(ColScan()==0);
		delay_ms(100);
		if(keyV>='0' && keyV<='9')
		{
			CharLCD(keyV);
			sum=(sum*10)+(keyV-48);
		}
		else if(keyV=='B')
		{
			sum/=10; 
			CmdLCD(0x10);
			CharLCD(' ');
			CmdLCD(0x10);
		}
		else if(keyV=='D')
		{
		 break;
		}
		
	}
	return sum;
	
}




