/*
 * EEPROM.h
 *
 * Created: 10/25/2020 5:36:22 PM
 *  Author: SHAHER
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

	#include <stdio.h>
	#include <avr/io.h>
	#include "MACROSH.h"
	#include "StandardTypes.h"
	
	
	typedef enum{
		EEPROM_INT_DB=0X00,
		EEPROM_INT_EN=0X08,
		}EEPROM_INT;

void EEPROM_INT_Init(EEPROM_INT INT);

void EEPROM_Write(uint16 address,uint8 Data);
uint8 EEPROM_Read(uint16 address);


void EEPROM_Write_Word(uint16 address,uint8 *Data);
void EEPROM_Read_Word(uint16 address,uint8 *Data);


#endif /* EEPROM_H_ */