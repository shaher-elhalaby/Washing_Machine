/*
 * GPIO.h
 *
 * Created: 5/28/2020 11:15:10 PM
 *  Author: shaher
 */ 


#ifndef GPIO_H_
#define GPIO_H_

   #include "MACROSH.h"
   #include "StandardTypes.h"
   #include <avr/io.h>
      
	  #define GPIOA  ((GPIO*)0x39)
	  #define GPIOB  ((GPIO*)0x36)
	  #define GPIOC  ((GPIO*)0x33)
	  #define GPIOD  ((GPIO*)0x30)
	  
	  /*
	  #define PIN0   ((uint8)0)
	  #define PIN1   ((uint8)1)
	  #define PIN2   ((uint8)2)
	  #define PIN3   ((uint8)3)
	  #define PIN4   ((uint8)4)
	  #define PIN5   ((uint8)5)
	  #define PIN6   ((uint8)6)
	  #define PIN7   ((uint8)7)
		
	 	*/  
	  
        typedef struct{
			vuint8 pin;
			vuint8 ddr;
			vuint8 port;
			}GPIO;	
			
				
		typedef enum{
			OUTPUT,
			INPUTFLOAT,
			INPUTPULLUP,
			}PIN_Mode;
		
		typedef enum{
			LOW=0x00,
			HIGH,
			}PIN_State;		

void PinDirection( GPIO * G , PIN_Mode Mode , uint8 PINS );
void PinWrite( GPIO * G , uint8 PINS ,  PIN_State State);
PIN_State PinRead( GPIO * G , uint8 PINS);

#endif /* GPIO_H_ */