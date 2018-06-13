/*******************************************************************************
 * File:        uart.c
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This file implements UART RX and TX tasks for user serial IO
 ******************************************************************************/
#include "uart.h"


/**
 * Local Variables
 */
TaskHandle_t uart_rx_handle;
QueueHandle_t uart_tx_queue;
extern QueueHandle_t e1_queue;

/**
 * Functions
 */
// RX task is responsible for receiving chars (from ISR) and sending to TX
void uartRxTask(void *params)
{
    char in; // We receive one character at a time
    
    while(1) {
        vTaskSuspend(NULL);
        
        in = UARTGetChar();
        if(uart_tx_queue != NULL) {
            xQueueSendToBack(uart_tx_queue, (void*)&in, (TickType_t)5);
        }
    }
}

// TX task receives all input via queue and makes smart decisions
// If valid operation, either call elevator queue or CLI
void uartTxTask(void *params)
{
    char tx_buf[UART_MAX_BUFFER_SIZE];
    memset(tx_buf, 0, sizeof(tx_buf));
    char cli_msg[UART_MAX_BUFFER_SIZE];
    memset(cli_msg, 0, sizeof(cli_msg));
    char cli_buf[UART_MAX_BUFFER_SIZE]; // Return from CLI function call
    memset(cli_buf, 0, sizeof(cli_buf));
    uint8_t cli_pos = 0;
    uint8_t op;
    portBASE_TYPE cont; // Continue processing commands?
    
    // Create our queue
    uart_tx_queue = xQueueCreate(UART_MAX_BUFFER_SIZE, 
            UART_MAX_BUFFER_SIZE * sizeof(char));
    if(uart_tx_queue == NULL) {
        for(;;);
    }
    
    while(1) {
        // Receive a char in blocking manner
        if(xQueueReceive(uart_tx_queue, &tx_buf, (TickType_t)portMAX_DELAY)) {
            // Transmit the byte regardless
            vUartPutC(UART1, tx_buf[0]);
            
            // Let's figure out what the user is trying to do
            if(tx_buf[0] == '\r') { // Make CLI call
                // Transmit a newline
                vUartPutC(UART1, '\n');
                
                // Null terminate our string and process CLI
                cli_msg[cli_pos] = '\0';
                do {
                    cont = FreeRTOS_CLIProcessCommand(cli_msg, cli_buf,
                            sizeof(cli_buf));
                    vUartPutStr(UART1, cli_buf);
                } while(cont != pdFALSE);
                
                // Transmit another newline for the heck of it and clean
                vUartPutC(UART1, '\r');
                vUartPutC(UART1, '\n');
                memset(cli_msg, 0, sizeof(cli_buf));
            } else if(islower(tx_buf[0])) { // "button" operation
                if(tx_buf[0] == 'z')        op = GD_UP;
                else if(tx_buf[0] == 'x')   op = P1_DN;
                else if(tx_buf[0] == 'c')   op = P1_UP;
                else if(tx_buf[0] == 'v')   op = P2_DN;
                else if(tx_buf[0] == 'b')   op = EMER_STP;
                else if(tx_buf[0] == 'n')   op = EMER_CLR;
                else if(tx_buf[0] == 'm')   op = DOOR_INT;
                
                xQueueSendToBack(e1_queue, (void*)&op, (TickType_t)10);
            } else if(isupper(tx_buf[0])) { // Otherwise, CLI
                cli_msg[cli_pos++] = tx_buf[0];
            } else if((tx_buf[0] == ' ') || isdigit(tx_buf[0])) { // CLI?
                cli_msg[cli_pos++] = tx_buf[0];
            }
            
            memset(tx_buf, 0, sizeof(tx_buf));
        }
    }
}

// Create our tasks 
void create_uart(void)
{
    if(xTaskCreate(uartRxTask, "receive", configMINIMAL_STACK_SIZE,
            NULL, 3, &uart_rx_handle) != pdPASS) {
        for(;;);
    }
    if(xTaskCreate(uartTxTask, "transmit", configMINIMAL_STACK_SIZE,
            NULL, 2, NULL) != pdPASS) {
        for(;;);
    }
}