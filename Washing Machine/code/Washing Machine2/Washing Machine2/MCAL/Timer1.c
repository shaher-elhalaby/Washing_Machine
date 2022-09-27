/*
 * Timer1.c
 *
 * Created: 7/4/2020 2:58:05 AM
 *  Author: shaher
 */ 

#include "Timer1.h"

void Timer1_Init( Timer1_Mode T1_Mode ,T1_Compare_OC1A_Mode  CMP_OC1A_Mode , T1_Compare_OC1B_Mode CMP_OC1B_Mode ,  Timer1_Prescaler CLK )
{
		TCCR1  =(FOC1A_EN<<11)|(FOC1B_EN<<10)|(ICNC1_EN<<7)|(ICES1_EN<<6)|(CMP_OC1A_Mode)|(CMP_OC1B_Mode)|(T1_Mode)|(CLK);
		TIMSK |=(TICIE1_EN<<TICIE1)|(OCIE1A_EN<<OCIE1A)|(OCIE1B_EN<<OCIE1B)|(TOIE1_EN<<TOIE1);
}



void T1_WaveGeneration_CTC_OC1A( Timer1_Mode T1_Mode , float32 Max ,float64 F_Timer ,float32 F_OutSignal )
{
	switch (T1_Mode)
	{
		case T1_CTC_OCR1A:
			OCR1A =(uint16)(Max);
			OCR1A = ((F_Timer/(2*F_OutSignal))-1) ;
			break;
		case T1_CTC_ICR1:
			ICR1 =(uint16)(Max);
			OCR1A = ((F_Timer/(2*F_OutSignal))-1) ;
			break;
		default:
			return;
	}
}


void T1_PWM_OC1A( float32 Duty , float32 Max , Timer1_Mode T1_Mode ,T1_Compare_OC1A_Mode  CMP_OC1A_Mode )
{
	switch (T1_Mode)
	{
		
		case T1_Phase_Correct_PWM_8Bit:
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*2*(0x00FF)) + 0.5 ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(0x00FF)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Phase_Correct_PWM_9Bit:
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*2*(0x01FF)) + 0.5 ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(0x01FF)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Phase_Correct_PWM_10Bit:
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*2*(0x03FF)) + 0.5 ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(0x03FF)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Fast_PWM_8Bit:
			switch (CMP_OC1A_Mode)
				{
					case T1_Fast_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*(0x00FF)) + 0.5 ;
						break;
					case T1_Fast_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*(0x00FF)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Fast_PWM_9Bit:
			switch (CMP_OC1A_Mode)
				{
					case T1_Fast_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*(0x01FF)) + 0.5 ;
						break;
					case T1_Fast_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*(0x01FF)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Fast_PWM_10Bit:
			switch (CMP_OC1A_Mode)
				{
					case T1_Fast_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*(0x03FF)) + 0.5 ;
						break;
					case T1_Fast_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*(0x03FF)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Phase_Freq_Correct_PWM_ICR1:
			ICR1 =(uint16)(Max);
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Phase_Freq_Correct_PWM_OCR1A:
			OCR1A =(uint16)(Max);
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Phase_Correct_PWM_ICR1:
			ICR1 =(uint16)(Max);
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Phase_Correct_PWM_OCR1A:
			OCR1A =(uint16)(Max);
			switch (CMP_OC1A_Mode)
				{
					case T1_Phase_Correct_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
						break;
					case T1_Phase_Correct_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Fast_PWM_ICR1:
			ICR1 =(uint16)(Max);
			switch (CMP_OC1A_Mode)
				{
					case T1_Fast_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)(((Duty/100)*(Max)) + 0.5) ;
						break;
					case T1_Fast_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*(Max)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		
		case T1_Fast_PWM_OCR1A:
			OCR1A =(uint16)(Max);
			switch (CMP_OC1A_Mode)
				{
					case T1_Fast_PWM_Non_Inverting_OC1A :
						OCR1A = (uint16)((Duty/100)*(Max)) + 0.5 ;
						break;
					case T1_Fast_PWM_Inverting_OC1A :
						OCR1A = (uint16)(((100 - Duty)/100)*(Max)) + 0.5 ;
						break;
					default:
						return;
				}
			break;
		default:
			return;
	}
}
void T1_PWM_OC1B( float32 Duty , float32 Max , Timer1_Mode T1_Mode ,T1_Compare_OC1B_Mode  CMP_OC1B_Mode )
{
	switch (T1_Mode)
	{
		
		case T1_Phase_Correct_PWM_8Bit:
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
				OCR1A = (uint16)((Duty/100)*2*(0x00FF)) + 0.5 ;
				break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
				OCR1A = (uint16)(((100 - Duty)/100)*2*(0x00FF)) + 0.5 ;
				break;
			default:
				return;
		}
		break;
		
		case T1_Phase_Correct_PWM_9Bit:
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
				OCR1A = (uint16)((Duty/100)*2*(0x01FF)) + 0.5 ;
				break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
				OCR1A = (uint16)(((100 - Duty)/100)*2*(0x01FF)) + 0.5 ;
				break;
			default:
				return;
		}
		break;
		
		case T1_Phase_Correct_PWM_10Bit:
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)((Duty/100)*2*(0x03FF)) + 0.5 ;
			break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*2*(0x03FF)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Fast_PWM_8Bit:
		switch (CMP_OC1B_Mode)
		{
			case T1_Fast_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)((Duty/100)*(0x00FF)) + 0.5 ;
			break;
			case T1_Fast_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*(0x00FF)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Fast_PWM_9Bit:
		switch (CMP_OC1B_Mode)
		{
			case T1_Fast_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)((Duty/100)*(0x01FF)) + 0.5 ;
			break;
			case T1_Fast_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*(0x01FF)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Fast_PWM_10Bit:
		switch (CMP_OC1B_Mode)
		{
			case T1_Fast_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)((Duty/100)*(0x03FF)) + 0.5 ;
			break;
			case T1_Fast_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*(0x03FF)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Phase_Freq_Correct_PWM_ICR1:
		ICR1 =(uint16)(Max);
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
			break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Phase_Freq_Correct_PWM_OCR1A:
		OCR1A =(uint16)(Max);
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
			break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Phase_Correct_PWM_ICR1:
		ICR1 =(uint16)(Max);
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
			break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Phase_Correct_PWM_OCR1A:
		OCR1A =(uint16)(Max);
		switch (CMP_OC1B_Mode)
		{
			case T1_Phase_Correct_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)(((Duty/100)*2*(Max)) + 0.5) ;
			break;
			case T1_Phase_Correct_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*2*(Max)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Fast_PWM_ICR1:
		ICR1 =(uint16)(Max);
		switch (CMP_OC1B_Mode)
		{
			case T1_Fast_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)(((Duty/100)*(Max)) + 0.5) ;
			break;
			case T1_Fast_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*(Max)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		
		case T1_Fast_PWM_OCR1A:
		OCR1A =(uint16)(Max);
		switch (CMP_OC1B_Mode)
		{
			case T1_Fast_PWM_Non_Inverting_OC1B :
			OCR1A = (uint16)((Duty/100)*(Max)) + 0.5 ;
			break;
			case T1_Fast_PWM_Inverting_OC1B :
			OCR1A = (uint16)(((100 - Duty)/100)*(Max)) + 0.5 ;
			break;
			default:
			return;
		}
		break;
		default:
		return;
	}
}
