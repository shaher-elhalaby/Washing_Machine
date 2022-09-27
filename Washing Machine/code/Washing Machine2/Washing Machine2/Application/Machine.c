/*
 * Machine.c
 *
 * Created: 10/18/2020 8:13:01 PM
 *  Author: SHAHER
 */ 

#include "Machine.h"

LCD_CONFIG lcd1;
RTC_Info RTC1;

uint8 Read_Selector_Dial(void)
{
	switch (PinRead(GPIOA,PIN1))
	{
		case 1:
			return WOOL;
			break;
		case 0:
			return COTTON;
			break;	
	}
	return 0;
}
uint8 Read_Water_Level(void)
{
	uint8 low = PinRead(GPIOB,LOW_LVL);
	uint8 high = PinRead(GPIOB,HIGH_LVL);
	if((high==1)&&(low==1))
	{
		return Water_Full;
	}
	if ((high==0)&&(low==0))
	{
		return Water_Empety;
	}
	return 0;
}
uint8 Read_Water_Temperature(void)
{
	return (analog_Read(_PA0_)*500.0/1024);
}


void Control_Detergent_Hatch(uint8 State)
{
	PinWrite(GPIOB,PIN7,State);
}
void Control_Door_Lock(uint8 State)
{
	PinWrite(GPIOB,DOOR,State);
}
void Control_Motor(uint8 Duty,uint8 Direction)
{
	switch(Direction)
	{
		case RIGHT:
			T0_PWM(Duty);
			PinWrite(GPIOC,M2,ON);
			PinWrite(GPIOC,M1,OFF);
			break;
		case LEFT:
			T0_PWM(Duty);
			PinWrite(GPIOC,M1,ON);
			PinWrite(GPIOC,M2,OFF);
			break;
		case OFF:
			T0_PWM(OFF);
			PinWrite(GPIOC,M1,OFF);
			PinWrite(GPIOC,M2,OFF);
			break;			
	}
		
	}
	void Control_Pump(uint8 State)
	{
		PinWrite(GPIOB,PUMP,State);
	}
	void Control_Water_Heater(uint8 State)
	{
		PinWrite(GPIOB,HEATER,State);
	}
	void Control_Water_Valve(uint8 State)
	{
		PinWrite(GPIOB,VAVLE,State);
	}
	
void Display(Display_info *info)
{
		static char lineOne[16],lineTwo[16],lineThree[16];
		
		static char shour[2],smin[2],ssec[2];
		static char shour1[2],smin1[2],ssec1[2];
		static char tmp[5];
			
			strcpy(lineThree,(const char*)"clk : ");
			strcpy(lineTwo,(const char*)"temp : ");
			strcpy(lineOne,(const char*)"State : ");
			strcat(lineOne,(const char*)info->state);
			strcat(lineOne,"  ");
			itoa((info->RTC->Hour&0x0f),shour,10);
			itoa((info->RTC->Min&0x0f),smin,10);
			itoa((info->RTC->Second&0x0f),ssec,10);
			itoa((info->RTC->Hour>>4),shour1,10);
			itoa(info->RTC->Min>>4,smin1,10);
			itoa(info->RTC->Second>>4,ssec1,10);
				
			itoa((info->funp)(),tmp,10);
			strcat(lineTwo,tmp);
			strcat(lineTwo," ");
				
				
			strcat(lineThree,shour1);
			strcat(lineThree,shour);
			strcat(lineThree,":");
			strcat(lineThree,smin1);
			strcat(lineThree,smin);
			strcat(lineThree,":");
			strcat(lineThree,ssec1);
			strcat(lineThree,ssec);

			LCD_RowCol(info->lcd,0,5);
			LCD_Send_String(info->lcd,(uint8*)"shaher");
			LCD_RowCol(info->lcd,1,0);
			LCD_Send_String(info->lcd,(uint8*)lineOne);
			LCD_RowCol(info->lcd,2,0);
			LCD_Send_String(info->lcd,(uint8*)lineTwo);
			LCD_RowCol(info->lcd,3,0);
			LCD_Send_String(info->lcd,(uint8*)lineThree);
			
}