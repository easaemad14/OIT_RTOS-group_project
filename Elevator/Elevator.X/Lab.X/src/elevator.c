/*******************************************************************************
 * File:        elevator.c
 * Author:      Steven Morales
 *              steven.morales@oit.edu
 * 
 * Description: This file contains all of the elevator specific functionality
 ******************************************************************************/
#include "elevator.h"


/**
 * Preprocessor Macros
 */
#define DIR_UP 0
#define DIR_DN 1
#define DIR_NO 2
#define ABS_MAX_ACCEL 30;   // ft/(s^2)
#define MAX_SPEED 20
#define MAX_ACCEL 2
#define GD_FLOOR 0
#define P1_FLOOR 51
#define P2_FLOOR 52
#define DOOR_SPEED (1000 / portTICK_PERIOD_MS)
#define DOOR_OPEN_DELAY (5000 / portTICK_PERIOD_MS)
#define E_QUEUE_LEN 20

// Elevator queue messages
#define GD_UP 0
#define P1_UP 1
#define P1_DN 2
#define P2_DN 3
#define GOTO_GD 4
#define GOTO_P1 5
#define GOTO_P2 6
#define OPEN_DOOR 7
#define CLOSE_DOOR 8 // LOL

/**
 * Local Variables
 */
QueueHandle_t e1_queue; // Queue for our first elevator

// Elevator class
struct elevator {
    uint8_t direction; // going up, down, or idle, respectively
    uint8_t rel_pos; // current floor the elevator is on; 0, 50, or 51
    uint16_t abs_pos; // displacement in feet
    uint8_t velocity; // Change in displacement
    uint8_t accel; // Change in velocity
    uint8_t gd_wait; // Someone is waiting to go up
    uint8_t p1_wait_up; // Go up from P1
    uint8_t p1_wait_dn; // Going down from P1
    uint8_t p2_wait; // Someone is waiting to go down
    uint8_t door_i; // Keep track of door status
    uint8_t door_int; // Someone got in the way
    uint8_t door_close; // Close the door
} E1;


/**
 * Functions and Tasks
 */
// Initialize elevator and all subtasks
void create_elevator(void)
{
    if(xTaskCreate(doorTask, "doors", configMINIMAL_STACK_SIZE, 
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
    
    if(xTaskCreate(recvTask, "receiver", configMINIMAL_STACK_SIZE,
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
    
    if(xTaskCreate(elevatorTask, "elevator", configMINIMAL_STACK_SIZE,
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
    
    // Build our elevator
    E1.direction = DIR_UP;
    E1.rel_pos = GD_FLOOR;
    E1.abs_pos = 0;
    E1.velocity = 0;
    E1.accel = 0;
    E1.gd_wait = 0;
    E1.p1_wait_up = 0;
    E1.p1_wait_dn = 0;
    E1.p2_wait = 0;
    E1.door_i = 3;
    E1.door_int = 0;
    E1.door_close = 0;
    
    // Close elevator doors
    setLED(LED1, 1);
    setLED(LED2, 1);
    setLED(LED3, 1);
}

// The elevator task is in charge of receiving all messages and applying logic
void elevatorTask(void *params)
{
    volatile int sw_gd, sw_p1, sw_p2, sw_open, sw_close;
    
    for(;;) {
        // TODO: Check switches and do logical stuff
#if 0
        sw_open = readSwitch(SWITCH_OPEN);
        sw_close = readSwitch(SWITCH_CLOSE);
        
        if(sw_open == 1) {
            LOCKOUT(SWITCH_OPEN);
            toggleLED(LED_UP);
        }
        
        if(sw_close == 1) {
            LOCKOUT(SWITCH_CLOSE);
            toggleLED(LED_DN);
        }
        
        vTaskDelay(SWITCH_DEBOUNCE_DELAY_MSECS);
#endif
    }
}

// The door task controls door functionality
// Doors only open to let "passengers" in; closed is default state
void doorTask(void *params)
{
    // Open the doors, unless some says otherwise
    while(E1.door_i > 0) {
        if(E1.door_close) {
            break;
        }
        setLED(--E1.door_i, 0);
        vTaskDelay(DOOR_SPEED);
    }
    vTaskDelay(DOOR_OPEN_DELAY);

    // Ensure we don't close the door on someone
    while(E1.door_i <= LED3) { // See the correlation here?
        if (E1.door_int) { // Open the doors
            return;
        }
        setLED(E1.door_i++, 1);
        vTaskDelay(DOOR_SPEED);
    }
}

// Thread to receive all requests 
void recvTask(void *params)
{
    uint8_t buf[E_QUEUE_LEN];
    e1_queue = xQueueCreate(E_QUEUE_LEN, sizeof(uint8_t));
    configASSERT(e1_queue != NULL);
    
    if(xQueueReceive(e1_queue, &buf, (TickType_t)portMAX_DELAY)) {
        // TODO: get lock and modify elevator
    }
}