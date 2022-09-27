/*
 * Scheduler.c
 *
 * Created: 7/5/2020 8:59:49 PM
 *  Author: shaher
 */ 

#include "Scheduler.h"

char ErrorFlag=0;


void SchedulerIntit(void)
{
	char i;
	for(i=0;i<Max_Tasks;i++)
	{
		Task_Delete(i);
	}
	ErrorFlag=0;
	Timer1_Init(T1_CTC_OCR1A, T1_Noraml_NO_OC1A, T1_Noraml_NO_OC1B, T1_FCPU);
	OCR1A=1000;
}

void SchedulerUpdate(void)
{
	for(uint8 Index=0;Index<Max_Tasks;Index++)
	{
		if (Task_Array[Index].FP)  //check task is In location.
		{
			if (Task_Array[Index].Delay==0) //Task is ready to run
			{
				Task_Array[Index].Run_me+=1;
				
				if (Task_Array[Index].Period) // Schedule Task to run again.
				{
					Task_Array[Index].Delay=Task_Array[Index].Period;
				}
			}
			else //Task is not ready to run again.
			{
				Task_Array[Index].Delay-=1;
			}
		}
	}
}

uint16 cresteTask(void(*PFuntion)(void),uint32 Initail_Delay,uint32 Period)
{
	uint16 Index =0;
	
	while((Task_Array[Index].FP!=0) && (Index < Max_Tasks)) // grab location for task
	{
		Index++;
	}
	
	if (Index ==Max_Tasks) //there's no space for anther task
	{
		ErrorFlag = Too_Many_Task_Error;
		return Max_Tasks;
	}
	//Create Task
	Task_Array[Index].FP=PFuntion;
	Task_Array[Index].Delay=Initail_Delay;
	Task_Array[Index].Period=Period;
	Task_Array[Index].Run_me=0;
	// Return ID for Task
	return Index;
	
}

void Dispatcher(void)
{
	for(int Index=0;Index<Max_Tasks;Index++)
	{
		if (Task_Array[Index].Run_me > 0)
		{
			(*Task_Array[Index].FP)();   //run the task
			Task_Array[Index].Run_me-=1; //reset run flag
			
			if (Task_Array[Index].Period==0) //if Task run for one time
			{
				Task_Delete(Index);
			}
		}
	}
	Task_Report();
	//Idle_Task();
}

uint8 Task_Delete(uint16 Index)
{
	if (Task_Array[Index].FP==0)
	{
		ErrorFlag = No_Task;
		return ERROR;
	}
	Task_Array[Index].FP=0x0000;
	Task_Array[Index].Delay=0;
	Task_Array[Index].Period=0;
	Task_Array[Index].Run_me=0;
	
	return status;
}

void Task_Report(void)
{
	#ifdef ERROR_STATUS
	
	#endif
}

void SchedulerStart(void)
{
	INT_Enable();
}