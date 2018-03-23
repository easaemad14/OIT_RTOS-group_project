/*************************************************************
* Author:		Steven Morales
* Filename:		myTasks.h
* Date Created:	1/27/18
* Modifications:	
*  			
**************************************************************/

#ifndef MY_TASKS_H
#define MY_TASKS_H

#include <xc.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

// InitElevator will quickly setup necessary infrastructure for the Elevator
// task then delete itself. Will call other setup functions in quick succession
// (unless delays are actually needed) to get the job done.
//
void InitElevator(void * some_parameter);


// Returns the height in feet of the elevator
//
uint16_t CurrentHeight(void);


//
//

#endif //MY_TASKS_H