//uart1.h
#ifndef _UART1_H_
#define _UART1_H_

#define UART_INT_ENABLE 1

//BAUD RATE CALCULATION & DIVISOR
#define FOSC      12000000   //Hz
#define CCLK  	  5*FOSC
#define PCLK  	  CCLK/4
#define BAUD  	  9600
#define DIVISOR   (PCLK/(16 * BAUD))


void InitUART1(void); /* Initialize Serial Interface       */ 
void UART1_Tx(char ch);  
char UART1_Rx(void); 
void UART1_Str(char *);
//void U0_Log(s8 * );
void UART1_Str1(unsigned char);
void UART1_Int(unsigned int);
void UART1_Float(float);


#endif
