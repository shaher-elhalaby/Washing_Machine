/*
 * Timer0.h
 *
 * Created: 5/29/2020 1:47:29 AM
 *  Author: shaher
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

   #include "GPIO.h"
   #include "MC_Config.h"
   #include <avr/io.h>

	
	#define FOC0_EN  (0)  /*use as a value*/
	
	
	typedef enum{
		T0_Normal=0x00,
		T0_CTC=0x08,
		T0_PhaseCorrect=0x40,
		T0_Fast=0x48,
		}T0_Mode;
	
	typedef enum{
		T0_Disconnect_OC0=0X00,
		T0_Toggle_OC0=0x10,
		T0_NonInverting_OC0=0x20,
		T0_Inverting_OC0=0x30,
		}OC0_State;
	
	typedef enum{
		T0_OFF,
		T0_FCPU,
		T0_FCPU8,
		T0_FCPU64,
		T0_FCPU256,
		T0_FCPU1024,
		T0_Ex_FALLING,
		T0_Ex_RISING,
		}T0_Prescaler;
		
	typedef enum {
		T0_NoInterrupt,
		T0_OverFlow,
		T0_Compare,
		T0_Both,
		}T0_Interrupt;			

      void T0_Init( T0_Mode Mode , OC0_State OC0 , T0_Interrupt INT , T0_Prescaler CLK );
	  void T0_PWM( float Duty );
	  void T0_WaveGeneration( double F_Timer , double F_Signal );
	  
	  void Delay(float _Delay_);


#endif /* TIMER0_H_ */