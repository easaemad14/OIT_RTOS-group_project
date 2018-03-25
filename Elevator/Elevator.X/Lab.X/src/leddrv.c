/*******************************************************************************
 * File:        leddrv.c
 * Author:      Easa El Sirgany
 *              easa.elsirgany@oit.edu
 * 
 * Description: This file controls LED functions
 ******************************************************************************/
#include "leddrv.h"


/**
 * Functions
 */
// Set up ports for the LEDs and set them to off state
// Returns 0 for success; other for failure
uint8_t initializeLedDriver(void)
{
    // Set LEDs low
    int i;
    for(i = LED1; i <= LED3; i++) {
        if(setLED(i, 0)) {
            return 1;
        }
    }

    // LEDs are outputs
    mPORTDSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2);
    return 0;
}

// Return the current state of the LED Number: 0 for off, 1 for on, 2 for fail
// 0 = LED1 (RDO), 1 = LED2 (RD1), 2 = LED3 (RD2)
uint8_t readLed(uint8_t ledNum)
{
    // Let's ensure that ledNum is in range first
    if(ledNum > LED3) {
        return 2; // Failure
    }
    // Return only a one or a zero
    return !!mPORTDReadBits(1 << ledNum);
}

// Set ledNum to state value (0 for OFF, other for ON)
// Returns 0 for success, other for failure
uint8_t setLED(uint8_t ledNum, uint8_t value)
{
    if(ledNum > LED3) {
        return 1;
    }
    
    (value == 0) ? mPORTDClearBits(1 << ledNum) :
                mPORTDSetBits(1 << ledNum);
    return 0;
}

// Toggle the current state of the LED
// Returns 0 on success, other for failure
uint8_t toggleLED(uint8_t ledNum)
{
    if(ledNum > LED3) {
        return 1;
    }
    
    mPORTDToggleBits(1 << ledNum);
    return 0;
}