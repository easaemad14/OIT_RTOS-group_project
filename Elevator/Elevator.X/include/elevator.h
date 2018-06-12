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
#define OPEN_DOOR 4 // 'm'

// Completed elevator tasks (from elevator)
#define CLEAR_GD 100
#define CLEAR_P1_UP 101
#define CLEAR_P1_DN 102
#define CLEAR_P2 103
#define CLEAR_DOOR_INT 104
#define CLEAR_DOOR_CLOSE 105

#define CMD_NULL 255


void create_elevator(void);