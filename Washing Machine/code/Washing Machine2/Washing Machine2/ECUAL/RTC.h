/*
 * DS1307.h
 *
 * Created: 9/24/2020 8:04:47 PM
 *  Author: SHAHER
 */ 


#ifndef RTC_H_
#define RTC_H_

	#include "I2C.h"
	
	#define RTC_Address_Write  ((uint8)0xD0)
	#define RTC_Address_Read   ((uint8)0xD1)
	#define SEC_Address        ((uint8)0x00)
	#define Control_Address    ((uint8)0x07)
	#define AMPM               ((uint8)0x20)
	#define Hour24_format      ((uint8)0x40)
	
	typedef struct  
	{
		vuint8 Second;
		vuint8 Min;
		vuint8 Hour;
		vuint8 Day;
		vuint8 Date;
		vuint8 Mon;
		vuint8 Year;
	}RTC_Info;



void RTC_Init(RTC_Info *Info);
void RTC_Read(RTC_Info *Info);
void RTC_Write(RTC_Info *Info);


#endif /* RTC_H_ */