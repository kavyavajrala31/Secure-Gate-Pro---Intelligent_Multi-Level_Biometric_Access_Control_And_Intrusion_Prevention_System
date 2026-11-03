                   /* spi_defines.h */
#ifndef __SPI_DEFINES_H__
#define __SPI_DEFINES_H__

//defines for SPI0 Pin Function Select
#define SCK0     0x00000100  //P0.4 
#define MOSI0    0x00001000  //P0.6  
#define MISO0    0x00000400  //P0.5
#define CS       (1<<7)      //p0.7 

// Control Register Bits Setting 
#define Mode_0  0x00  // CPOL 0 CPHA 0
#define Mode_1  0x08  // CPOL 0 CPHA 1
#define Mode_2  0x10  // CPOL 1 CPHA 0
#define Mode_3  0x18  // CPOL 1 CPHA 1
#define MSTR   (1<<5) // SPI0 as Master 
#define LSBF   (1<<6) // default MSB first,if set LSB first

// Status Register bits
#define SPIF (1<<7) // Data Transfer Completion Flag

#endif
