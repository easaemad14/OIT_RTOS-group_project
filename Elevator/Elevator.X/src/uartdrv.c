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
 * Local Variables
 */
extern TaskHandle_t uart_rx_handle; // To be resumed from ISR
char uart_rx_buf[UART_MAX_BUFFER_SIZE];
uint8_t rx_buf_pos;

// Wrapper for assembly interrupt
void __attribute__((interrupt(ipl0AUTO), vector(_UART_1_VECTOR)))
vUART_ISR_Wrapper(void);


/**
 * Functions
 */
// Initialize UART
// This function does NOT do any error checking!
void initUART(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
{
    // Initialized buffer and postion
    memset(uart_rx_buf, 0, sizeof(uart_rx_buf));
    rx_buf_pos = 0;
    
    // Set the Baud Rate of the UART
    UARTSetDataRate(umPortNum, (uint32_t)configPERIPHERAL_CLOCK_HZ,
            ui32WantedBaud);
    
    // Enable UART for tx and rx
    UARTEnable(umPortNum, 
            UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    
    // Set when interrupts will occur
    UARTSetFifoMode(umPortNum, UART_INTERRUPT_ON_RX_NOT_EMPTY);
    
    // Set interrupt priority
    INTSetVectorPriority(INT_VECTOR_UART(umPortNum), INT_PRIORITY_LEVEL_1);
    
    // Enable RX interrup
    INTEnable(INT_SOURCE_UART_RX(umPortNum), INT_ENABLED);
}

// Get a character from our buffer
char UARTGetChar()
{
    configASSERT(rx_buf_pos != 0); // This should never happen
    return uart_rx_buf[rx_buf_pos-- - 1];
}

// Transmit a byte over the UART port specified
void vUartPutC(UART_MODULE umPortNum, char cByte)
{
    while(!UARTTransmitterIsReady(umPortNum));
    
    // Write and assume it works
    UARTSendDataByte(umPortNum, cByte);
}

// Transmit a string over the UART port specified
// Don't assume the string is NULL terminated; just write
// This function does no error checking
void vUartPutStr(UART_MODULE umPortNum, char *pString)
{
    int i;
    
    for(i = 0; isalnum(pString[i]) || isspace(pString[i]); ++i) {
        vUartPutC(UART1, pString[i]);
    }
}

void vUART_ISR()
{
    BaseType_t yieldRequired;
    
    if(INTGetFlag(INT_U1RX)) {
        // Don't do anything if I'm not ready
        if(uart_rx_handle == NULL) {
            INTClearFlag(INT_U1RX);
            return;
        }
        
        // Insert our character into the buffer
        uart_rx_buf[rx_buf_pos++] = (char)UARTGetData(UART1).data8bit;
        
        INTClearFlag(INT_U1RX);
        yieldRequired = xTaskResumeFromISR(uart_rx_handle);
        
        if(yieldRequired == pdTRUE) {
            portEND_SWITCHING_ISR(yieldRequired);
        }
    }
}