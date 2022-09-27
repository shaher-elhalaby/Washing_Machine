/*
 * I2C_EEPROM.c
 *
 * Created: 9/28/2020 4:17:51 PM
 *  Author: SHAHER
 */ 

#include "I2C_EEPROM.h"

Status_Code I2C_EEPROM_Write(uint8 Slave_Address ,uint8 Address , uint8 Data)
{
	I2C_Start();

	I2C_Write_byte((Slave_Address<<1));

	I2C_Write_byte(Address);

	I2C_Write_byte(Data);

	I2C_Stop();
	return 0;
}

Status_Code I2C_EEPROM_Read(uint8 Slave_Address ,uint8 Address , uint8 *R_Data)
{
	I2C_Start();

	I2C_Write_byte((Slave_Address<<1));

	I2C_Write_byte(Address);

	I2C_Start();

	I2C_Write_byte(Address+1);

	
	*R_Data=I2C_Read_NAck();
	
	I2C_Stop();
	return 0;
}