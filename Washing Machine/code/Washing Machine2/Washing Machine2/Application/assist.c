
/*
 * assist.c
 *
 * Created: 10/20/2020 11:22:58 AM
 *  Author: SHAHER
 */ 


#include "MAIN.h"

extern LCD_CONFIG lcd1;
extern RTC_Info RTC1;
Display_info dis;

uint8 sys_state = OFF;
uint8 ERROR_FLAG=0;

uint8 sys=outProcess;
uint8 sys_stage=idle;
uint16 time_stage=0,OP_Time=0;

uint8_t state_changed=0;

void sys_update(void)
{	
	if(ERROR_FLAG==0)
	{
		if (sys_state==start||sys==inProcess)
		{
			switch(sys_stage)
			{
				case idle:
				sys_stage=fill01;
				time_stage=0;
				break;
				case fill01:
					if (++time_stage>=MaxFillTime)
					{
						ERROR_FLAG=1;
					}
					strcpy((char*)dis.state,"Fill");
					sys=inProcess;
					Control_Door_Lock(ON);
					Control_Water_Valve(ON);
					if(Read_Water_Level()==Water_Full)
					{
						Control_Water_Valve(OFF);
						state_changed=1;
						sys_stage=HEAT;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case HEAT:
					if (++time_stage>=MaxHeatTime)
					{
						ERROR_FLAG=1;
					}
					sys=inProcess;
					strcpy((char*)dis.state,"Heat");
					Control_Water_Heater(ON);
					if(Read_Water_Temperature()>=temperature)
					{
						Control_Water_Heater(OFF);
						state_changed=1;
						sys_stage=wash01;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case wash01:
					if(++time_stage<OP_Time)
					{
						sys=inProcess;
						strcpy((char*)dis.state,"Wash");
						Control_Motor(128,RIGHT);
						Control_Detergent_Hatch(ON);
					}
					if(time_stage>=OP_Time)
					{
						Control_Motor(OFF,OFF);
						Control_Detergent_Hatch(OFF);
						state_changed=1;
						sys_stage=wash02;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case wash02:
					if(++time_stage<OP_Time)
					{
						sys=inProcess;
						strcpy((char*)dis.state,"Wash");
						Control_Motor(128,LEFT);
					}
					if(time_stage>=OP_Time)
					{
						Control_Motor(OFF,OFF);
						state_changed=1;
						sys_stage=drain01;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case drain01:
					if (++time_stage>=MaxFillTime)
					{
						ERROR_FLAG=1;
					}
					sys=inProcess;
					strcpy((char*)dis.state,"Drain");
					Control_Pump(ON);
					if(Read_Water_Level()==Water_Empety)
					{
						Control_Pump(OFF);
						state_changed=1;
						sys_stage=fill02;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case fill02:
					if (++time_stage>=MaxFillTime)
					{
						ERROR_FLAG=1;
					}
					sys=inProcess;
					strcpy((char*)dis.state,"Fill");
					Control_Water_Valve(ON);
					if(Read_Water_Level()==Water_Full)
					{
						Control_Water_Valve(OFF);
						state_changed=1;
						sys_stage=raise01;
						sys=outProcess;
						time_stage=0;
					}
					break;
					case raise01:
					if(++time_stage<OP_Time)
					{
						sys=inProcess;
						strcpy((char*)dis.state,"Raise");
						Control_Motor(255,RIGHT);
					}
					if(time_stage>=OP_Time)
					{
						Control_Motor(OFF,OFF);
						state_changed=1;
						sys_stage=raise02;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case raise02:
					if(++time_stage<OP_Time)
					{
						sys=inProcess;
						strcpy((char*)dis.state,"Raise");
						Control_Motor(255,LEFT);
					}
					if(time_stage>=OP_Time)
					{
						Control_Motor(OFF,OFF);
						state_changed=1;
						sys_stage=drain02;
						sys=outProcess;
						time_stage=0;
					}
					break;
				case drain02:
					if (++time_stage>=MaxFillTime)
					{
						ERROR_FLAG=1;
					}
					sys=inProcess;
					strcpy((char*)dis.state,"Drain");
					Control_Pump(ON);
					if(Read_Water_Level()==Water_Empety)
					{
						Control_Pump(OFF);
						state_changed=1;
						sys_stage=idle;
						sys_state=OFF;
						sys=outProcess;
						time_stage=0;
					}
					break;
			}
		}
		else if (sys_state==pause&&sys==outProcess)
		{
			state_changed=1;
			strcpy((char*)dis.state,"Paused");
		}
	}
	if (sys_state==OFF)
	{
		strcpy((char*)dis.state,"Idle");
		state_changed=1;
		Control_Door_Lock(OFF);
		switch(Read_Selector_Dial())
		{
			case COTTON:
			OP_Time=40;
			break;
			case WOOL:
			OP_Time=20;
			break;
		}
		EEPROM_Write(0x05,OP_Time);
		_delay_us(10);
	}
	EEPROM_Write(0x06,time_stage);
	_delay_us(10);
}

void sys_init(void)
{
	uint8 Boot=0,error;
	
	lcd1.LCD_Control=GPIOA;
	lcd1.LCD_Data   =GPIOC;
	lcd1.RS         =PIN5;
	lcd1.RW         =PIN6;
	lcd1.E          =PIN7;
	
	dis.funp=Read_Water_Temperature;
	dis.lcd=&lcd1;
	dis.RTC=&RTC1;
	strcpy((char*)dis.state,"idle");
	
	I2C_Init(0X08,100000,I2C_INT_Disable,I2C_pre1);
	ADC_Init(Free_Running, AVCC, ADC_No_Int, ADC_Pre2);
	RTC_Init(&RTC1);
	LCD_INIT(&lcd1);
	LCD_Clear(&lcd1);
	T0_Init( T0_Fast, T0_NonInverting_OC0, T0_NoInterrupt, T0_FCPU64);
	EX_INT_Enable(_INT0, Raising_INT0);
	
	PinDirection(GPIOB, OUTPUT,DOOR);
	PinDirection(GPIOB, OUTPUT,PUMP);
	PinDirection(GPIOB, OUTPUT,VAVLE);
	PinDirection(GPIOC, OUTPUT,M1);
	PinDirection(GPIOC, OUTPUT,M2);
	PinDirection(GPIOC, OUTPUT,ERRORpIN);
	PinDirection(GPIOB, OUTPUT,HEATER);
	
	Boot=EEPROM_Read(0x01);
	_delay_us(10);
	error=EEPROM_Read(0x07);
	_delay_us(10);
	if(Boot==0xFF ||error==1)
	{
		EEPROM_Write(0x01,0);
		_delay_us(10);
		EEPROM_Write(0x02,OFF);
		_delay_us(10);
		EEPROM_Write(0x03,idle);
		_delay_us(10);
		EEPROM_Write(0x04,outProcess);
		_delay_us(10);
		EEPROM_Write(0x05,0);
		_delay_us(10);
		EEPROM_Write(0x06,0);
		_delay_us(10);
		EEPROM_Write(0x07,0);
		_delay_us(10);
	}
	else{
		sys_state=EEPROM_Read(0x02);
		_delay_us(10);
		sys_stage=EEPROM_Read(0x03);
		_delay_us(10);
		sys=EEPROM_Read(0x04);
		_delay_us(10);
		OP_Time=EEPROM_Read(0x05);
		time_stage=EEPROM_Read(0x06);
		_delay_us(10);
	}
}
void save_state(void)
{
	if(state_changed==1)
	{
	EEPROM_Write(0x02,sys_state);
	_delay_us(10);
	EEPROM_Write(0x03,sys_stage);
	_delay_us(10);
	EEPROM_Write(0x04,sys);
	_delay_us(10);
	EEPROM_Write(0x07,ERROR_FLAG);
	_delay_us(10);
	}
}

void Display2(void)
{
	RTC_Read(dis.RTC);
	Display(&dis);
}
void BinkError(void)
{
	if(ERROR_FLAG==1)
	{
		static uint8 blink=0;
		strcpy((char*)dis.state,"Error");
		PinWrite(GPIOC,ERRORpIN,blink);
		Control_Detergent_Hatch(OFF);
		Control_Door_Lock(OFF);
		Control_Motor(OFF,OFF);
		Control_Pump(OFF);
		Control_Water_Heater(OFF);
		Control_Water_Valve(OFF);
		blink^=1;
	}
}
	

