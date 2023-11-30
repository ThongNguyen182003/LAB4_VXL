/*
 * scheduler.c
 *
 *  Created on: Nov 30, 2023
 *      Author: babyh
 */

#ifndef SRC_SCHEDULER_C_
#define SRC_SCHEDULER_C_
#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0 ;

void SCH_Init(void){

}

void SCH_Add_Task( void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task ++ ;
	}
}
void SCH_Delete_Task(uint32_t ID) {
    if (ID < current_index_task && SCH_tasks_G[ID].pTask) {
        for (uint32_t i = ID;  i < current_index_task - 1; i++) {
            SCH_tasks_G[i] = SCH_tasks_G[i + 1];
            SCH_tasks_G[i+1].TaskID =  SCH_tasks_G[i+1].TaskID - 1;
        }
        current_index_task--;
    }
}


void SCH_Update(void){
    unsigned char Index;
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].pTask){
            if (SCH_tasks_G[Index].Delay == 0) {
                SCH_tasks_G[Index].RunMe += 1;
                if (SCH_tasks_G[Index].Period) {
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            } else {
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}

void SCH_Dispatch_Tasks(void){
	for( int i = 0 ; i < current_index_task ; i++)
	{
		if(SCH_tasks_G[i].RunMe > 0)
		{
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
		}
		if(SCH_tasks_G[i].Period == 0)
		{
			SCH_Delete_Task(i);
		}
	}
}

#endif /* SRC_SCHEDULER_C_ */
