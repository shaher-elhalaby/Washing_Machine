/*
 * I2C.h
 *
 * Created: 8/28/2019 4:07:50 PM
 *  Author: shaher
 */ 


#ifndef I2C_H_
#define I2C_H_
   
   #include "StandardTypes.h"
   #include "MACROSH.h"
   #include "MC_Config.h"
   #include <avr/io.h>

	      #define TWS  ((TWSR)&(0xF8))  /*TWI Status*/
		  #define General_Call  (0)
	  
	      typedef enum {
				  I2C_pre1,
				  I2C_pre4,
				  I2C_pre16,
				  I2C_pre64,
			  }Prescalar_Bits;	
			  
			  
			 typedef enum{
				   START=0x08,
				   RpSTART=0x10,
				   SLA_W_AKN=0x18,
				   SLA_W_NOT_AKN=0x20,
				   Data_AKN=0x28,
				   Data_NOT_AKN=0x30,
				   SLA_ARB_Lost=0x38,
			   }Status_Code;
			   
			   
			typedef enum
			{
				I2C_INT_Disable,
				I2C_INT_Enable,   
			}INT_Config;
			
			
void I2C_Init( uint8 Address , uint32 F_SCL,INT_Config INT , Prescalar_Bits Bits);
void I2C_Start(void);
uint8 I2C_Read_Ack(void);
uint8 I2C_Read_NAck(void);
void I2C_Write_byte(uint8 Data);
Status_Code I2C_Master_Read(uint8 Slave_Address , uint8 * R_Data );
Status_Code I2C_Master_Write(uint8 Slave_Address , uint8 Data );
Status_Code I2C_Master_Mutli_Deal(uint8 Slave_Address ,uint8 Address , uint8*R_Data);
Status_Code I2C_Slave_Read( uint8 * R_Data );
Status_Code I2C_Slave_Write( uint8 Data );
void I2C_Stop(void);
Status_Code Error(void);




#endif /* I2C_H_ */