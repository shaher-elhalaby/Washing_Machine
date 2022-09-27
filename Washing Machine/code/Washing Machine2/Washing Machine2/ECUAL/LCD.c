/*
 * LCD.c
 *
 * Created: 7/3/2019 6:50:35 PM
 *  Author: shaher
 */ 

#include "LCD.h"

void LCD_INIT(LCD_CONFIG * ports)
{
	ports->LCD_Control->ddr |=(1<<ports->RW) |(1<<ports->RS) |(1<<ports->E);
   
    #if Eight_Bit
	   
	   ports->LCD_Data->ddr =0xFF;
	   
	#else
	   #if Upper_Data_Port
	   
	   ports->LCD_Data->ddr  |=(0xF0);
	   
	   #else
	   
	   ports->LCD_Data->ddr  |=(0x0F);

       #endif
	  
	#endif
	Send_Instruction(ports,Return_Home); /*what the heal is that?*/
	Send_Instruction(ports,Function_Set);
	Send_Instruction(ports,Display_ON);
	Send_Instruction(ports,Display_Clear);
	
}

void Send_Instruction(LCD_CONFIG * ports,uint8 Instruction)
{
	Clear_Bit(ports->LCD_Control->port,ports->RS);
	Clear_Bit(ports->LCD_Control->port,ports->RW);
	
	Set_Bit(ports->LCD_Control->port,ports->E);
	_delay_ms(1);
	
	#if Eight_Bit
	   ports->LCD_Data->port=Instruction;
	   _delay_ms(1);
	   Clear_Bit(ports->LCD_Control->port,ports->E);
	   _delay_ms(1);
	#else
	   #if Upper_Data_Port
	      ports->LCD_Data->port &=(0x0F); 
		  ports->LCD_Data->port|=(Instruction &(0xF0));
		  _delay_ms(1);
		  
		  Clear_Bit(ports->LCD_Control->port,ports->E);
		  _delay_ms(1);
		  
		  Set_Bit(ports->LCD_Control->port,ports->E);
		  _delay_ms(1);
		  
		  ports->LCD_Data->port &= (0x0F);
		  ports->LCD_Data->port|=((Instruction )<<4);
		  _delay_ms(1);
		  
		  Clear_Bit(ports->LCD_Control->port,ports->E);
		  _delay_ms(1);
		#else
		  ports->LCD_Data->port &= (0xF0);
		  ports->LCD_Data->port|=(Instruction &(0x0F));
		  _delay_ms(1);
		  
		  Clear_Bit(ports->LCD_Control->port,ports->E);
		  _delay_ms(1);
		  
		  Set_Bit(ports->LCD_Control->port,ports->E);
		  _delay_ms(1);
		  
		  ports->LCD_Data->port &= (0xF0);
		  ports->LCD_Data->port|=((Instruction )>>4);
		  _delay_ms(1);
		  
		  Clear_Bit(ports->LCD_Control->port,ports->E);
		  _delay_ms(1);  

       #endif   

    #endif
}

void LCD_Send_Char(LCD_CONFIG * ports,uint8 Data)
{
	Set_Bit(ports->LCD_Control->port,ports->RS);
	Clear_Bit(ports->LCD_Control->port,ports->RW);
	
	Set_Bit(ports->LCD_Control->port,ports->E);
	_delay_ms(1);
	
	 #if Eight_Bit
	      ports->LCD_Data->port=Data;
	      _delay_ms(1);
	      Clear_Bit(ports->LCD_Control->port,ports->E);
	      _delay_ms(1);
	 #else
	    #if Upper_Data_Port
	    ports->LCD_Data->port &= (0x0F) ;
		ports->LCD_Data->port|=(Data &(0xF0));
	    _delay_ms(1);
	
	    Clear_Bit(ports->LCD_Control->port,ports->E);
	    _delay_ms(1);
	
	    Set_Bit(ports->LCD_Control->port,ports->E);
	    _delay_ms(1);
	
	    ports->LCD_Data->port &=(0x0F);
		ports->LCD_Data->port|=((Data )<<4);
	    _delay_ms(1);
	
	    Clear_Bit(ports->LCD_Control->port,ports->E);
	    _delay_ms(1);
		
	    #else
		
	     ports->LCD_Data->port &= (0xF0);
	     ports->LCD_Data->port|=(Data &(0x0F));
	     _delay_ms(1);
	
	     Clear_Bit(ports->LCD_Control->port,ports->E);
	     _delay_ms(1);
	
	     Set_Bit(ports->LCD_Control->port,ports->E);
	     _delay_ms(1);
	
	     ports->LCD_Data->port &= (0xF0);
		 ports->LCD_Data->port|=((Data )>>4);
	     _delay_ms(1);
	
	     Clear_Bit(ports->LCD_Control->port,ports->E);
	     _delay_ms(1);

	    #endif

    #endif
}

void LCD_Send_String(LCD_CONFIG * ports,uint8 * ptr)
{
	while (* ptr !='\0')
	{
		LCD_Send_Char(ports,*ptr);
		ptr++;
	}
}

void LCD_Clear(LCD_CONFIG * ports)
{
	Send_Instruction(ports,Display_Clear);
}

void LCD_RowCol(LCD_CONFIG * ports,uint8 Row ,uint8 Col)
{
	uint8 Address=0;
	
	switch (Row)
	{
		case 0:
		   Address=Col+LCD_1ST_Base;
		   break;
		case 1:
		   Address=Col+LCD_2ND_Base;
		   break;
		case 2:
		   Address=Col+LCD_3RD_Base;
		   break;
		case 3:
		   Address=Col+LCD_4TH_Base;
		   break;
		default:
		   return;         
	}
	Send_Instruction(ports,DDRAM|Address);
}
void LCD_DisplayInt(LCD_CONFIG * ports,sint32 data)
{
	/* String to hold the ascii result */
	char Result[17];
	/* 10 for decimal */
	itoa(data,Result,10);
	/* Display The Result */
	LCD_Send_String(ports,Result);
}