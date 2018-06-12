#pragma once
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING 1
#endif
#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif

/*******************************************************************************
 * File:        uartdrv.h
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This is the header file for uartdrv.c, containing all of the 
 *              needed goodies.
 ******************************************************************************/
#include <plib.h>
#include <stdint.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"

#define UART_BAUD_RATE 9600
#define UART_DELAY 2 / portTICK_RATE_MS
#define UART_MAX_BUFFER_SIZE 128 // For any RX/TX buffers

/**
 * Functions
 */
void initUART(UART_MODULE umPortNum, uint32_t ui32WantedBaud);
void vUartPutC(UART_MODULE umPortNum, char cByte);
void vUartPutStr(UART_MODULE umPortNum, char *pString, int iStrLen);