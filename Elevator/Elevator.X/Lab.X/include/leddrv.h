#pragma once
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING 1
#endif
#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif

/*******************************************************************************
 * File:        leddrv.h
 * Author:      Easa El Sirgany
 *              easa.elsirgany@oit.edu
 * 
 * Description: This is the header file for leddrv.c, containing all of the 
 *              needed goodies.
 ******************************************************************************/
#include <xc.h> // PIC32 support
#include <plib.h>
#include <stdint.h>
#include "FreeRTOS.h" // For portTICK_RATE_MS

// Default LED blink rate
#define DEFAULT_LED_DELAY_MSECS 500 / portTICK_RATE_MS

// enums in C are garbage (there is no type safety) and this is equivalent
#define LED1 0
#define LED2 1
#define LED3 2
#define LED_UP 4
#define LED_DN 5

#define IS_VALID_LED(N) (                   \
            (N == LED1) || (N == LED2) ||   \
            (N == LED3) || (N == LED_UP) || \
            (N == LED_DN))


/**
 * Function definitions
 */
uint8_t initializeLedDriver(void);
uint8_t readLed(uint8_t ledNum);
uint8_t setLED(uint8_t ledNum, uint8_t value);
uint8_t toggleLED(uint8_t ledNum);