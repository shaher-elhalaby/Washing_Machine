/*
 * I2C.c
 *
 * Created: 8/28/2019 4:08:01 PM
 *  Author: shaher
 */ 
#include "I2C.h"

void I2C_Init( uint8 Address , uint32 F_SCL,INT_Config INT , Prescalar_Bits Bits)
{
	/*SCL_Freq=(F_CPU)/(16+(2*TWBR*(4^Presscalar_Bits)))*/
	switch(Bits)
	{
		case I2C_pre1:
		TWBR=(uint8)(((double)F_CPU/(2.0*F_SCL))-8.0);
		break;
		case I2C_pre4:
		TWBR=(uint8)(((double)F_CPU/(8.0*F_SCL))-2.0);
		break;
		case I2C_pre16:
		TWBR=(uint8)(((double)F_CPU/(32.0*F_SCL))-0.5);
		break;
		case I2C_pre64:
		TWBR=(uint8)(((double)F_CPU/(128.0*F_SCL))-0.125);
		break;
		default:
		return;
	}
	TWAR =(Address<<1)|(General_Call<<TWGCE);
	TWSR|=(Bits);
	TWCR =(1<<TWEN)|(INT<<TWIE);
}
void I2C_Start(void)
{
	TWCR&=0x07;
	TWCR|=(1<<TWINT)|(1<<TWSTA);
	while(Bit_Is_Clear(TWCR,TWINT));
}
void I2C_Stop(void)
{
	TWCR&=0x07;
	TWCR|=(1<<TWINT)|(1<<TWSTO);
}
uint8 I2C_Read_Ack(void)
{
	TWCR&=0x07;
	TWCR|=(1<<TWINT)|(1<<TWEA);
	while(Bit_Is_Clear(TWCR,TWINT));
	return TWDR;
}
uint8 I2C_Read_NAck(void)
{
	TWCR&=0x07;
	TWCR|=(1<<TWINT);
	while(Bit_Is_Clear(TWCR,TWINT));
	return TWDR;
}
void I2C_Write_byte(uint8 Data)
{
	TWDR=Data;
	TWCR&=0x07;
	TWCR|=(1<<TWINT);
	while(Bit_Is_Clear(TWCR,TWINT));
}
Status_Code I2C_Master_Read(uint8 Slave_Address , uint8 * R_Data )
{
	I2C_Start();
	if (TWS!=START)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Write_byte(((Slave_Address<<1)|(1)));
	if (TWS!=SLA_W_AKN)
	{
		I2C_Stop();
		return TWS;
	}
	* R_Data=I2C_Read_NAck();
	I2C_Stop();
	return 0;
}
Status_Code I2C_Master_Write(uint8 Slave_Address , uint8 Data )
{
	I2C_Start();
	if (TWS!=START)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Write_byte((Slave_Address<<1));
	if (TWS!=SLA_W_AKN)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Write_byte(Data);
	if (TWS!=SLA_W_AKN)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Stop();
	return 0;
}
Status_Code I2C_Master_Mutli_Deal(uint8 Slave_Address ,uint8 Address , uint8*R_Data)
{
	I2C_Start();
	if (TWS!=START)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Write_byte((Slave_Address<<1));
	if (TWS!=SLA_W_AKN)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Write_byte(Address);
	if (TWS!=SLA_W_AKN)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Start();
	if (TWS!=RpSTART)
	{
		I2C_Stop();
		return TWS;
	}
	I2C_Write_byte(((Slave_Address<<1)|(1)));
	if (TWS!=SLA_W_AKN)
	{
		I2C_Stop();
		return TWS;
	}
	*R_Data=I2C_Read_NAck();
	I2C_Stop();
	return 0;
}
Status_Code I2C_Slave_Read( uint8 * R_Data )
{
	*R_Data=I2C_Read_Ack();
	return TWS;
}
Status_Code I2C_Slave_Write( uint8 Data )
{
	I2C_Write_byte(Data);
	return TWS;
}

