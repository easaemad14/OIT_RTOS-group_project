/*************************************************************
*
* Lab/Assignment:
* 
* Overview:
*
* Input:
*
* Output:
*	
*
************************************************************/

#include "elevator.h"

// Creating a flag to separate production code from whatever else I need just
// simulate coms from other tasks and variables. comment out to make ready for release
//
#define DEBUG_MODE

// these definitions will only hold for debugging.
//
#ifdef DEBUG_MODE

#define ABS_MAX_ACCEL 9;    // ft/(s^2)

uint8_t max_speed = 20;     // ft/second
uint8_t max_accel = 2;      // ft/(s^2)

#endif

/*
 * All tasks will be instantiated for the moment with unused parameters 
 */

// function calculates braking distance necessary for stopping 
// safely based on the current acceleration and max speed.
//
uint16_t brakingdistance( void /*will be void until otherwise needed*/)
{
    return 0;
}

// Function (not task) to assemble the queues, semaphores and any other 
// necessary interprocess communication for the 
//
void SetupQueuesAndStuff(void)
{
    
}

// This will figure out the direction speed and
// necessary stop distance of the movement. Will not update
// its speed or acceleration settings while already moving, updates values at
// the last second before departing the current floor.
//
void MoveTask(void * params)
{
    
}

// Setups the initial Elevator movement task
//
void SetupLift(void)
{
    BaseType_t success = xTaskCreate(
                                    MoveTask,
                                    "Move",
                                    configMINIMAL_STACK_SIZE,
                                    (void*) NULL,
                                    1,
                                    NULL  );
    if(success == pdFAIL)
    {
        while(1);
    }
}

// Actual operating door
//
void DoorTask(void * usused)
{
    
}

// Just instantiates a Door task
//
void BuildDoors(void)
{
    BaseType_t success = xTaskCreate(
                                    DoorTask,
                                    "Doors",
                                    configMINIMAL_STACK_SIZE,
                                    (void*) NULL,
                                    1,
                                    NULL  );
    if(success == pdFAIL)
    {
        while(1);
    }
}


// This function will run through instantiating 
// the necessary other functions and tasks of the 
// elevator
//
void InitElevator(void * unused)
{
    // Init functions all go here
    //

    // Deletes itself when finished with setup.
    //
    vTaskDelete(NULL);
}