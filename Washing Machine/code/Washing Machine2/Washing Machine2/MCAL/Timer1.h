/*
 * Timer1.h
 *
 * Created: 7/4/2020 2:57:56 AM
 *  Author: shaher
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

	#include "MACROSH.h"
	#include "StandardTypes.h"
	#include "MC_Config.h"
	#include <avr/io.h>



	#define TCCR1       (*(vuint16*)0x4E)



	/*Timer/Counter Interrupt Mask Register  (TIMSK)*/
	#define TICIE1_EN       (0)    /*Timer/Counter1 Input Capture Interrupt Enable*/
	#define OCIE1A_EN       (1)    /*Timer/Counter1A Output Compare Match Interrupt Enable*/
	#define OCIE1B_EN       (0)    /*Timer/Counter1B Output Compare Match Interrupt Enable*/
	#define TOIE1_EN        (0)    /*Timer/Counter1 Overflow Interrupt Enable*/

	/*Timer/Counter Control Register (TCCR1A)*/
	#define FOC1A_EN        (0)    /*Force Output Compare (non-PWM mode)*/
	#define FOC1B_EN        (0)    /*Force Output Compare (non-PWM mode)*/

	/*Timer/Counter1 Control Register B (TCCR1B) ICR*/
	#define ICNC1_EN        (0)    /*Input Capture Noise Canceler*/
	#define ICES1_EN        (1)    /*Input Capture Edge Select 0 a falling (negative) edge ,1 a rising (positive) edge*/

	/****************************************************/


	/*PreScalar Setting  in TCCR1B*/
	typedef enum{
	
	T1_OFF,       /*No clock source (Timer/Counter stopped)*/
	T1_FCPU,
	T1_FCPU8,
	T1_FCPU64,
	T1_FCPU256,
	T1_FCPU1024,
	T1_EX_Rising,    /*T1 Pin*/
	T1_EX_Falling,   /*T1 Pin*/
	
}Timer1_Prescaler;

/************************************************************/

/*COM 1A1:1A0 IN TCCR1A*/
	typedef enum{
	
	/*----------OC1A---------------*/
	
	T1_Noraml_NO_OC1A=0x0000,                      /*Normal port operation, OC1 disconnected*/
	
	T1_NO_PWM_Toggle_OC1A=0x4000,                   /*Toggle OC1 on compare match*/
	T1_NO_PWM_Clear_OC1A=0x8000,                    /*Clear OC1 on compare match*/
	T1_NO_PWM_Set_OC1A=0xC000,                      /*Set OC1 on compare match*/
	
	T1_Fast_PWM_Non_Inverting_OC1A=0x8000,              /*Clear OC1 on compare match, set OC1 at BOTTOM*/
	T1_Fast_PWM_Inverting_OC1A=0xC000,                  /*Set OC1 on compare match, clear OC1 at BOTTOM*/
	
	T1_Phase_Correct_PWM_Non_Inverting_OC1A=0x8000,     /*Clear OC1 on compare match when up-counting. Set OC1 on compare match when down counting*/
	T1_Phase_Correct_PWM_Inverting_OC1A=0xC000,         /*Set OC1 on compare match when up-counting. Clear OC1 on compare match when down counting*/
	
	
}T1_Compare_OC1A_Mode;


/*COM 1B1:1B0 IN TCCR1A*/
typedef enum{
	/*----------OC1B---------------*/
	
	T1_Noraml_NO_OC1B=0x0000,                      /*Normal port operation, OC1 disconnected*/
	
	T1_NO_PWM_Toggle_OC1B=0x1000,                   /*Toggle OC1 on compare match*/
	T1_NO_PWM_Clear_OC1B=0x2000,                    /*Clear OC1 on compare match*/
	T1_NO_PWM_Set_OC1B=0x3000,                      /*Set OC1 on compare match*/
	
	T1_Fast_PWM_Non_Inverting_OC1B=0x2000,              /*Clear OC1 on compare match, set OC1 at BOTTOM*/
	T1_Fast_PWM_Inverting_OC1B=0x3000,                  /*Set OC1 on compare match, clear OC1 at BOTTOM*/
	
	T1_Phase_Correct_PWM_Non_Inverting_OC1B=0x2000,     /*Clear OC1 on compare match when up-counting. Set OC1 on compare match when down counting*/
	T1_Phase_Correct_PWM_Inverting_OC1B=0x3000,         /*Set OC1 on compare match when up-counting. Clear OC1 on compare match when down counting*/
	
}T1_Compare_OC1B_Mode;

typedef enum{
	T1_Normal                      =0x0000,
	T1_Phase_Correct_PWM_8Bit      =0x0100,
	T1_Phase_Correct_PWM_9Bit      =0x0200,
	T1_Phase_Correct_PWM_10Bit     =0x0300,
	T1_CTC_OCR1A                   =0x0008,
	T1_Fast_PWM_8Bit               =0x0108,
	T1_Fast_PWM_9Bit               =0x0208,
	T1_Fast_PWM_10Bit              =0x0308,
	T1_Phase_Freq_Correct_PWM_ICR1 =0x0010,
	T1_Phase_Freq_Correct_PWM_OCR1A=0x0110,
	T1_Phase_Correct_PWM_ICR1      =0x0210,
	T1_Phase_Correct_PWM_OCR1A     =0x0310,
	T1_CTC_ICR1                    =0x0018,
	
	T1_Fast_PWM_ICR1               =0x0218,
	T1_Fast_PWM_OCR1A              =0x0318,
}Timer1_Mode;



void Timer1_Init( Timer1_Mode T1_Mode ,T1_Compare_OC1A_Mode  CMP_OC1A_Mode , T1_Compare_OC1B_Mode CMP_OC1B_Mode ,  Timer1_Prescaler CLK );
void T1_WaveGeneration_CTC_OC1A( Timer1_Mode T1_Mode , float32 Max ,float64 F_Timer ,float32 F_OutSignal );
void T1_PWM_OC1A( float32 Duty , float32 Max , Timer1_Mode T1_Mode ,T1_Compare_OC1A_Mode  CMP_OC1A_Mode );
void T1_PWM_OC1B( float32 Duty , float32 Max , Timer1_Mode T1_Mode ,T1_Compare_OC1B_Mode  CMP_OC1B_Mode );







#endif /* TIMER1_H_ */