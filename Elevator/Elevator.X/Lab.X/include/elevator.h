#pragma once
/*************************************************************
* Author:		Steven Morales
* Filename:		myTasks.h
* Date Created:	1/27/18
* Modifications:	
*  			
**************************************************************/
#include <xc.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "leddrv.h"
#include "swdrv.h"
#include "queue.h"


// InitElevator will quickly setup necessary infrastructure for the Elevator
// task then delete itself. Will call other setup functions in quick succession
// (unless delays are actually needed) to get the job done.
//
void InitElevator(void * some_parameter);

// Returns the height in feet of the elevator in feet
//
int16_t getCurrentHeight( void );

//returns the current speed in ft/s
//
int8_t getCurrentSpeed( void );

// Returns the current acceleration ft/s^2
//
int8_t getCurrentAccel( void );

void elevatorTask(void *params);
void doorTask(void *params);