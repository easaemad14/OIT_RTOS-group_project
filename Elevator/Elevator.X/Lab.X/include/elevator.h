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


typedef uint8_t bool_t;
#define TRUE  255
#define FALSE 0

#define NUM_LEDS 3

#define SW1     0x40    //RD6
#define SW2     0x80    //RD7
#define SW3     0x2000  //RD13
#define PRESSED 0       //Active low

#define PORT_MASK 0x20C0 //Only need the switches 

typedef uint8_t bool_t;

// InitElevator will quickly setup necessary infrastructure for the Elevator
// task then delete itself. Will call other setup functions in quick succession
// (unless delays are actually needed) to get the job done.
//
void InitElevator(void * some_parameter);


#endif //MY_TASKS_H