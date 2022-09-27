/*
 * Timer2.c
 *
 * Created: 10/18/2020 10:15:46 PM
 *  Author: SHAHER
 */ 
#include "Timer2.h"


void T2_Init( T2_Mode Mode , OC2_State OC2 , T2_Interrupt INT , T2_Prescaler CLK )
{
	TCCR2  =(FOC2_EN<<FOC2)|(Mode)|(OC2)|(CLK);
	TIMSK |=(INT);
	
	if(OC2 != T2_Disconnect_OC2 )
	{
		PinDirection( GPIOD , OUTPUT ,PIN7);
	}
}
void T2_PWM( float Duty )
{
	OCR2 = (uint8)((Duty/100.0)*255)+0.5;
}
void T2_WaveGeneration( double F_Timer , double F_Signal )
{
	OCR2 = (uint8)(F_Timer/2*F_Signal)+0.5;
}

