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
#define ABS_MAX_ACCEL 30 // ft/s^2
#define MAX_SPEED 20
#define MAX_ACCEL 2
#define GD_FLOOR 0
#define P1_FLOOR 51
#define P2_FLOOR 52
#define MAX_DOOR_I 3
#define DOOR_SPEED (1000 / portTICK_PERIOD_MS)
#define DOOR_OPEN_DELAY (5000 / portTICK_PERIOD_MS)
#define UART_DELAY (500 / portTICK_PERIOD_MS)
#define DEFAULT_TASK_DELAY (100 / portTICK_PERIOD_MS)
#define E_QUEUE_LEN 5


/**
 * Local Variables
 */
QueueHandle_t e1_queue; // Queue for our first elevator
char status[17];

// Elevator class
struct elevator {
    uint8_t direction; // going up, down, or idle, respectively
    uint8_t rel_pos; // current floor the elevator is on; 0, 50, or 51
    uint16_t abs_pos; // displacement in feet
    uint8_t velocity; // Change in displacement
    uint8_t accel; // Change in velocity
    uint8_t gd_wait; // Someone is waiting to go up
    uint8_t p1_wait_up; // Go up from P1
    uint8_t p1_goto; // Direction doesn't matter
    uint8_t p1_wait_dn; // Going down from P1
    uint8_t p2_wait; // Someone is waiting to go down
    int8_t door_i; // Keep track of door status; signed
    uint8_t door_int; // Someone got in the way or door open
    uint8_t door_close; // Close the door
} E1;


/**
 * Functions and Tasks
 */
// Thread to receive all requests 
void recvTask(void *params)
{
    volatile int sw_gd, sw_p1, sw_p2, sw_open, sw_close;
    uint8_t buf[E_QUEUE_LEN];
    memset(buf, CMD_NULL, sizeof(buf));
    
    e1_queue = xQueueCreate(E_QUEUE_LEN, sizeof(uint8_t));
    configASSERT(e1_queue != NULL);

    // Build our elevator defaults
    E1.direction = DIR_NO;
    E1.rel_pos = GD_FLOOR;
    E1.abs_pos = 0;
    E1.velocity = 0;
    E1.accel = 0;
    E1.gd_wait = 0;
    E1.p1_wait_up = 0;
    E1.p1_wait_dn = 0;
    E1.p2_wait = 0;
    E1.door_i = MAX_DOOR_I;
    E1.door_int = 0;
    E1.door_close = 0;
    
    // Close elevator doors
    setLED(LED1, 1);
    setLED(LED2, 1);
    setLED(LED3, 1);
    
    for(;;) {
        vTaskDelay(DEFAULT_TASK_DELAY); // HOLD UP! WAIT A MINUTE!
        
        // First, let's check to see if we have any messages
        if(xQueueReceive(e1_queue, &buf, 0)) {
            int i;
            for(i = 0; buf[i] != CMD_NULL; i++) {
                switch(buf[i]) {
                    case GD_UP:
                        E1.gd_wait = 1;
                        break;
                    case P1_UP:
                        E1.p1_wait_up = 1;
                        break;
                    case P1_DN:
                        E1.p1_wait_dn = 1;
                        break;
                    case P2_DN:
                        E1.p2_wait = 1;
                        break;
                    case OPEN_DOOR:
                        E1.door_int = 1;
                        break;
                    case CLEAR_GD:
                        E1.gd_wait = 0;
                        break;
                    case CLEAR_P1_UP:
                        E1.p1_wait_up = 0;
                        break;
                    case CLEAR_P1_DN:
                        E1.p1_wait_dn = 0;
                        break;
                    case CLEAR_P2:
                        E1.p2_wait = 0;
                        break;
                    case CLEAR_DOOR_INT:
                        E1.door_int = 0;
                        break;
                    case CLEAR_DOOR_CLOSE:
                        E1.door_close = 0;
                        break;
                    default:
                        for(;;); // WTF?
                }
                
                buf[i] = CMD_NULL; // Don't repeat
            }
        }
        
        // Next, check all buttons
        sw_open = readSwitch(SWITCH_OPEN);
        sw_close = readSwitch(SWITCH_CLOSE);
        sw_gd = readSwitch(SWITCH_GOTO_GD);
        sw_p1 = readSwitch(SWITCH_GOTO_P1);
        sw_p2 = readSwitch(SWITCH_GOTO_P2);
        
        // Debounce all switches
        vTaskDelay(SWITCH_DEBOUNCE_DELAY_MSECS);
        sw_open &= readSwitch(SWITCH_OPEN);
        sw_close &= readSwitch(SWITCH_CLOSE);
        sw_gd &= readSwitch(SWITCH_GOTO_GD);
        sw_p1 &= readSwitch(SWITCH_GOTO_P1);
        sw_p2 &= readSwitch(SWITCH_GOTO_P2);
        
        // Set all button vars appropriately
        E1.door_int |= sw_open;
        // Don't close door flag if already closed
        E1.door_close |= (E1.door_i < MAX_DOOR_I) ? sw_close : 0;
        E1.gd_wait |= sw_gd;
        E1.p1_goto |= sw_p1;
        E1.p2_wait |= sw_p2;
    }
}

// This function will open (or close) the elevator doors
// Doors only open to let "passengers" in; closed is default state
void openDoors()
{
    portTickType start;
    uint8_t status;
    
    // Open the doors, unless some says otherwise
    while(E1.door_i > 0) {
        if(E1.door_close) {
            break;
        }
        setLED(--E1.door_i, 0);
        
        // Delay
        start = xTaskGetTickCount();
        while((xTaskGetTickCount() - start) < DOOR_SPEED);
    }
    start = xTaskGetTickCount(); // Get the time first
    status = CLEAR_DOOR_INT;
    xQueueSendToFront(e1_queue, (void*)&status, (TickType_t)portMAX_DELAY);
    while((xTaskGetTickCount() - start) < DOOR_OPEN_DELAY) {
        if(E1.door_close) {
            break;
        }
    }

    // Ensure we don't close the door on someone
    while(E1.door_i < MAX_DOOR_I) {
        if (E1.door_int) { // Open the doors
            return;
        }
        setLED(E1.door_i++, 1);
        start = xTaskGetTickCount();
        while((xTaskGetTickCount() - start) < DOOR_SPEED);
    }
    status = CLEAR_DOOR_CLOSE;
    xQueueSendToFront(e1_queue, (void*)&status, (TickType_t)portMAX_DELAY);
}

// Lift will move the elevator, send UART updates, and simulate motors
void liftTask(void *params)
{
    for(;;) {
        vTaskDelay(UART_DELAY);
        
        strncpy(status, "Floor GD Stopped\0", sizeof(status));
        vUartPutStr(UART1, status, strlen(status));
        
#if 1 // This doesn't do anything yet...
        vTaskDelete(NULL);
#endif
    }
}

// The elevator task is in charge of receiving all messages and applying logic
void elevatorTask(void *params)
{
    // Wait for all components to be up
    while(e1_queue == NULL) {
        vTaskDelay(DEFAULT_TASK_DELAY);
    }
    
    for(;;) {
        vTaskDelay(DEFAULT_TASK_DELAY);
        
        // Check to see if we need to open the doors
        if(E1.door_int && (E1.direction == DIR_NO)) {
            do { // openDoors will return on failure
                openDoors();
            } while(E1.door_i < MAX_DOOR_I);
        }
        
        // TODO: Add more functionality
    }
}

// Initialize elevator and all subtasks
void create_elevator(void)
{
    if(xTaskCreate(recvTask, "receiver", configMINIMAL_STACK_SIZE,
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
    
    if(xTaskCreate(elevatorTask, "elevator", configMINIMAL_STACK_SIZE,
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
}