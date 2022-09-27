/*
 * GPIO.c
 *
 * Created: 5/28/2020 11:15:25 PM
 *  Author: shaher
 */ 

#include "GPIO.h"


void PinDirection( GPIO * G , PIN_Mode Mode , uint8 PINS )
{
	switch(Mode)
	{
		case OUTPUT:
		     Set_Bit (G->ddr,PINS);
			 break;
		case INPUTFLOAT:
		     Clear_Bit(G->ddr,PINS);
			 Clear_Bit(G->port,PINS);
			 break;	 
		case INPUTPULLUP:
		     Clear_Bit(G->ddr,PINS);
			 Set_Bit(G->port,PINS);
			 break;	 
	}
	
}
void PinWrite( GPIO * G , uint8 PINS ,  PIN_State State)
{
	switch (State)
	{
		case LOW:
		     Clear_Bit(G->port,PINS);
		     break;
		case HIGH:
		     Set_Bit(G->port,PINS);
			 break;
	}
}
PIN_State PinRead( GPIO * G , uint8 PINS)
{
	return ((G->pin & (1<<PINS)) !=0x00);
}
