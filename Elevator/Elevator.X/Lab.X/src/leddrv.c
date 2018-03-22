#include "leddrv.h"

#define LED_BITS 0x4
#define NUM_LEDS 3
#define LAST_LED 2
#define LED_OUT_OF_RANGE 255

uint8_t initializeLedDriver(void)
{
   //
   // Clear the bottom three bits, then set
   // PORTD to digital output 
   //
    PORTDCLR = 0x7;
    TRISDCLR = 0x7;       
}

uint8_t readLED(uint8_t ledNum)
{
    //verify correct input
    if (ledNum > LED_BITS)
        return LED_OUT_OF_RANGE; //Error: Incorrect input.    
    
    //
    // Bitwise and the ledNum with PORTD, then
    // bit-shift by the ledNum.
    //   
    return ( ledNum & (uint8_t)mPORTDReadBits(LED_BITS) ) >> ledNum;
}

uint8_t setLED(const uint8_t ledNum, const uint8_t value)
{
    //verify correct input
    if(ledNum > LED_BITS)
        return LED_OUT_OF_RANGE; //Error: Incorrect Input    
    
    // take in the ledNum and load PORTSET
    // or PORTDCLR based on "value"
    //
    if(value == 0)
        PORTDCLR = (1 << ledNum);
    else
        PORTDSET = (1 << ledNum);
    return 0;     
}

uint8_t toggleLED(const uint8_t ledNum)
{
    //verify correct input
    if(ledNum > LED_BITS)
        return LED_OUT_OF_RANGE; //Error: Incorrect Input    
    
    // Just flipping bits
    //
    PORTDINV = (1 << ledNum);        
            
    return 0;
}