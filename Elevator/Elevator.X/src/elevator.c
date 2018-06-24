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
#define DEFAULT_VEL 10
#define DEFAULT_ACC 2
#define GD_FLOOR 0
#define P1_FLOOR 51
#define P2_FLOOR 52
#define MAX_DOOR_I 3
#define DOOR_SPEED (1000 / portTICK_PERIOD_MS)
#define DOOR_OPEN_DELAY (5000 / portTICK_PERIOD_MS)
#define UART_DELAY (500 / portTICK_PERIOD_MS)
#define DEFAULT_TASK_DELAY (100 / portTICK_PERIOD_MS)
#define E_QUEUE_LEN 5
#define STATUS_LENGTH 20

// NOTE: Only use this if the doors should already be closed
// This is used because simulated movement toggles these pins
#define EMERGENCY_CLOSE_DOORS       \
            (void)setLED(LED1, 1);  \
            (void)setLED(LED2, 1);  \
            (void)setLED(LED3, 1)

// Toggle the RDn pins to simulate movement
#define TOGGLE_RDn                  \
            (void)toggleLED(LED1);  \
            (void)toggleLED(LED2);  \
            (void)toggleLED(LED3)

#define SET_DIR_UP                      \
            E1.direction = DIR_UP;      \
            (void)setLED(LED_UP, 1);    \
            (void)setLED(LED_DN, 0)

#define SET_DIR_DN                      \
            E1.direction = DIR_DN;      \
            (void)setLED(LED_UP, 0);    \
            (void)setLED(LED_DN, 1)


/**
 * Local Variables
 */
TaskHandle_t lift_handle; // This task will be started for movement
QueueHandle_t e1_queue; // Queue for our first elevator


/**
 * Functions and Tasks
 */
// This function will open (or close) the elevator doors
// Doors only open to let "passengers" in; closed is default state
void openDoors()
{
    portTickType start;
    uint8_t status;
    
    // If this is called, we aren't moving...
    lift_handle = NULL;
    
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
    
    // If we are here while emergency stop, block here
    while(E1.emer_stop);

    // Ensure we don't close the door on someone
    while(E1.door_i < MAX_DOOR_I) {
        if (E1.door_int || E1.emer_stop) { // Open the doors
            return;
        }
        setLED(E1.door_i++, 1);
        start = xTaskGetTickCount();
        while((xTaskGetTickCount() - start) < DOOR_SPEED);
    }
    status = CLEAR_DOOR_CLOSE;
    xQueueSendToFront(e1_queue, (void*)&status, (TickType_t)portMAX_DELAY);
}

// Thread to receive all requests 
void controlTask(void *params)
{
    volatile int sw_gd, sw_p1, sw_p2, sw_open, sw_close;
    uint8_t buf[E_QUEUE_LEN];
    memset(buf, CMD_NULL, sizeof(buf));
    
    e1_queue = xQueueCreate(E_QUEUE_LEN, sizeof(uint8_t));
    configASSERT(e1_queue != NULL);
    
    for(;;) {
        vTaskDelay(DEFAULT_TASK_DELAY); // HOLD UP! WAIT A MINUTE!
        
        // First, let's check to see if we have any messages
        if(xQueueReceive(e1_queue, &buf, 0)) {
            int i;
            for(i = 0; buf[i] != CMD_NULL; i++) {
                if(buf[i] == GD_CALL)               E1.gd_wait = 1;
                else if(buf[i] == P1_CALL)          E1.p1_wait = 1;
                else if(buf[i] == P2_CALL)          E1.p2_wait = 1;
                else if(buf[i] == DOOR_INT)         E1.door_int = 1;
                else if(buf[i] == EMER_STP)         E1.emer_stop = 1;
                else if(buf[i] == CLEAR_GD)         E1.gd_wait = 0;
                else if(buf[i] == CLEAR_P1)         E1.p1_wait = 0;
                else if(buf[i] == CLEAR_P1)         E1.p1_wait = 0;
                else if(buf[i] == CLEAR_P2)         E1.p2_wait = 0;
                else if(buf[i] == CLEAR_DOOR_INT)   E1.door_int = 0;
                else if(buf[i] == CLEAR_DOOR_CLOSE) E1.door_close = 0;
                else if(buf[i] == EMER_CLR)         E1.emer_stop = 0;
                else for(;;); // WTF
                
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
        E1.p1_wait |= sw_p1;
        E1.p2_wait |= sw_p2;
    }
}

// Lift will move the elevator, send UART updates, and simulate motors
// This task is started from the elevator task, and destroys itself when done
void liftTask(void *params)
{
    uint8_t *op = (uint8_t *)params; // Also floor number
    uint8_t done = DOOR_INT; // When done, set door int so elevator will open
    char status[STATUS_LENGTH];
    strncpy(status, "Floor GD Stopped\r\n\0", sizeof(status)); // Appends zeroes
    
    for(;;) {
        if(E1.emer_stop) {
            // TODO: Decelerate, move car to GD, and open doors
            break;
        }
        
        // TODO: Move corresponding to operation data
#if 1
        if(*op == GOTO_GD) {
            strncpy(status, "Floor GD Moving\r\n\0", sizeof(status));
        } else if(*op == GOTO_P1) {
            strncpy(status, "Floor P1 Moving\r\n\0", sizeof(status));
        } else if(*op == GOTO_P2) {
            strncpy(status, "Floor P2 Moving\r\n\0", sizeof(status));
        } else for(;;);
#endif
        
        break;
    }
    
    vUartPutStr(UART1, status);
    xQueueSendToFront(e1_queue, (void*)&done, (TickType_t)portMAX_DELAY);
    vTaskDelete(NULL);
}

// The elevator task is in charge of receiving all messages and applying logic
void elevatorTask(void *params)
{
    uint8_t lift, con; // What does the lift need to do?
    
    // Wait for all components to be up
    while(e1_queue == NULL) {
        vTaskDelay(DEFAULT_TASK_DELAY);
    }
    
    for(;;) {
        vTaskDelay(DEFAULT_TASK_DELAY);
        
        // Don't do anything if we are in emergency stop
        if(E1.emer_stop) {
            if(lift_handle == NULL) {
                if(xTaskCreate(liftTask, "lift", configMINIMAL_STACK_SIZE,
                        NULL, 1, lift_handle) == pdFAIL) {
                    for(;;);
                }
            } // Else, this task checks
            while(E1.emer_stop); // We've got nothing to do
        }
        
        // Check to see if we need to open the doors
        if(E1.door_int && (lift_handle == NULL)) {
            do { // openDoors will return on failure
                openDoors();
            } while(E1.door_i < MAX_DOOR_I);
        }
        
        // If the lift is active, don't do anything
        if(lift_handle != NULL) {
            continue;
        }
        
        lift = CMD_NULL;
        con = CMD_NULL;
            
        // First, let's check to see if we need to service the current floor
        if((E1.rel_pos == GD_FLOOR) && (E1.gd_wait)) {
            lift = GOTO_GD;
        } else if((E1.rel_pos == P1_FLOOR) && (E1.p1_wait)) {
            lift = GOTO_P1;
        } else if((E1.rel_pos == P2_FLOOR) && (E1.p2_wait)) {
            lift = GOTO_P2;
        }

        // If I have something to do, start the lift
        if(lift != CMD_NULL) {
            goto start_lift;
        }
        
        // Now, check if we need to move current direction
        if(E1.direction == DIR_UP) {
            switch(E1.rel_pos) {
                case GD_FLOOR:
                    // Check floor P2 wait first so P1 can override value
                    lift = (E1.p1_wait) ? GOTO_P1 :
                            (E1.p2_wait) ? GOTO_P2 : CMD_NULL;
                    break;
                case P1_FLOOR:
                    lift = (E1.p2_wait) ? GOTO_P2 : CMD_NULL;
                    break;
                default:
                    break;
            }
            if(lift != CMD_NULL) {
                SET_DIR_UP;
                goto start_lift;
            }
        } else if(E1.direction == DIR_DN) {
            switch(E1.rel_pos) {
                case P2_FLOOR:
                    lift = (E1.p1_wait) ? GOTO_P1 :
                            (E1.gd_wait) ? GOTO_GD : CMD_NULL;
                    break;
                case P1_FLOOR:
                    lift = (E1.gd_wait) ? GOTO_GD : CMD_NULL;
                    break;
                default:
                    break;
            }
            if(lift != CMD_NULL) {
                SET_DIR_DN;
                goto start_lift;
            }
        }

        // If I have gotten here, I must be going a different direction
        // Luckily for me, P1 is the only floor that can go both directions
        if(E1.p2_wait) {
            lift = GOTO_P2;
            SET_DIR_UP;
            goto start_lift;
        } else if(E1.gd_wait) {
            lift = GOTO_GD;
            SET_DIR_DN;
            goto start_lift;
        }

        // I can only get here if I have nothing to do; don't fall through
        continue;
        
start_lift:
        // If we have something to do, pass along to lift and clear the wait
        if(lift != CMD_NULL) {
            con = (lift == GOTO_GD) ? CLEAR_GD :
                    (lift == GOTO_P1) ? CLEAR_P1 :
                    (lift == GOTO_P2) ? CLEAR_P2 : CMD_NULL;
            configASSERT(con != CMD_NULL); // WTF?
            xQueueSendToBack(e1_queue, (void*)&con, (TickType_t)portMAX_DELAY);
            if(xTaskCreate(liftTask, "lift", configMINIMAL_STACK_SIZE,
                    (void*)&lift, 1, lift_handle) == pdFAIL) {
                for(;;);
            }
        }
    }
}

// Initialize elevator and all subtasks
void create_elevator(void)
{
    // Build our elevator defaults
    E1.direction = DIR_UP;
    E1.rel_pos = GD_FLOOR;
    E1.abs_pos = 0;
    E1.rel_vel = 0;
    E1.abs_vel = DEFAULT_VEL;
    E1.rel_acc = 0;
    E1.abs_acc = DEFAULT_ACC;
    E1.gd_wait = 0;
    E1.p1_wait = 0;
    E1.p2_wait = 0;
    E1.door_i = MAX_DOOR_I;
    E1.door_int = 0;
    E1.door_close = 0;
    E1.emer_stop = 0;
    
    // Close elevator doors
    setLED(LED1, 1);
    setLED(LED2, 1);
    setLED(LED3, 1);
    
    if(xTaskCreate(controlTask, "controller", configMINIMAL_STACK_SIZE,
            NULL, 1, NULL) == pdFAIL) {
        for(;;);
    }
    
    if(xTaskCreate(elevatorTask, "elevator", configMINIMAL_STACK_SIZE,
            NULL, 2, NULL) == pdFAIL) {
        for(;;);
    }
}