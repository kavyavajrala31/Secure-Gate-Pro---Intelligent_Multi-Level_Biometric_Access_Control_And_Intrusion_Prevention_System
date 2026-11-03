//kpm.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "kpm_defines.h"
u32 kpmLUT[4][4]=
{
	{0,1,2,3},
	{4,5,6,7},
	{8,9,10,11},
	{12,13,14,15}
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
u32 KeyScan(void)
{
	u32 rNo,cNo;
  //wait to detect any key press
	while(ColScan());
	//if any key pressed was detected & 
	//while key is in pressed state
	//proceed to identify row in which key was 
	//pressed
	rNo=RowCheck();
	//proceed to identify col in which key was
	//presed
	cNo=ColCheck();
	//extract key value from LUT for key pressed
	return kpmLUT[rNo][cNo];
}
