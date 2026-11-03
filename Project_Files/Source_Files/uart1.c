//uart1.c
#include <LPC21xx.H>  /* LPC21xx definitions         */

#include "uart1.h"
#include "lcd.h"
#include "lcd_defines.h"
char rec_buff[25],dummy;
unsigned char i=0,ch,r_flag;

extern unsigned char buf[25]; 

void UART1_isr(void) __irq
{
  /*CmdLCD(CLEAR_LCD);
  CmdLCD(GOTO_LINE1_POS0);
  StrLCD("uart");*/
  if((U1IIR & 0x04)) //check if receive interrupt
  {
		//StrLCD()
		ch = U1RBR;	/* Read to Clear Receive Interrupt */
		if(i<25)
			rec_buff[i++] = ch; 
  }
  else
  {
      dummy=U1IIR; //Read to Clear transmit interrupt
  
  }
   VICVectAddr = 0; /* dummy write */
}

void InitUART1 (void) /* Initialize Serial Interface       */ 
{  
            		
  PINSEL0 |= 0x00050000; /* Enable RxD0 and TxD0              */
  U1LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit     */
  U1DLL = DIVISOR;           /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
  U1DLM = DIVISOR>>8;
  U1LCR = 0x03;         /* DLAB = 0  */
  
  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)UART1_isr;
  VICVectCntl0 = 0x20 | 7; /* UART0 Interrupt */
  VICIntEnable = 1 << 7;   /* Enable UART0 Interrupt */
 
  U1IER = 0x03;       /* Enable UART1  RX and THRE Interrupts */   
             
  #endif
						
}

void UART1_Tx(char ch)  /* Write character to Serial Port    */  
{ 
  while (!(U1LSR & 0x20));
  U1THR = ch;                
}

char UART1_Rx(void)    /* Read character from Serial Port   */
{                     
  while (!(U1LSR & 0x01));
  return (U1RBR);
}

void UART1_Str(char *s)
{
   while(*s)
       UART1_Tx(*s++);
}

void UART1_Str1(unsigned char n)
{
 	unsigned char j;   
    for(j=0;j<n;j++)
    {
        UART1_Tx(buf[j]);
    }   
}

void UART1_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART1_Tx('0');
		return;
  }
  else
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   UART1_Tx(a[i]);
	 }
   }
}

void UART1_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART1_Int(x);
  UART1_Tx('.');
  temp=(f-x)*100;
  x=temp;
  UART1_Int(x);
}


								




/*//uart0.c
#include "defines.h"
//uar  t.c
#include <LPC21xx.h>
#include "types.h"
#include "uart_defines.h"

static u32 log_count=1;

void Init_UART0(void)
{
	//cfg p0.1& p0.2 as txd0& rxd0 respectively
	PINSEL0|=0x0000005;
	//cfg uart for 8N1,& activate DLAB bit
	U0LCR=1<<DLAB_BIT|WORD_LEN_SEL;
	//cfg baudrate 
	U0DLL=LOADVAL;
	U0DLM=LOADVAL>>8;
	//deactivate DLAB bit;
	CLRBIT(U0LCR,DLAB_BIT);
	
}

void U0_TxChar(u8 sByte)
{
	//place byte to transmitted into THR sfr
	U0THR=sByte;
	//wait until transmitter empty status
	while(READBIT(U0LSR,TEMT_BIT)==0);	
}	

u8 U0_RxChar(void)
{
	//wait until data recvd status
	while(READBIT(U0LSR,DR_BIT)==0);
	//read & return recv data
	return U0RBR;
}

void U0_TxStr(s8 *s)
{
	while(*s)
		U0_TxChar(*s++);
}

void U0_TxU32(u32 n)
{
	s32 i=0;
	u8 a[10];
	if(n==0)
	{
		U0_TxChar('0');
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
			U0_TxChar(a[i]);
		}
  }		
}

void U0_Log(s8 *message)
{
U0_TxStr("LOG");
if(log_count <10)
U0TxStr("00");
else if(log_count <100)
U0TxStr("0");
U0TxU32(log_count++);
U0TxStr(":");
U0TxStr(message);
U0TxStr("\n");
}
void U0_TxS32(s32 n)
{
	if(n<0)
	{
		U0_TxChar('-');
		n=-n;
	}
	U0_TxU32(n);
}

void U0_TxF32(f32 f,u32 nDP)
{
	u32 n,i;
	if(f<0.0)
	{
		U0_TxChar('-');
		f=-f;
	}
	n=f;
	U0_TxU32(n);
	U0_TxChar('.');
	for(i=0;i<nDP;i++)
	{
		f=(f-n)*10;
		n=f;
		U0_TxChar(n+48);
	}		
}

s8 * U0_RxStr(void)
{
	static s8 s[100];
	s32 i=0;
	while(1)
	{
		s[i]=U1_RxChar();
		U0_TxChar(s[i]);
		if((s[i]=='\n')||(s[i]=='\r'))
		{
			s[i]='\0';
			break;
		}
		i++;
	}
	return s;
}
   */