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

#define CLOSE_DOORS 0
#define OPEN_DOORS 1


QueueHandle_t doors_queue;


// Defined some basic boolean-type variables since there is no bool type
// already available in FreeRTOS
//
typedef uint8_t bool_t;
#define TRUE  255
#define FALSE 0
#define PRESSED 0       //Active low buttons. Need reverse logic


//**************************************************************************************//
// Creating a flag to separate production code from whatever else I need just to        //
// simulate communication from other tasks and variables. comment out to                //
// make ready for release                                                               //
//
#define DEBUG_MODE
//
//**************************************************************************************//

//**************************************************//
// these definitions will only hold for debugging.  //
//                                                  //

    //some definitions


#ifdef DEBUG_MODE

#define ABS_MAX_ACCEL 30;   // ft/(s^2)

int16_t max_speed = 20;     // ft/second
int16_t max_accel = 2;      // ft/(s^2)


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





#endif



//******************************************************************//
// These defs/functions/etc will be used once debugging is          //
// undefined (ie. in release).                                      //
//                                                                  //
#ifndef DEBUG_MODE

/*No production code yet*/

#endif

struct{
    uint16_t CALL_FROM_GD       : 1;
    uint16_t CALL_FROM_P2       : 1;
    uint16_t CALL_UP_FROM_P1    : 1;
    uint16_t CALL_DOWN_FROM_P1  : 1;
    uint16_t EMERGANCY_STOP     : 1;
    uint16_t CLEAR_E_STOP       : 1;
    uint16_t GO_TO_GD           : 1;
    uint16_t GO_TO_P1           : 1;
    uint16_t GO_TO_P2           : 1;
    
}ButtonSignal;

//******************************************************************//
// This section will have basic defines and variables as outlined   //           
// in the term project instructions                                 //
//                                                                  //
#define PENT_HOUSE_2    52
#define PENT_HOUSE_1    51
#define GROUND_FLOOR    0
#define CURRENT_FLOOR   (current_height/80)
#define UPDATE_RATE     (500 / portTICK_PERIOD_MS)

//******************************************************//
// some definitions for the door task                   //
//                                                      //
#define FULLY_OPEN  3
#define CLOSED      0
#define _5_SECONDS      (5000 / portTICK_PERIOD_MS)
#define DOOR_SPEED      (1000 / portTICK_PERIOD_MS)

//******************************************************************//
// This section will be initialize variable that elevator is        //
// responsible for calculating                                      //
//                    
static uint16_t current_speed = 0;
static uint16_t current_accel = 0;
static uint16_t current_height = GROUND_FLOOR;
static uint16_t destination_height = GROUND_FLOOR;

//**********************************************************************//
// basic function definitions, except the public ones provided be the   //
// header, those are in the next section                                //
//                                                                      //
//
static void SetupLift(void);
static void BuildDoors(void);
static void InstallButtonPanel( void );
static void Open( uint8_t * doors );
static void Close( uint8_t * doors );
//
//Tasks, no actual parameters in use at the moment
//
void vUpwardTask(void * params );
void vDownwardTask(void * params );
void DoorTask(void * params );
void ButtonScanner(void * Params );
//
// Task handle allocation
//
TaskHandle_t Tasks[4];
#define MOVE_UP_TASK    (Tasks[0])
#define MOVE_DOWN_TASK  (Tasks[1])
#define DOOR_TASK       (Tasks[2])
#define HANDLE_E_STOP   (Tasks[3])

////////////////////////////////// FUNCTIONS ///////////////////////////////////

//**********************************************************************//
// Basic getter functions to allow retrieval of current stats without   //
// exposing the actual variable to accidental reassignment              //
//                                                                      //
// In order to allow 1/2 second update intervals with 1 ft/s^2          //
// resolution without floating points had to multiply all values        //
// internally by 8. Return functions will correct for this before       //
// actually returning.                                                  //
//                                                                      //
int8_t getCurrentAccel(void)
{
    return (current_accel >> 3);
}

int8_t getCurrentSpeed( void )
{
    return (current_speed >> 3);
}

int16_t getCurrentHeight(void)
{
    return (current_height >> 3);
}

#define SET_ACCEL   ( current_accel = (max_accel << 3) )
#define STOP        ( current_accel = 0 )
#define ACCELERATE  ( current_speed += current_accel )

// braking will have to counter the acceleration needs to be twice as strong
//
#define BRAKE       ( current_speed -= (current_accel << 1) ) 
#define MOVE_UP     ( current_height += (current_speed >> 1) + (current_accel >> 3))
#define MOVE_DOWN   ( current_height -= (current_speed >> 1) + (current_accel >> 3))

// formula for stopping distance = v^2/(2a), since values are 
// increased 8 fold, adjusted formula is 4(v^2)/a
//
#define STOP_DISTANCE   (((current_speed * current_speed) << 2) / max_accel )
#define DISTANCE_DOWN   ( current_height - destination_height )
#define DISTANCE_UP     ( destination_height - current_height )


static void Open( uint8_t * doors )
{
    PORTDSET = (*doors);
    ++(*doors); 
}

static void Close( uint8_t * doors  )
{
    PORTDCLR = --(*doors);
}


////////////////////////////////////// TASKS ///////////////////////////////////

//**************************************************************************//
// This will figure out the direction speed and necessary stop              //
// updates values at distance of the movement. Will not update              //
// its max_speed or acceleration settings while already moving;             //
// will wait til the last second before departing the current floor.        //
//                                                                          //
void vUpwardTask(void * params)
{     
    while(1)
    {
        // Start off by sleeping the task
        // will be woken by the button panel
        //
        if(DISTANCE_UP == 0)
        {
            STOP;
            vTaskSuspend(NULL);
            SET_ACCEL;
        }
        
        MOVE_UP;
        
        if( current_speed < (max_speed << 3))
        {
            ACCELERATE;
        }
        
        if ( DISTANCE_UP < STOP_DISTANCE )
        {
            BRAKE;
        }
        vTaskDelay(UPDATE_RATE);
    }
}

void vDownwardTask(void * params)
{
     while(1)
    {
        // Start off by sleeping the task
        // will be woken by the button panel
        //
        if(DISTANCE_DOWN == 0)
        {
            STOP;
            vTaskSuspend(NULL);
            SET_ACCEL;
        }
        
        MOVE_DOWN;
        
        if( current_speed < (max_speed << 3))
        {
            ACCELERATE;
        }
        
        if ( DISTANCE_DOWN < STOP_DISTANCE )
        {
            BRAKE;
        }
        vTaskDelay(UPDATE_RATE);        
     }
}

//*********************************************************************//
// Door task will open the door over three seconds hold for 5 seconds
// then close the door over 3 second as long as there is no interference
// 
//
void DoorTask(void * params)
{
    while(1)
    {
        //Open doors over 3 seconds
        //
        
        //Hold open for 5 seconds or until close_door command
        //
        
        //Close door as long as no interference
        //and no open_door command
        //
    }
}

//**************************************************************************//
// Button Scanner will check the queue(s) for saved button presses          //
// and take appropriate action depending on the button(s) in the queue(s)   //
//                                                                          //
void ButtonScanner(void * Params)
{
    while(1)
    {
        ;
    }
}

//////////////////////////////// Setup Functions ///////////////////////////////


// Sets up the initial Elevator movement task
//
static void SetupLift(void)
{
    BaseType_t success = xTaskCreate(
                                    vUpwardTask,
                                    "MoveUp",
                                    configMINIMAL_STACK_SIZE,
                                    (void*) NULL,
                                    1,
                                    MOVE_UP_TASK  );
    if(success == pdFAIL)
    {
        while(1);
    }
    
    success = xTaskCreate(
                        vDownwardTask,
                        "MoveDown",
                        configMINIMAL_STACK_SIZE,
                        (void*) NULL,
                        1,
                        MOVE_DOWN_TASK  );
    
    if(success == pdFAIL)
    {
        while(1);
    }
}

// Just instantiates a Door task
//
static void BuildDoors(void)
{
    BaseType_t success = xTaskCreate(
                                    DoorTask,
                                    "Doors",
                                    configMINIMAL_STACK_SIZE,
                                    (void*) NULL,
                                    1,
                                    DOOR_TASK  );
    if(success == pdFAIL)
    {
        while(1);
    }
}

// Prepare the necessary queues and button task
//
static void InstallButtonPanel(void)
{
    // Instantiate the necessary queues first...
    //
    
    
    // ...Then create the task to use them
    //
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


//**************************************************//
// This function will run through instantiating     //
// the necessary other functions and tasks of the   //
// elevator                                         //
//                                                  //
void InitElevator(void * unused)
{
    // Init functions all go here
    //
    SetupLift();
    
    BuildDoors();    
    
    InstallButtonPanel();

    // Task deletes itself when finished with setup.
    //
    vTaskDelete(NULL);
}

//
//function to call from main()
//
void create_elevator(void)
{
    if(xTaskCreate(doorTask, "doors", configMINIMAL_STACK_SIZE, 
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
    if(xTaskCreate(elevatorTask, "elevator", configMINIMAL_STACK_SIZE,
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
}

// The elevator task that (should) runs for the life of the program
void elevatorTask(void *params)
{
    int op;
    
    for(;;) {
        //op = OPEN_DOORS;
        //if(doors_queue != NULL) {
        //    xQueueSendToBack(doors_queue, (void *)&op, (TickType_t)5);
        //}
        //vTaskDelay(2* _5_SECONDS);
    }
}

// Doors default to closed; only open if we receive the open command
void doorTask(void *params)
{
    int doorBuf[2]; // Need to be big enough for latency
    doors_queue = xQueueCreate((UBaseType_t)2, (UBaseType_t)sizeof(int));
    
    // Doors default to closed
    setLED(LED1, 1);
    setLED(LED2, 1);
    setLED(LED3, 1);
    
    for(;;) {
        if(xQueueReceive(doors_queue, &doorBuf, (TickType_t)portMAX_DELAY)) {
            if(doorBuf[0] || doorBuf[1]) {
                setLED(LED3, 0);
                vTaskDelay(DOOR_SPEED);
                setLED(LED2, 0);
                vTaskDelay(DOOR_SPEED);
                setLED(LED1, 0);
                vTaskDelay(_5_SECONDS);
            }
            
            // We close the doors either way, even if we just opened
            setLED(LED1, 1);
            vTaskDelay(DOOR_SPEED);
            setLED(LED2, 1);
            vTaskDelay(DOOR_SPEED);
            setLED(LED3, 1);
            vTaskDelay(DOOR_SPEED);
        }
    }
}
