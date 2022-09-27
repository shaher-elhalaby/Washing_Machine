/*
 * Timer0.c
 *
 * Created: 5/29/2020 1:47:38 AM
 *  Author: shaher
 */ 
#include "Timer0.h"


void T0_Init( T0_Mode Mode , OC0_State OC0 , T0_Interrupt INT , T0_Prescaler CLK )
{
	TCCR0  =(FOC0_EN<<FOC0)|(Mode)|(OC0)|(CLK);
	TIMSK |=(INT);
	
	if(OC0 != T0_Disconnect_OC0 )
	{
		PinDirection( GPIOB , OUTPUT ,PIN3);
	}
}
void T0_PWM( float Duty )
{
	OCR0 = (uint8)((Duty/100.0)*255)+0.5;
}
void T0_WaveGeneration( double F_Timer , double F_Signal )
{
	OCR0 = (uint8)(F_Timer/2*F_Signal)+0.5;
}

void Delay(float _Delay_)
{
	float Frequency=0,Value=0;
	Frequency = (F_CPU/1000000.0);
	Value = 255-((float)F_CPU/(Frequency*10000.0)) ;
	if(_Delay_ !=0)
	{
		_Delay_=3*_Delay_;
		while(_Delay_--)
		{
			T0_Init( T0_Normal , T0_Disconnect_OC0 , T0_NoInterrupt , T0_FCPU );
			TCNT0=(uint8)Value;
			while((TIFR&(1<<TOV0))==0);
			TIFR = (1<<TOV0);
		}
	}
}