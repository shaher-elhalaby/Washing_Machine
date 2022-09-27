/*
 * INTERRUPT.c
 *
 * Created: 6/20/2019 10:57:07 AM
 *  Author: shaher
 */ 

#include "EX_INTERRUPT.h"


void EX_INT_Enable(INT_Sel Sel , INT_Mode Mode)
{
	INT_Disable();
	switch(Sel)
	{
		case _INT0:
		    MCUCR|= Mode;
			GICR|=Sel;
			break;
		case _INT1:
		    MCUCR|= Mode;
			GICR|=Sel;
			break;
		case _INT2:
		    MCUCSR|=Mode;
		    GICR|=Sel;
			break;
		default:
		    return;		
	}
	INT_Enable();
}

void EX_INT_Disable( INT_Sel Sel )
{
	GICR&=(~(Sel));
}
