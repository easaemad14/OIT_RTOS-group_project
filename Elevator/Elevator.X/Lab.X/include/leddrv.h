#ifndef LEDDRV_H
#define LEDDRV_H

#define _SUPPRESS_PLIB_WARNING 1

#include <stdint.h>
#include <plib.h>
#include <xc.h>


uint8_t initializeLedDriver(void);
//1. This function will setup the ports for the LEDs and set them to the OFF state.
//Returns a 0 for success, any other value for failure.

uint8_t readLED(const uint8_t ledNum);
//1. This function will return the current state of the given LED Number. 0 for off, 1 for
//on, any other number is an error condition
//ledNum is defined as:
// 0 = LED1 (RD0)
// 1 = LED2 (RD1)
// 2 = LED3 (RD2)

uint8_t setLED(const uint8_t ledNum, const uint8_t value);
//1. Sets ledNum to a state of OFF or ON depending on value. If value is 0 turn OFF
//LED, any other value will turn ON LED. Returns a 0 for success or any other
//number for failure
        
uint8_t toggleLED(const uint8_t ledNum);
//1. This function will toggle the current state of the LED. If the LED is OFF it will turn
//it ON, if LED is ON it will turn it OFF. Returns 0 for success, any other value for
//error.

#endif // !LEDDRV_H