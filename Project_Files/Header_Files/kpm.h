#ifndef __LCD_H__
#define __LCD_H__

#include "types.h"

u32 ColScan(void);

u32 RowCheck(void);

u32 ColCheck(void);

void Init_KPM(void);

u8 KeyScan(void);

u32 ReadNum(void);
void Read(u8*val);
#endif

