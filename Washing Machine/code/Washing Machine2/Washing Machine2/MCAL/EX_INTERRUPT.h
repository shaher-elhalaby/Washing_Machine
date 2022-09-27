/*
 * INTERRUPT.h
 *
 * Created: 6/20/2019 10:56:56 AM
 *  Author: shaher
 */ 


#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

	#include "MACROSH.h"
	#include "StandardTypes.h"
	#include <avr/io.h>

	
	typedef enum
	{
		
		_INT0 = 0x40,
		_INT1 = 0x20,
		_INT2 = 0x80,

	}INT_Sel;
	
	typedef enum
	{
		LVL_INT0=0x00,
		LowLVL_INT0=0x01,
		Failing_INT0=0x02,
		Raising_INT0=0x03,
		
		LVL_INT1=0x00,
		LowLVL_INT1=0x04,
		Failing_INT1=0x08,
		Raising_INT1=0x0c,
		
		Failing_INT2=0x00,
		Raising_INT2=0x40,
		
		
	}INT_Mode;
	
	void EX_INT_Enable( INT_Sel Sel , INT_Mode Mode);
	void EX_INT_Disable( INT_Sel Sel );
	
	#define INT_Enable()  (Set_Bit(SREG,7))
	#define INT_Disable()  (Clear_Bit(SREG,7))

#endif /* INTERRUPT_H_ */