#include <LPC21xx.h>
#include "types.h"
#define FOSC 12000000
#define cCLK (5*fosc)
#define PCLK (CCLK/4)
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))
void RTC_Init(void);
void set_time(void);
void Date_Init(void);
void set_date(void);
void display_main(void);
void display_menu(void);
