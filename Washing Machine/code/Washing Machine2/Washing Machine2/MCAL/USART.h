/*
 * USART.h
 *
 * Created: 8/20/2019 2:53:40 PM
 *  Author: shaher
 */ 


#ifndef USART_H_
#define USART_H_

#include "StandardTypes.h"
#include "MACROSH.h"
#include "MC_Config.h"
#include <avr/io.h>

	
	 
	 #define UBRR(DATA)	do {\
		 UBRRL = (uint8)(DATA);\
		 UBRRH = ((DATA) >> 8) & 0x03;\
	 }while (0);
	 
	 /********************** Sets *************************/
				   #define _9thBit     (0)
	 /************************************************/	 
	 #define Double_Speed    (1)
	 #define Mulit_processor (0)
	 /********************** UCSRC Sets *************************/
		   
		   typedef enum{
			   USART_Async=0x00,
			   USART_Sync_Raising=0x00,
			   USART_Sync_Failing=0x01,
			   }USART_Mode;
		   
		   typedef enum{
			   PARITY_Disable,
			   PARITY_Even=0x20,
			   PARITY_Odd=0x30,
		   }Parity_Mode;
		   
		   typedef enum{
			   _5Bit,
			   _6Bit=0x02,
			   _7Bit=0x04,
			   _8Bit_9Bit=0x06,
		      }Bits_Set;
			  
			typedef enum
			{
				USART_INT_Disable = 0x00,
				USART_INT_UDRE,
				USART_INT_TX,
				USART_INT_UDRE_TX,
				USART_INT_RX,
				USART_INT_UDRE_RX,
				USART_INT_RX_TX,
				USART_INT_UDRE_RX_TX,
			}INT_Enable;
			
			typedef enum
			{
				STOP1,
				STOP2,
			}Stop_Bits;
			  
		  
	 /**********************************************************/

void  USART_Init(uint16 Baud_Rate, Bits_Set Bit, USART_Mode Mode,INT_Enable INT,Parity_Mode Parity,Stop_Bits Stop);
void  USART_SendByte(uint8 Data);
uint8 USART_RecByte(void);

#endif /* USART_H_ */