                      /* spi_eeprom.h */
#ifndef __SPI_EEPROM_H__
#define __SPI_EEPROM_H__

#include "types.h"
void Cmd_25LC512(u8 cmd);
void ByteWrite_25LC512(u16 wBuffAddr,u8 dat);
u8   ByteRead_25LC512(u16 rBuffAddr);
void PageWrite_25LC512(u16 pageStartAddr,u8 *ptr128Bytes);
void PageRead_25LC512(u16 pageStartAddr,u32 n,u8*rec);
#endif



