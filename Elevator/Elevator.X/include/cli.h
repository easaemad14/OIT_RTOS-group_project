#pragma once
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING 1
#endif
#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif

/*******************************************************************************
 * File:        cli.h
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This is the header file for Command Line Interface
 ******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <string.h>

// NOTE: Order here matters! The CLI header assumes definitions -_-
#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "leddrv.h"
#include "elevator.h"


void cli_init();

portBASE_TYPE prvChangeMaxSpeedCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);

portBASE_TYPE prvChangeAccCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);

portBASE_TYPE prvSendToFloorCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);

portBASE_TYPE prvEmergencyStopCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);

portBASE_TYPE prvEmergencyClearCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);

portBASE_TYPE prvTaskStatsCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);

portBASE_TYPE prvRunTimeStats(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString);