#include "defines.h"
//uart.c
#include <LPC21xx.h>
#include "types.h"
#include "uart_defines.h"

void Init_UART1(void)
{
	//cfg p1.8& p1.9 as txd0& rxd0 respectively
	PINSEL0|=0x00050000;
	//cfg uart for 8N1,& activate DLAB bit
	U1LCR=1<<DLAB_BIT|WORD_LEN_SEL;
	//cfg baudrate 
	U1DLL=LOADVAL;
	U1DLM=LOADVAL>>8;
	//deactivate DLAB bit;
	CLRBIT(U1LCR,DLAB_BIT);
	
}

void U1_TxChar(u8 sByte)
{
	//place byte to transmitted into THR sfr
	U1THR=sByte;
	//wait until transmitter empty status
	while(READBIT(U1LSR,TEMT_BIT)==0);	
}	

u8 U1_RxChar(void)
{
	//wait until data recvd status
	while(READBIT(U1LSR,DR_BIT)==0);
	//read & return recv data
	return U1RBR;
}

void U1_TxStr(s8 *s)
{
	while(*s)
		U1_TxChar(*s++);
}

void U1_TxU32(u32 n)
{
	s32 i=0;
	u8 a[10];
	if(n==0)
	{
		U1_TxChar('0');
	}
  else
  {
		while(n!=0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			U1_TxChar(a[i]);
		}
  }		
}

void U1_TxS32(s32 n)
{
	if(n<0)
	{
		U1_TxChar('-');
		n=-n;
	}
	U1_TxU32(n);
}

void U1_TxF32(f32 f,u32 nDP)
{
	u32 n,i;
	if(f<0.0)
	{
		U1_TxChar('-');
		f=-f;
	}
	n=f;
	U1_TxU32(n);
	U1_TxChar('.');
	for(i=0;i<nDP;i++)
	{
		f=(f-n)*10;
		n=f;
		U1_TxChar(n+48);
	}		
}

s8 * U1_RxStr(void)
{
	static s8 s[100];
	s32 i=0;
	while(1)
	{
		s[i]=U1_RxChar();
		U1_TxChar(s[i]);
		if((s[i]=='\n')||(s[i]=='\r'))
		{
			s[i]='\0';
			break;
		}
		i++;
	}
	return s;
}
