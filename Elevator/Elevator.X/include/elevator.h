#pragma once
/*******************************************************************************
 * File:        elevator.h
 * Author:      Steven Morales
 *              steven.morales@oit.edu
 * 
 * Description: This is the header file for the elevator system
 ******************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "leddrv.h"
#include "swdrv.h"
#include "queue.h"
#include "string.h"


// Elevator queue messages
#define GD_CALL 1 // 'z'
#define P1_CALL 2 // 'c' OR 'x'
#define P2_CALL 3 // 'v'
#define DOOR_INT 4 // 'm'
#define EMER_STP 5 // 'b' || ES (CLI)

// Lift operations
#define GOTO_GD 0
#define GOTO_P1 51
#define GOTO_P2 52

// Completed elevator tasks (from elevator)
#define CLEAR_GD 100
#define CLEAR_P1 101
#define CLEAR_P2 102
#define CLEAR_DOOR_INT 103
#define CLEAR_DOOR_CLOSE 104
#define EMER_CLR 105 // 'n' || ER

#define CMD_NULL 255


// Elevator class
struct elevator {
    uint8_t direction; // going up, down, or idle, respectively
    uint8_t rel_pos; // current floor the elevator is on; 0, 50, or 51
    uint16_t abs_pos; // floor elevator is heading (in feet)
    uint8_t rel_vel; // Change in displacement
    uint8_t abs_vel; // Max velocity
    uint8_t rel_acc; // Change in velocity
    uint8_t abs_acc; // Max acceleration
    uint8_t gd_wait; // Someone is waiting to go up
    uint8_t p1_wait; // Someone is waiting to go some direction
    uint8_t p2_wait; // Someone is waiting to go down
    int8_t door_i; // Keep track of door status; signed
    uint8_t door_int; // Someone got in the way or door open
    uint8_t door_close; // Close the door
    uint8_t emer_stop; // Emergency stop
} E1;


void create_elevator(void);