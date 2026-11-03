//lcd.h
#include"types.h"
void writeLCD(u8);
void CmdLCD(u8);
void CharLCD(u8);
void InitLCD(void);
void StrLCD(u8 *);
void u32LCD(u32);
void s32LCD(s32);
void f32LCD(f32,u32);
void hexLCD(u32);
void binLCD(u32,u32);
void BuildCGRAM(u8*,u32);
