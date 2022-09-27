/*
 * DS1307.c
 *
 * Created: 9/24/2020 8:04:59 PM
 *  Author: SHAHER
 */ 

#include "RTC.h"

void RTC_Init(RTC_Info *Info)
{
	I2C_Start();
	I2C_Write_byte(RTC_Address_Write);
	I2C_Write_byte(Control_Address);
	I2C_Write_byte(0X10);
	I2C_Stop();
	
}
void RTC_Read(RTC_Info *Info)
{
	I2C_Start();
	I2C_Write_byte(RTC_Address_Write);
	I2C_Write_byte(SEC_Address);
	I2C_Stop();
	I2C_Start();
	I2C_Write_byte(RTC_Address_Read);
	Info->Second=I2C_Read_Ack();
	Info->Min   =I2C_Read_Ack();
	Info->Hour  =I2C_Read_Ack();
	Info->Day   =I2C_Read_Ack();
	Info->Date  =I2C_Read_Ack();
	Info->Mon   =I2C_Read_Ack();
	Info->Year  =I2C_Read_NAck();
	I2C_Stop();
	  
}
void RTC_Write(RTC_Info *Info)
{
	I2C_Start();
	I2C_Write_byte(RTC_Address_Write);
	I2C_Write_byte(SEC_Address);
	I2C_Write_byte(Info->Second);
	I2C_Write_byte(Info->Min);
	I2C_Write_byte(Info->Hour);
	I2C_Write_byte(Info->Day);
	I2C_Write_byte(Info->Date);
	I2C_Write_byte(Info->Mon);
	I2C_Write_byte(Info->Year);
	I2C_Stop();
}