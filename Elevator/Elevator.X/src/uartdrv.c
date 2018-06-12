/*******************************************************************************
 * File:        uartdrv.c
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This file contains all the tasks for the uart component of the
 *              third lab.
 ******************************************************************************/
#include "uartdrv.h"

/**
 * Functions
 */
// Initialize UART
// This function does NOT do any error checking!
void initUART(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
{
    // Set the Baud Rate of the UART
    UARTSetDataRate(umPortNum, (uint32_t)configPERIPHERAL_CLOCK_HZ,
            ui32WantedBaud);
    
    // Enable UART for tx
    UARTEnable(umPortNum, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX));
}

// Transmit a byte over the UART port specified
void vUartPutC(UART_MODULE umPortNum, char cByte)
{
    while(!UARTTransmitterIsReady(umPortNum)) {
        vTaskDelay(UART_DELAY);
    }
    
    // Write and assume it works
    UARTSendDataByte(umPortNum, cByte);
}

// Transmit a string over the UART port specified
// Don't assume the string is NULL terminated; just write
// This function does no error checking
void vUartPutStr(UART_MODULE umPortNum, char *pString, int iStrLen)
{
    int i;
    for(i = 0; i < iStrLen; ++i) {
        vUartPutC(umPortNum, pString[i]);
    }
}