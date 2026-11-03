//i2c_peripheral.c
#include <LPC21xx.h>
#include "types.h"
#include "pin_func_defines.h"
#include "pin_connect_block.h"
#include "i2c_defines.h"
void init_i2c(void) 
{ 
   //Cfg p0.2 for SCL functions 
   cfgportpinfunc(0,2,SCL_PIN_0_2); 
   //Cfg p0.3 for SDA functions  
   cfgportpinfunc(0,3,SDA_PIN_0_3); 
   //Cfg Speed for I2C Serial Communication 
   I2SCLL=I2C_DIVIDER; 
   I2SCLH=I2C_DIVIDER; 
   //I2C Peripheral Enable for Communication 
   I2CONSET=1<<I2EN_BIT;  
}
void i2c_start(void) 
{ 
  // start condition 
  I2CONSET=1<<STA_BIT; 
  //wait for start bit status 
  while(((I2CONSET>>SI_BIT)&1)==0); 
  // clear start condition 
  I2CONCLR=1<<STA_BIT; 
}	 
void i2c_restart(void) 
{ 
   // start condition 
   I2CONSET=1<<STA_BIT; 
   //clr prev SI_BIT 
   I2CONCLR=1<<SIC_BIT; 
    //wait for SI bit status 
   while(((I2CONSET>>SI_BIT)&1)==0); 
   // clear start condition 
   I2CONCLR=1<<STA_BIT; 
}	 
void i2c_write(u8 dat) 
{ 
   //put data into I2DAT 
    I2DAT=dat;	 
    //clr SI_BIT using I2CON 
    I2CONCLR=1<<SIC_BIT; 
    //wait for SI bit status 
    while(((I2CONSET>>SI_BIT)&1)==0); 
}	 
void i2c_stop(void) 
{ 
    // issue stop condition 
	I2CONSET=1<<STO_BIT; 
    // clr SI bit status	 
    I2CONCLR=1<<SIC_BIT; 
    //stop will be cleared automatically 
} 
u8  i2c_nack(void) 
{	 
     //I2CONSET = 0x00; //Assert Not of Ack 
     I2CONCLR=1<<SIC_BIT; 
     while(((I2CONSET>>SI_BIT)&1)==0); 
     return I2DAT; 
} 
u8 i2c_mack(void) 
{	 
    I2CONSET=1<<AA_BIT; //Assert Ack 
    I2CONCLR=1<<SIC_BIT; 

    while(((I2CONSET>>SI_BIT)&1)==0); 
    I2CONCLR=1<<AAC_BIT; //Clear Assert Ack 
    return I2DAT; 
}
