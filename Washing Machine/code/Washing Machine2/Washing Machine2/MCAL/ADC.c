/*
 * ADC.c
 *
 * Created: 7/9/2019 9:27:20 PM
 *  Author: shaher
 */ 
#include "ADC.h"

void ADC_Init(Trigger_Mode mode,ADC_REF REF,INT_ENABLE INT,PreScalar_Sel CLK)
{
	ADMUX  =(REF);
	ADCSRA =(INT<<ADIE)|(CLK);
	if (mode!=Free_Running)
	{
		Set_Bit(ADCSRA,ADATE); 
	}
	Set_Bit(ADCSRA,ADEN);
}
uint16 analog_Read(Channel_Sel Channel)
{
	uint16 Data=0;
	ADMUX &=0xE0;
	/*start conv*/
	ADMUX |=Channel;
	ADCSRA|=(1<<ADSC);
	while (Bit_Is_Set(ADCSRA,ADIF)==0){};
	Data = (ADC & 0x03FF);
	/* ADIF must be Cleared*/
	Set_Bit(ADCSRA,ADIF);
	return Data;
}
