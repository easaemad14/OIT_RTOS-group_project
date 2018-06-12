/*******************************************************************************
 * File:        cli.c
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This is the source file for Command Line Interface
 ******************************************************************************/
#include "cli.h"


/**
 * Private Variables
 */
// Common CLI Messages
static const char taskListHdr[] = "Name\t\tStat\tPri\tTCB\r\n";

// CLI commands
// TODO: Do these need their own function, or can I call an already used one?
static const xCommandLineInput xChangeMaxSpeedCommand = {"S",
        "S <n>: Change max Speed to n feet per second\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvChangeMaxSpeedCommand,
        1};

static const xCommandLineInput xChangeAccCommand = {"AP",
        "AP <n>: Change acceleration to n feet per squared second",
        (pdCOMMAND_LINE_CALLBACK)prvChangeAccCommand,
        1};

static const xCommandLineInput xSendToFloorCommand = {"SF",
        "SF <1/2/3>: Send elevator to corresponding floor",
        (pdCOMMAND_LINE_CALLBACK)prvSendToFloorCommand,
        1};

static const xCommandLineInput xEmergencyStopCommand = {"ES",
        "ES: Emergency Stop",
        (pdCOMMAND_LINE_CALLBACK)prvEmergencyStopCommand,
        0};

static const xCommandLineInput xEmergencyClearCommand = {"EC",
        "EC: Emergency Clear",
        (pdCOMMAND_LINE_CALLBACK)prvEmergencyClearCommand,
        0};

static const xCommandLineInput xTaskStatsCommand = {"TS",
        "TS: Displays a table of task state information\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvTaskStatsCommand,
        0};

static const xCommandLineInput xRunTimeStats = {"RTS",
        "RTS: Display Run Time Stats\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvRunTimeStats,
        0};


/**
 * Functions
 */
// Register all commands
void cli_init()
{
    FreeRTOS_CLIRegisterCommand(&xChangeMaxSpeedCommand);
    FreeRTOS_CLIRegisterCommand(&xChangeAccCommand);
    FreeRTOS_CLIRegisterCommand(&xSendToFloorCommand);
    FreeRTOS_CLIRegisterCommand(&xEmergencyStopCommand);
    FreeRTOS_CLIRegisterCommand(&xEmergencyClearCommand);
    FreeRTOS_CLIRegisterCommand(&xTaskStatsCommand);
    FreeRTOS_CLIRegisterCommand(&xRunTimeStats);
}

portBASE_TYPE prvChangeMaxSpeedCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    return pdFALSE;
}

portBASE_TYPE prvChangeAccCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    return pdFALSE;
}

portBASE_TYPE prvSendToFloorCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    return pdFALSE;
}

portBASE_TYPE prvEmergencyStopCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    return pdFALSE;
}

portBASE_TYPE prvEmergencyClearCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    return pdFALSE;
}

portBASE_TYPE prvTaskStatsCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    sprintf(pcWriteBuffer, taskListHdr);
    pcWriteBuffer += strlen(taskListHdr);
    vTaskList(pcWriteBuffer);

    return pdFALSE;
}

portBASE_TYPE prvRunTimeStats(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    return pdFALSE;
}
