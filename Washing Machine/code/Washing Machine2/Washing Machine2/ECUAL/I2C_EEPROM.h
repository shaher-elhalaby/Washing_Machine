/*
 * I2C_EEPROM.h
 *
 * Created: 9/28/2020 4:17:41 PM
 *  Author: SHAHER
 */ 


#ifndef I2C_EEPROM_H_
#define I2C_EEPROM_H_


	#include "I2C.h"
	
	
Status_Code I2C_EEPROM_Read(uint8 Slave_Address ,uint8 Address , uint8 *R_Data);

Status_Code I2C_EEPROM_Write(uint8 Slave_Address ,uint8 Address , uint8 Data);	


#endif /* I2C_EEPROM_H_ */