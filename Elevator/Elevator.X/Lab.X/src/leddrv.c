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
    uint8_t retVal;
    
    // Up and down LEDs need to enable pull-ups
    ConfigCNPullups(CN6_PULLUP_ENABLE | CN7_PULLUP_ENABLE);
    // Set LEDs low
    retVal = setLED(LED1, 0);
    retVal |= setLED(LED2, 0);
    retVal |= setLED(LED3, 0);
    retVal |= setLED(LED_UP, 0);
    retVal |= setLED(LED_DN, 0);
    
    // LEDs are outputs
    mPORTDSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2);
    mPORTBSetPinsDigitalOut(BIT_4 | BIT_5);
    
    return retVal;
}

// Return the current state of the LED Number: 0 for off, 1 for on, 2 for fail
// 0 = LED1 (RDO), 1 = LED2 (RD1), 2 = LED3 (RD2)
uint8_t readLed(uint8_t ledNum)
{
    // Let's ensure that ledNum is in range first
    if(!IS_VALID_LED(ledNum)) {
        return 2; // Failure
    }
    
    // Return only a one or a zero
    return !!mPORTDReadBits(1 << ledNum);
}

// Set ledNum to state value (0 for OFF, other for ON)
// Returns 0 for success, other for failure
uint8_t setLED(uint8_t ledNum, uint8_t value)
{
    if(!IS_VALID_LED(ledNum)) {
        return 1;
    }
    
    switch(ledNum) {
        case LED1:
        case LED2:
        case LED3:
            (value == 0) ? mPORTDClearBits(1 << ledNum) :
                mPORTDSetBits(1 << ledNum);
            break;
        case LED_UP:
        case LED_DN:
            (value == 0) ? mPORTBSetBits(1 << ledNum) :
                mPORTBClearBits(1 << ledNum);
            break;
        default:
            for(;;);
    }
    
    return 0;
}

// Toggle the current state of the LED
// Returns 0 on success, other for failure
uint8_t toggleLED(uint8_t ledNum)
{
    if(!IS_VALID_LED(ledNum)) {
        return 1;
    }
    
    switch(ledNum) {
        case LED1:
        case LED2:
        case LED3:
            mPORTDToggleBits(1 << ledNum);
            break;
        case LED_UP:
        case LED_DN:
            mPORTBToggleBits(1 << ledNum);
            break;
        default:
            for(;;);
    }
    
    return 0;
}