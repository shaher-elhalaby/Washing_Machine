/*
 * Timer2.h
 *
 * Created: 10/18/2020 10:15:58 PM
 *  Author: SHAHER
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_


   #include "GPIO.h"
   #include "MC_Config.h"
   #include <avr/io.h>

   
   #define FOC2_EN  (0)  /*use as a value*/
   
   
   typedef enum{
	   T2_Normal=0x00,
	   T2_CTC=0x08,
	   T2_PhaseCorrect=0x40,
	   T2_Fast=0x48,
   }T2_Mode;
   
   typedef enum{
	   T2_Disconnect_OC2=0X00,
	   T2_Toggle_OC2=0x10,
	   T2_NonInverting_OC2=0x20,
	   T2_Inverting_OC2=0x30,
   }OC2_State;
   
   typedef enum{
	   T2_OFF,
	   T2_FCPU,
	   T2_FCPU8,
	   T2_FCPU64,
	   T2_FCPU256,
	   T2_FCPU1024,
	   T2_Ex_FALLING,
	   T2_Ex_RISING,
   }T2_Prescaler;
   
   typedef enum {
	   T2_NoInterrupt,
	   T2_OverFlow   =0X40,
	   T2_Compare    =0x80,
	   T2_Both       =0xC0,
   }T2_Interrupt;

   void T2_Init( T2_Mode Mode , OC2_State OC2 , T2_Interrupt INT , T2_Prescaler CLK );
   void T2_PWM( float Duty );
   void T2_WaveGeneration( double F_Timer , double F_Signal );
   




#endif /* TIMER2_H_ */