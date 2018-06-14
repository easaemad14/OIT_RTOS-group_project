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


// Elevator queue messages (from UART)
#define GD_UP 0 // 'z'
#define P1_UP 1 // 'c'
#define P1_DN 2 // 'x'
#define P2_DN 3 // 'v'
#define OPEN_DOOR 4 
#define DOOR_INT 5 // 'm'
#define EMER_STP 6 // 'b' || ES (CLI)
#define P1_GOTO 7

// Completed elevator tasks (from elevator)
#define CLEAR_GD 100
#define CLEAR_P1_UP 101
#define CLEAR_P1_DN 102
#define CLEAR_P2 103
#define CLEAR_DOOR_INT 104
#define CLEAR_DOOR_CLOSE 105
#define EMER_CLR 106 // 'n' || ER

#define CMD_NULL 255


// Elevator class
struct elevator {
    uint8_t direction; // going up, down, or idle, respectively
    uint8_t rel_pos; // current floor the elevator is on; 0, 50, or 51
    uint16_t abs_pos; // floor elevator is heading (in feet)
    uint8_t rel_vel; // Change in displacement
    uint8_t abs_vel; // Max velociy
    uint8_t rel_acc; // Change in velocity
    uint8_t abs_acc; // Max acceleration
    uint8_t gd_wait; // Someone is waiting to go up
    uint8_t p1_wait_up; // Go up from P1
    uint8_t p1_goto; // Direction doesn't matter
    uint8_t p1_wait_dn; // Going down from P1
    uint8_t p2_wait; // Someone is waiting to go down
    int8_t door_i; // Keep track of door status; signed
    uint8_t door_int; // Someone got in the way or door open
    uint8_t door_close; // Close the door
    uint8_t emer_stop; // Emergency stop
} E1;


void create_elevator(void);