//uart_defines.h

#define FOSC 12000000 //Hz
#define CCLK (FOSC*5) //Hz
#define PCLK (CCLK/4) //Hz
#define BAUD 9600
#define LOADVAL (PCLK/(16*BAUD))

//UxLCR sfr defines
#define _8BITS 3
#define WORD_LEN_SEL _8BITS
#define DLAB_BIT 7

//UxLSR sfr defines
#define DR_BIT   0
#define TEMT_BIT 6



