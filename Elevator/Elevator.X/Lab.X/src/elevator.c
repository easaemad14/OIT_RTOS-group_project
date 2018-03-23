/*************************************************************
*
* Lab/Assignment: Term Project, FreRTOS elevator
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

//**************************************************************************************//
// Creating a flag to separate production code from whatever else I need just           //
// simulate coms from other tasks and variables. comment out to make ready for release  //
//
#define DEBUG_MODE
//
//**************************************************************************************//




//******************************************************************//
// This section will have basic defines and variables as outlined   //           
// in the term project instructions                                 //
//                                                                  //
#define PENT_HOUSE_2    52
#define PENT_HOUSE_1    51
#define GROUND_FLOOR    0

#define TOP_FLOOR       PENT_HOUSE_2
#define BOTTOM_FLOOR    GROUND_FLOOR
#define HALF_WAY       ( ( TOP_FLOOR - BOTTOM_FLOOR) >> 1 )

// Defined some basic bool variables since there is no bool type
// already available in FreeRTOS
//
typedef uint8_t bool_t;
#define TRUE  255
#define FALSE 0
#define PRESSED 0       //Active low buttons. Need reverse logic

//******************************************************//
// These will be the hardware checks to the PIC32 and   //
// EFlight Board button "Panels".                       //
//                                                      //
#define P2_INNER    0x40    //RD6
#define P1_INNER    0x80    //RD7
#define GD_INNER    0x2000  //RD13
#define PORT_D_MASK 0x20C0  //Filtering for the 3 PORT C switches

#define OPEN_DOOR   0x2     //RC1
#define CLOSE_DOOR  0x4     //RC2
#define PORT_C_MASK 0x6     //Filtering for the 2 PORT D switches

static int8_t current_speed = 0;
static int8_t current_accel = 0; 


//**************************************************//
// these definitions will only hold for debugging.  //
//                                                  //
#ifdef DEBUG_MODE

#define ABS_MAX_ACCEL 9;    // ft/(s^2)

uint8_t max_speed = 20;     // ft/second
uint8_t max_accel = 2;      // ft/(s^2)



bool_t up = FALSE;

#endif


//******************************************************************//
// These defs/functions/etc will be used once debugging is          //
// undefined (ie. in release).                                      //
//                                                                  //
#ifndef DEBUG_MODE

/*No production code yet*/

#endif

//******************************************************************//
// This section will be for variable that elevator is responsible   //
// for calculating                                                  //
//                                                                  //
static  int16_t    height = GROUND_FLOOR;
#define CURRENT_FLOOR       (height/10)



//Funtion resets accel to a known state
//
void Coast(void){ current_accel = 0; }

void MoveUp( void )
{
    Coast();
    current_accel += max_accel;
}

void MoveDown( void )
{
    Coast();
    current_accel -= max_accel;
}

void Brake(void )
{
    ;
}

//**********************************************************************/
//Need to have some kinematics in here to update stats as neccessary    /
//                                                                      /
// Update height first                                                  /
// Then update speed                                                    /
//

int16_t CurrentHeight(void)
{
    return height;
}

int8_t CurrentSpeed()
{
    return current_speed;
}

int8_t CuurentAccel(void)
{
    return current_accel;
}

static void newSpeed ( void )
{
    ;
}

static void NewHeight(void )
{
    if (up == TRUE)
    {
        height += 
    }
    else
    {
        
    }
}




// function calculates braking distance necessary for stopping 
// safely based on the current acceleration and max speed.
//
static uint16_t brakingDistance( void /*will be void until otherwise needed*/)
{
    return (uint16_t)( (max_speed * max_speed / max_accel) >> 1);
}


// Need to calculate the threshold to begine the actual breaking
//
static uint16_t brakingMark( void )
{
    return ( (up == TRUE) ? (brakingDistance()) : ( PENT_HOUSE_2 -  brakingDistance()) );
}

// Function (not task) to assemble the queues, semaphores and any other 
// necessary interprocess communication for the 
//
void SetupQueuesAndStuff(void)
{
    
}


/*
 * All tasks will be instantiated for the moment with unused parameters 
 */

// This will figure out the direction speed and
// necessary stop distance of the movement. Will not update
// its speed or acceleration settings while already moving, updates values at
// the last second before departing the current floor.
//
void MoveTask(void * params)
{
    
    
    while(1)
    {
        ;
    }
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
    while(1)
    {
        ;
    }
}

//**************************************************//
// Just instantiates a Door task                    //
//                                                  //
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

void ButtonScanner(void * Params)
{
    while(1)
    {
        ;
    }
}

void InstallButtonPanel()
{
    BaseType_t success = xTaskCreate(
                                    ButtonScanner,
                                    "Panel",
                                    configMINIMAL_STACK_SIZE,
                                    (void*) NULL,
                                    1,
                                    NULL  );
    if(success == pdFAIL)
    {
        while(1);
    }
}


//**************************************************/
// This function will run through instantiating     /
// the necessary other functions and tasks of the   /
// elevator                                         /
//                                                  /
void InitElevator(void * unused)
{
    // Init functions all go here
    //
    SetupLift();
    
    BuildDoors();    
    
    InstallButtonPanel();

    // Deletes itself when finished with setup.
    //
    vTaskDelete(NULL);
}