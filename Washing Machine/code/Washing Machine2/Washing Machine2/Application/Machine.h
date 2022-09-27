/*
 * Machine.h
 *
 * Created: 10/18/2020 8:12:52 PM
 *  Author: SHAHER
 */ 


#ifndef MACHINE_H_
#define MACHINE_H_

#include "StandardTypes.h"
#include "MACROSH.h"
#include "MC_Config.h"
#include "GPIO.h"
#include <avr/io.h>
#include "LCD.h"
#include "RTC.h"
#include "Timer2.h"
#include "Timer0.h"
#include "ADC.h"
#include <string.h>


#define Water_Empety ((uint8)0x03)
#define Water_Full   ((uint8)0x04)

#define	WOOL   1
#define COTTON 0

#define ON     1
#define OFF    0
#define RIGHT  1
#define LEFT   2

	typedef struct
	{
		uint8 state[8];
		uint8(*funp)(void);
		RTC_Info *RTC;
		LCD_CONFIG *lcd;
	}Display_info; 
	
	#define	FR_M1		(7)
	#define M1			(2)
	#define M2			(3)
	#define PUMP		(4)
	#define VAVLE		(2)
	#define HIGH_LVL	(0)
	#define LOW_LVL		(1)
	#define TEMP		(0)
	#define TIM			(1)
	#define HEATER		(6)
	#define DOOR		(5)
	#define ERRORpIN	(2)

	uint8 Read_Selector_Dial(void);
	uint8 Read_Start_Switch(void);
	uint8 Read_Water_Level(void);
	uint8 Read_Water_Temperature(void);


	void Control_Detergent_Hatch(uint8 State);
	void Control_Door_Lock(uint8 State);
	void Control_Motor(uint8 Duty,uint8 Direction);
	void Control_Pump(uint8 State);
	void Control_Water_Heater(uint8 State);
	void Control_Water_Valve(uint8 State);


	void Display(Display_info *info);

#endif /* MACHINE_H_ */