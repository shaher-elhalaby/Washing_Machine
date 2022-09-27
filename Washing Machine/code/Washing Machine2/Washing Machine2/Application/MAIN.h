/*
 * MAIN.h
 *
 * Created: 10/20/2020 11:05:34 AM
 *  Author: SHAHER
 */ 


#ifndef MAIN_H_
#define MAIN_H_

	#include <avr/io.h>
	#include "Machine.h"
	#include "EX_INTERRUPT.h"
	#include "EEPROM.h"
	
	
	#define pause  (2)
	#define start  (1)

	#define inProcess  (1)
	#define outProcess (0)

	#define MaxFillTime  (20)
	#define MaxHeatTime  (400)
	#define MaxDrainTime (20)
	#define temperature  (80)

	#define idle     20
	#define fill01   22
	#define HEAT     30
	#define wash01   24
	#define drain01  26
	#define raise01  28
	#define fill02   23
	#define wash02   25
	#define drain02  27
	#define raise02  29
	
	
	void sys_init(void);
	void sys_update(void);
	void Display2(void);
	void BinkError(void);
	void save_state(void);




#endif /* MAIN_H_ */