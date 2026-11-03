//uart.h
#include "types.h"
void Init_UART0(void);
void U0_TxChar(u8);	
u8 U0_RxChar(void);
void U0_TxStr(s8 *);
void U0_TxU32(u32);
void U0_TxS32(s32);
void U0_TxF32(f32,u32);
s8 * U0_RxStr(void);
