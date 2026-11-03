#include<LPC21XX.h>
#include"defines.h"
#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"kpm.h"
#include "ext_int.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "device.h"
#include "R305.h" 
#include "uart0.h"
#include "uart1.h"

#include<string.h>
#define SW_AL 5
unsigned char pass[5],curpass[5],newpass[5];
unsigned char *pas=pass,*curpas=curpass,*newpas=newpass;
unsigned char choose,k=0;
unsigned int pageid;
int usrcnt=0,rusrcnt;
u8 userid[5],ruserid[5],pwd[5],rpwd[5];
u8 usrid[5],rpd[5],pd[5];
u32 count=0;
void menu(void);
void edit_pass(void);
void edit_fp(void);
extern unsigned char a;
int flag=0;

int mystrcmp(const char* a,const char* b)
{
	int k;
	for(k=0;a[k];k++)
	{
		if(a[k]!=b[k])
		{
			return a[k]-b[k];
		}
	}
	return 0;	
}


int main()
{
	int usrcheck;
	InitUART1();
	InitUART0();
	UART0_Str("********************************************************\r\n");
	UART0_Str("*                     WELCOME TO                       *\r\n");
	UART0_Str("*             SECUREGATE PRO - INTELLIGENT             *\r\n");
	UART0_Str("*                MULTI-LEVEL BIOMETRIC                 *\r\n");
	UART0_Str("*                 ACCESS CONTROL AND                   *\r\n");
	UART0_Str("*                INTRUSION PREVENTION                  *\r\n");
	UART0_Str("*                      SYSTEM                          *\r\n");
	UART0_Str("********************************************************\r\n");
	UART0_Str("*******************SYSTEM STARTED***********************\r\n");
	init_i2c();
	InitLCD();
	Init_KPM();
	UART0_Str("*****************SYSTEM INITIALISED*********************\r\n");
	UART0_Str("********************************************************\r\n");
	Enable_EINT2();
	//i2c_eeprom_bytewrite(0x50,0x0000,usrcnt);
	rusrcnt=i2c_eeprom_randomread(0x50,0x0000);
	UART0_Str("Rusrcnt: ");
	UART0_Int(rusrcnt);
	
	//i2c_eeprom_pagewrite(0x50,0x0100,"1111",4);
	//i2c_eeprom_seqread(0x50,0x0100,4,rpwd,4);
	while(1)
	{
		LABEL1:CmdLCD(CLEAR_LCD);
		if(rusrcnt==0)
		{
			CmdLCD(0x01);
			StrLCD("NO DATA BASE");
			UART0_Str("*                     NO DATA BASE                     *\r\n");
			while(a==0);
			a=0;
			menu();
		}
		else
		{
		CmdLCD(0x01);
		StrLCD("Enter 4 digit id:");
		while(ColScan()==1)
		{
			if(a==1)
			{
				a=0;
				menu();
				//goto LABEL1;
			}
		}
		CmdLCD(GOTO_LINE2_POS0);
		memset(userid,'\0',5);
		Read(userid);

		for(k=0;k<rusrcnt;k++)
		{
			i2c_eeprom_seqread(0x50,(0x0002*(k*5)),ruserid,4);
			if((mystrcmp((const char*)usrid,(const char*)ruserid))==0)
			{
				U0_LogUser((char *)usrid, "USER ID VERIFIED");
				flag=1;
			}
			if(flag==1)
			{
				flag=0;
				i2c_eeprom_seqread(0x50,0x0100,rpwd,4);
PASS:			CmdLCD(CLEAR_LCD);
				StrLCD("Enter 4 digit pwd:");
				CmdLCD(GOTO_LINE2_POS0);
				Read(pd);
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD(pd);
				delay_ms(1000);
				if((mystrcmp((const char*)pd,(const char*)rpwd))==0)
	 			{
					U0_LogUser((char *)usrid, "PASSWORD VERIFIED");
					CmdLCD(0x01);
	   				CmdLCD(0x80);
          			if(search_fp())
					{
				   		U0_LogUser((char *)usrid, "FINGERPRINT VERIFIED");
				   		U0_LogUser((char *)usrid, "ACCESS GRANTED");
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE1_POS0);
						StrLCD("DOOR OPEN\r\n");
						motor_open();
						U0_LogUser((char *)usrid, "DOOR OPENED");
						U0_LogUser((char *)usrid, "PRESS SW TO CLOSE");
						while(READBIT(IOPIN0,SW_AL)==1); 
                    	motor_close();
						U0_LogUser((char *)usrid, "DOOR CLOSED");
					} 
					delay_ms(1000);
				}
				else
				{
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					if(count==3)
					{
						U0_LogUser((char *)usrid, "ACCOUNT LOCKED ");
						U0_LogUser((char *)usrid, "ACCESS DENIED ");
					}
					count++;
					StrLCD("pwd incorrect");
					U0_LogUser((char *)usrid, "WRONG PASSWORD ");
				//U0_LogUser((char *)usrid, "ACCESS DENIED ");
                CmdLCD(GOTO_LINE2_POS0);
				goto PASS;
				/*StrLCD("Wait & Enter agn");
				delay_s(1);*/
			}
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Usr id incorrect");
			U0_LogUser((char *)usrid, "INVALID USER ID");
			U0_LogUser((char *)usrid, "ACCESS DENIED");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("Wait & Enter agn");
			delay_s(1);
		}
		}
	}
	}
}


void menu()
{
	//InitUART1();
	char ch;
	a=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	UART0_Str("*****************ADMIN - LOGIN SUCCESSFUL****************\r\n");
	while(1)
	{
		StrLCD("MENU: ");
		StrLCD("1)Edit pass");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("2)Edit FP 3)EXIT");
		ch=KeyScan();
		switch(ch)
		{
			case '1':edit_pass();
					break;
			case '2':edit_fp();
					break;
			case '3':CmdLCD(0x01);
					return;
		}
		/*if(KeyScan()=='1')
		{
			edit_pass();
			return;
		}	
		if(KeyScan()=='2')
		{
			edit_fp();
		}
		return;*/
	}
}
void edit_fp(void)
{
    //InitLCD();
    //InitUART1();
	CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("FINGER PRINT");
	UART0_Str("***********************FINGERPRINT**********************\r\n");

    delay_ms(2000);

    while (1)
    {
	   	CmdLCD(0x01);
	   	CmdLCD(0x80);
	   	StrLCD("1.ENROLL 3.DEL ");		
		CmdLCD(0xc0);
		StrLCD("2.SEARCH 4.D.ALL");
		choose = KeyScan();
		while(ColScan()==0);
		//delay_ms(100);
		switch(choose)
		{
		
		case '1':
			CmdLCD(0x01);
	   		CmdLCD(0x80);
			StrLCD("Enter user ID:");
			CmdLCD(0xC0);
			Read(usrid);
	   		delay_ms(1000);
			CmdLCD(0x01);
			StrLCD("Enter ID: ");
			pageid = ReadNum();
	   		CmdLCD(0xC0);
	   		u32LCD(pageid);				
    		delay_ms(100);
			if(pageid>0 && pageid <10)
			{
				if((enroll(pageid)))
				{
					UART0_Str("LOG: USER ID: ");
					UART0_Str(usrid);
					UART0_Str("  FINGERPRINT ENROLLED\r\n");
					i2c_eeprom_pagewrite(0x50,(0x0002*(usrcnt*5)),usrid,4);
					usrcnt++;
					i2c_eeprom_bytewrite(0x50,0x0000,usrcnt);
					rusrcnt=i2c_eeprom_randomread(0x50,0x0000);
					UART0_Int(rusrcnt);
					UART0_Str("\r\n");
				}
			}
			break;
	
			
		case '2':
	   		CmdLCD(0x01);
	   		CmdLCD(0x80);
	   		StrLCD("PLACE FINGER");
         	CmdLCD(0xC0);
          	u32LCD(search_fp()); 
			U0_LogUser((char *)usrid, "SEARCH SUCCESSFUL ");
			delay_ms(1000); 
			break;
		case '3':
			CmdLCD(0x01);
	   		CmdLCD(0x80);
	   		StrLCD("Enter ID: ");
			pageid = ReadNum();
	   		CmdLCD(0xC0);
	   		u32LCD(pageid);					
    		delay_ms(100);
			if(pageid>0 && pageid <10)
			{
				if(delete_fp(pageid) == 0x00)
				{
					CmdLCD(0x01);
			   		CmdLCD(0x80);
			   		StrLCD("SELECTED ID DEL.");	
					U0_LogUser((char *)usrid, "SELECTED ID DEL ");
					if(usrcnt>0)
					usrcnt--;
					i2c_eeprom_bytewrite(0x50,0x0000,usrcnt);
					rusrcnt=i2c_eeprom_randomread(0x50,0x0000);				
					delay_ms(1000);
				}
				else
				{
					CmdLCD(0x01);
			   		CmdLCD(0x80);
			   		StrLCD("FAILED TO DEL");
					U0_LogUser((char *)usrid, "FAILED TO DEL ");					
					delay_ms(1000);
				}
			}
			break;
		case '4':
			if(deleteall_fp() == 0x00)
			{
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("DEL ALL SUCCUSS");					
				delay_ms(1000);	
			}
			else
			{
				CmdLCD(0x01);
			   	CmdLCD(0x80);
			   	StrLCD("FAILED DEL.");					
				delay_ms(1000);				
			}
			break;
		default: return;
		}
    }
}
void edit_pass(void)
{
	i2c_eeprom_pagewrite(0x50,0x0100,"1111",4);
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Ent 4 dig cur Pass:");
	CmdLCD(GOTO_LINE2_POS0);
	Read(pas);
	i2c_eeprom_seqread(0x50,0x0100,curpass,4);
	if(!(strcmp((const char*)pas,(const char*)curpas)))
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Ent 4 dig New pas:");
		CmdLCD(GOTO_LINE2_POS0);
		Read(pas);
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Ent 4 dig New pas agn:");
		CmdLCD(GOTO_LINE2_POS0);
		Read(newpas);
		if(!(strcmp((const char*)pas,(const char*)newpas)))
		{
			i2c_eeprom_pagewrite(0x50,0x0100,newpas,4);
			CmdLCD(CLEAR_LCD);
			StrLCD("PASS CHANGE SUC");
			U0_LogUser((char *)usrid, "PASSWORD UPDATED ");
			delay_s(1);
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("PWD CHANGE FAIL");
			delay_ms(300);
			return;
		}
	}
	else
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("PWD CHANGE FAIL");
		delay_ms(200);
		return;
	}
}
