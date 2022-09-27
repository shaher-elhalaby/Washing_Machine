/*
 * ADC.h
 *
 * Created: 7/9/2019 9:27:08 PM
 *  Author: shaher
 */ 



/* ADC for Simple using */


#ifndef ADC_H_
#define ADC_H_

	#include "StandardTypes.h"
	#include "MACROSH.h"
	#include "MC_Config.h"
	#include <avr/io.h>

	

	typedef enum {
		_PA0_=0x00,
		_PA1_,
		_PA2_,
		_PA3_,
		_PA4_,
		_PA5_,
		_PA6_,
		_PA7_,
		_PA0X10_,
		_PA1X10_,
		//future adding Gain.
		}Channel_Sel;

	typedef enum{
			 AREF     =0x00,
			 AVCC     =0x40,
			 Internal_REF=0xC0,
			 }ADC_REF;
		 
	typedef enum{
		ADC_Pre2=0x01,
		ADC_Pre4,
		ADC_Pre8,
		ADC_Pre16,
		ADC_Pre32,
		ADC_Pre64,
		ADC_Pre128,
	}PreScalar_Sel;		

	typedef enum{
		Free_Running,
		Analog_Comparator=0x40,
		EX_INT0,
		Timer_Counter0_Compare_Match,
		Timer_Counter0_Overflow,
		Timer_Counter1_Compare_Match_B,
		Timer_Counter1_Overflow,
		Timer_Counter1_Capture_Event,
	}Trigger_Mode; 
	
	typedef enum{
		ADC_No_Int,
		ADC_Int_EN,
	}INT_ENABLE;
			 	

void ADC_Init(Trigger_Mode mode,ADC_REF REF,INT_ENABLE INT,PreScalar_Sel CLK);
uint16 analog_Read(Channel_Sel Channel);
	
#endif /* ADC_H_ */