                 /* spi_eemprom.c */
#include <LPC21xx.h>
#include "types.h"
#include "spi_defines.h"
#include "spi.h"
#include "spi_eeprom_defines.h"
#include "spi_eeprom.h"
#include "delay.h"
#include"lcd.h"

void Cmd_25LC512(u8 cmd)
{
  IOCLR0=CS;
  SPI0(cmd);//issue WREN/WRDI
  IOSET0=CS;
}

void ByteWrite_25LC512(u16 addr,u8 dat)
{
  Cmd_25LC512(WREN);//activate write enable latch
	
  IOCLR0=CS;
  SPI0(WRITE); //issue WRITE instruction
  SPI0(addr>>8);//msbyte of 16-bit address loc to be written into
  SPI0(addr);//lsbyte of 16-bit address loc to be written into
  SPI0(dat);//data for that address loc
  IOSET0=CS;
  delay_ms(10);
  Cmd_25LC512(WRDI);//disable/deactivate write enable latch
}  

u8 ByteRead_25LC512(u16 addr)
{
  u8 dat;
  IOCLR0=CS;
  SPI0(READ);   //issue READ instruction
  SPI0(addr>>8);//msbyte of 16-bit address loc to be read
  SPI0(addr);   //lsbyte of 16-bit address loc to be read
  dat=SPI0(0x00);//sending garbage & reading data at loc
  IOSET0=CS;
  return dat;   
}  

void PageWrite_25LC512(u16 pageStartAddr,u8 *ptr128Bytes)
{
  Cmd_25LC512(WREN);//activate write enable latch
  IOCLR0=CS;
  SPI0(WRITE);//issue WRITE instruction
  SPI0(pageStartAddr>>8);//msbyte of 16-bit start of page address loc to be written into
  SPI0(pageStartAddr);//lsbyte of 16-bit address start of page loc to be written into
  while(*ptr128Bytes)
    SPI0(*ptr128Bytes++);
  IOSET0=CS;   
  delay_ms(10);
  Cmd_25LC512(WRDI);//disable/deactivate write enable latch
}

void PageRead_25LC512(u16 pageStartAddr,u32 n,u8*rec)
{
  //u8 buf;
  u32 i=0;
  //buf=ByteRead_25LC512(pageStartAddr);
  for(i=0;i<n;i++)
  {
	rec[i]=ByteRead_25LC512(pageStartAddr+i);
  }
  rec[i]='\0';
}




