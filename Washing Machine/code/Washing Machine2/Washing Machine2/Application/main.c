/*
 * Washing_Machine2.c
 *
 * Created: 10/18/2020 8:06:43 PM
 *  Author: SHAHER
 */ 



#include "MAIN.h"

#include <avr/io.h>
#include "Machine.h"
#include "Scheduler.h"


	extern uint8 sys_state;
	

ISR(TIMER1_COMPA_vect)
{
	SchedulerUpdate();
}

ISR(INT0_vect)
{
	switch(sys_state)
	{
		case OFF:
		sys_state=start;
		break;
		case start:
		sys_state=pause;
		break;
		case pause:
		sys_state=start;
		break;
	}
}

int main(void)
{
	sys_init();
	SchedulerIntit();
	
	cresteTask(sys_update,0,100);
	cresteTask(Display2,1,100);
	cresteTask(BinkError,0,1000);
	cresteTask(save_state,0,1000);
	
	SchedulerStart();
    while(1)
    {
        Dispatcher();
    }
}

