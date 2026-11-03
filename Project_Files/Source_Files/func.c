


void menu()
{
	a='0';
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("MENU: ");
	StrLCD("1)Edit pass");
	CmdLCD(GOTO_LINE2_POS0+6);
	StrLCD("2)Edit FP");
	//choose=KeyScan();
	//while(ColScan());
	if(KeyScan()=='1')
	{
		edit_pass();
	}	
	if(KeyScan()=='2')
	{
		edit_fp();
	}
}
int edit_fp(void)
{
     
   
    InitLCD();
    InitUART0();
    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("FINGER PRINT ");

    delay_ms(2000);

    while (1)
    {
	   	CmdLCD(0x01);
	   	CmdLCD(0x80);
	   	StrLCD("1.ENROLL 3.DEL ");		
		CmdLCD(0xc0);
		StrLCD("2.SEARCH 4.D.ALL");
	//	do
	//	{
			choose = KeyScan();
	//	}while((pageid != '1') && (pageid != '2') && (pageid !='3') && (pageid != '4'));

		if(choose == '1')
		{
			CmdLCD(0x01);
	   		CmdLCD(0x80);
	   		StrLCD("Enter ID: ");
			pageid = ReadNum();
	   		CmdLCD(0xC0);
	   		u32LCD(pageid);					
    		delay_ms(100);
			if(pageid>0 && pageid <10)
			{
				enroll(pageid);
				//delay_s(2);
			}
		}
		else if(choose == '2')
		{
	   		CmdLCD(0x01);
	   		CmdLCD(0x80);
	   		StrLCD("PLACE FINGER");
         	CmdLCD(0xC0);
          	u32LCD(search_fp()); 
			delay_ms(1000); 
		}
		else if(choose == '3')
		{
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
					delay_ms(1000);
				}
				else
				{
					CmdLCD(0x01);
			   		CmdLCD(0x80);
			   		StrLCD("Failed to del..");					
					delay_ms(1000);
				}
			}
		}
		else if(choose == '4')
		{
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
			   	StrLCD("Failed to del..");					
				delay_ms(1000);				
			}
		}	
    }
}
void edit_pass(void)
{
	//PageWrite_25LC512(0x0000,"1111");
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Ent 4 dig cur Pass:");
	CmdLCD(GOTO_LINE2_POS0);
	//pas=pass;
	pas=Readval(pas);
	CmdLCD(CLEAR_LCD);
	PageRead_25LC512(0x0000,4,curpas);
	if(!(strncmp(pas,curpas,4)))
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Ent 4 dig New pas:");
		CmdLCD(GOTO_LINE2_POS0);
		pas=Readval(pas);
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Ent 4 dig New pas agn:");
		CmdLCD(GOTO_LINE2_POS0);
		newpas=Readval(newpas);
		if(!(strncmp(pas,newpas,4)))
		{
			PageWrite_25LC512(0x0000,newpas);
			CmdLCD(CLEAR_LCD);
			StrLCD("Pwd changd");
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Pwd chg fail");
			delay_s(1);
		}
		PageRead_25LC512(0x0000,4,curpas);
		if(!(strncmp(newpas,curpas,4)))
		{
		CmdLCD(CLEAR_LCD);
		StrLCD("pwd chg sucful");
		delay_s(1);
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Pwd chg fail");
			delay_s(1);	
		}
	}
	else
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Pwd chg fail");
		delay_s(1);
	}
}