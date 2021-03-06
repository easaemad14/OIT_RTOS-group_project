/*******************************************************************************
 * File:        swdrv.c
 * Author:      Easa El Sirgany
 *              easa.elsirgany@oit.edu
 * 
 * Description: This file controls switch functions used by myTasks.c
 ******************************************************************************/
#include "swdrv.h"


/**
 * Functions
 */
// Set up ports for the LEDs and set them to off state
// Returns 0 for success; other for failure
uint8_t initializeSwitchDriver(void)
{
    // Enable pullups for switches SW1 (RD6), SW2 (RD7), and SW3 (RD13)
    ConfigCNPullups(CN15_PULLUP_ENABLE | 
            CN16_PULLUP_ENABLE | CN19_PULLUP_ENABLE);
    
    return 0;
}

// Return the current state of the switch (active low):
// 0 for not pressed, 1 for pressed, other for failure
uint8_t readSwitch(uint8_t swNum)
{
    switch(swNum) {
        case SWITCH_GOTO_P2:
            return !mPORTDReadBits(1 << SWITCH1_BIT_POSITION);
        case SWITCH_GOTO_P1:
            return !mPORTDReadBits(1 << SWITCH2_BIT_POSITION);
        case SWITCH_GOTO_GD:
            return !mPORTDReadBits(1 << SWITCH3_BIT_POSITION);
        case SWITCH_OPEN:
            return !mPORTCReadBits(1 << SWITCH_OPEN_POSITION);
        case SWITCH_CLOSE:
            return !mPORTCReadBits(1 << SWITCH_CLOSE_POSITION);
        default:
            return 2; // 2 for failure
    }
}