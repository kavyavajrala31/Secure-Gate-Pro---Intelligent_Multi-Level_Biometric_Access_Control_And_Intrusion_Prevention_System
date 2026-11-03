//i2c_eeprom.c
#include "types.h"
#include "delay.h"
#include "i2c.h"
void i2c_eeprom_bytewrite(u8 slaveAddr,u8 wBuffAddr,u8 dat) 
{ 
    //issue i2c start 
   i2c_start();	 
   //slaveAddr + w,& take ack 
   i2c_write(slaveAddr<<1);  
   //wBuffAddr,& take ack 
    i2c_write(wBuffAddr>>8);
	i2c_write(wBuffAddr);     
   //dat,& take ack 
   i2c_write(dat);    
   //issue i2c stop	 
   i2c_stop(); 
   //write cycle delay 
   delay_ms(10); 
}			  
u8 i2c_eeprom_randomread(u8 slaveAddr,u8 rBuffAddr) 
{ 
    u8 dat;	 
    //start condition 
    i2c_start();	 
    //slaveAddr + w,&take ack 
    i2c_write(slaveAddr<<1); 
    //rBuffAddr , &take ack 
    i2c_write(rBuffAddr>>8);
	i2c_write(rBuffAddr); 
    //restart     
    i2c_restart();	 
    //slaveAddr + r, &take ack 
    i2c_write(slaveAddr<<1|1);  
	 //read byte from slave & give nack
	dat=i2c_nack();	 
    //stop condition 
    i2c_stop(); 
    return dat; 
} 
void i2c_eeprom_pagewrite(u8 slaveAddr,u16 wBuffStartAddr,s8 *p,u8 nBytes) 
{ 
  u8 i; 
  i2c_start();	 
 //slaveAddr + w 
  i2c_write(slaveAddr<<1);     
  //wBuffStartAddr ,& take ack
  i2c_write(wBuffStartAddr>>8);
  i2c_write(wBuffStartAddr);  
  //write nbytes,for each take ack	
  for(i=0;i<nBytes;i++) 
  { 
   //wDATA,& take ack 
    i2c_write(p[i]);              
  } 
	//issue stop condition
  i2c_stop(); 
	//internal write cycle delay
  delay_ms(10); 
}			  


void i2c_eeprom_seqread(u8 slaveAddr,u16 rBuffStartAddr,s8 *p,u8 nBytes) 
{ 
  u8 i; 
  i2c_start();	
   //slaveAddr + w,& take ack	
   i2c_write(slaveAddr<<1);  
	 //rBuffStartAddr ,& take ack
   i2c_write(rBuffStartAddr>>8);
   i2c_write(rBuffStartAddr);  
  //restart condition	
   i2c_restart();	 
	 //slaveAddr + r ,& take ack 
	i2c_write(slaveAddr<<1|1); 
	 //read nBytes-1,for each give mack
	 for(i=0;i<nBytes-1;i++) 
   { 
		  //read byte,give mack
      p[i]=i2c_mack();	 
   } 
	 //read last byte,give nack
   p[i]=i2c_nack(); 
	 //stop condition
   i2c_stop(); 
}
