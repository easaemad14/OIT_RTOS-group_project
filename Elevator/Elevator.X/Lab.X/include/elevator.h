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
#define GD_UP 0
#define P1_UP 1
#define P1_DN 2
#define P2_DN 3
#define GOTO_GD 4
#define GOTO_P1 5
#define GOTO_P2 6
#define OPEN_DOOR 7
#define CLOSE_DOOR 8


void create_elevator(void);