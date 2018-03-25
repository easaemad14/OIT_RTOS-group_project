#pragma once
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING 1
#endif
#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif

/*******************************************************************************
 * File:        swdrv.h
 * Author:      Easa El Sirgany
 *              easa.elsirgany@oit.edu
 * 
 * Description: This is the header file for swdrv.c, containing all of the 
 *              needed goodies.
 ******************************************************************************/
#include <xc.h> // PIC32 support
#include <plib.h>
#include <stdint.h>

#include "FreeRTOS.h"

#define SWITCH1 0
#define SWITCH2 1
#define SWITCH3 2

// 0 = SW1 (RD6), 1 = SW2 (RD7), 2 = SW3 (RD13)
#define SWITCH1_BIT_POSITION 6
#define SWITCH2_BIT_POSITION 7
#define SWITCH3_BIT_POSITION 13

// SW debounce value
#define SWITCH_DEBOUNCE_DELAY_MSECS 10 / portTICK_RATE_MS

// Do not progress until a switch is released
// This is not false-negative debounced
#define LOCKOUT(SW) while(readSwitch(SW))


/**
 * Function definitions
 */
uint8_t initializeSwitchDriver(void);
uint8_t readSwitch(uint8_t swNum);