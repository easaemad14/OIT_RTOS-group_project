#pragma once
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING 1
#endif
#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif

/*******************************************************************************
 * File:        uart.h
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This is the header file for uart RX and TX tasks.
 ******************************************************************************/
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "FreeRTOS.h"
#include "task.h"
#include "uartdrv.h"
#include "queue.h"
#include "elevator.h"

void create_uart(void);