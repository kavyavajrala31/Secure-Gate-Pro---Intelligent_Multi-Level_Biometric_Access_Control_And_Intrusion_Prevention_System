//uart0.c
#include <LPC21xx.H>  /* LPC21xx definitions         */

#include "uart0.h"
#include "lcd.h"
#include "lcd_defines.h"

static u32 log_count=1;
/*char rec_buff[25],dummy;
unsigned char i=0,ch,r_flag;

extern unsigned char buf[25]; 

void UART0_isr(void) __irq
{
  CmdLCD(CLEAR_LCD);
  CmdLCD(GOTO_LINE1_POS0);
  StrLCD("uart");
  if((U0IIR & 0x04)) //check if receive interrupt
  {
		//StrLCD()
		ch = U0RBR;	Read to Clear Receive Interrupt 
		if(i<25)
			rec_buff[i++] = ch; 
  }
  else
  {
      dummy=U0IIR; //Read to Clear transmit interrupt
  
  }
   VICVectAddr = 0; //dummy write 
}  */

void InitUART0(void) /* Initialize Serial Interface       */ 
{  
            		
  PINSEL0 |= 0x00000005; /* Enable RxD0 and TxD0              */
  U0LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit     */
  U0DLL = DIVISOR;           /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
  U0DLM = DIVISOR>>8;
  U0LCR = 0x03;         /* DLAB = 0  */
  
  /*#if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // IRQ
//  VICVectAddr0 = (unsigned)UART1_isr;
  VICVectCntl0 = 0x20 | 7; /* UART0 Interrupt */
  //VICIntEnable = 1 << 7;   /* Enable UART0 Interrupt */
 
  //U0IER = 0x03;       /* Enable UART1  RX and THRE Interrupts */   
             
  //#endif
						
}

void UART0_Tx(char ch)  /* Write character to Serial Port    */  
{ 
  while (!(U0LSR & 0x20));
  U0THR = ch;                
}

char UART0_Rx(void)    /* Read character from Serial Port   */
{                     
  while (!(U0LSR & 0x01));
  return (U0RBR);
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}

/*void UART0_Str1(unsigned char n)
{
 	unsigned char j;   
    for(j=0;j<n;j++)
    {
        UART0_Tx(buf[j]);
    }   
}  */


void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART0_Tx('0');
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
	   UART0_Tx(a[i]);
	 }
   }
}

void U0_Log(char *message)
{
UART0_Str("LOG");
if(log_count <10)
UART0_Str("00");
else if(log_count <100)
UART0_Str("0");
UART0_Int(log_count++);
UART0_Str(":");
UART0_Str(message);
UART0_Str("\n");

}

void U0_LogUser(char *user_id,char *event)
{
UART0_Str("LOG");
if(log_count <10)
UART0_Str("00");
else if(log_count <100)
UART0_Str("0");
UART0_Int(log_count++);
UART0_Str(":USER");
UART0_Str(user_id);
UART0_Str("-");
UART0_Str(event);
UART0_Str("\r\n");
}





void UART0_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART0_Int(x);
  UART0_Tx('.');
  temp=(f-x)*100;
  x=temp;
  UART0_Int(x);
}