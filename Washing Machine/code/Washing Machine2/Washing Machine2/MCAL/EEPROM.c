/*
 * EEPROM.c
 *
 * Created: 10/25/2020 5:36:09 PM
 *  Author: SHAHER
 */ 


#include "EEPROM.h"

void EEPROM_INT_Init(EEPROM_INT INT)
{
	EECR |=INT;
}

void EEPROM_Write(uint16 address,uint8 Data)
{
	while(EECR &(1<<EEWE));  /*wait until prev complete.*/
	EEAR = address;			//write address of byte.
	EEDR = Data;            //write Data.
	EECR |= (1<<EEMWE);     //halt before writing.
	EECR |= (1<<EEWE);      //enable writing. 	
}
uint8 EEPROM_Read(uint16 address)
{
	while(EECR &(1<<EEWE));  /*wait until prev complete.*/
	EEAR = address;			//write address of byte.
	EECR |= (1<<EERE);      //ENAble reading.
	return EEDR;            //write Data.
}


void EEPROM_Read_Word(uint16 address,uint8 *Data)
{
	uint16 i=0;
	while(EEPROM_Read(address+i)!='\0')
	{
		Data[i] = EEPROM_Read(address+i);
		i++;
	}
	Data[i]='\0';
}
void EEPROM_Write_Word(uint16 address,uint8 *Data)
{
	uint16 i=0;
	while(Data[i]!='\0')
	{
		EEPROM_Write(address+i,Data[i]);
		i++;
	}
	EEPROM_Write(address+i,'\0');
}