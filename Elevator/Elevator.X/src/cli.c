/*******************************************************************************
 * File:        cli.c
 * Author:      Charles Bassinger
 *              charles.bassinger@oit.edu
 * 
 * Description: This is the source file for Command Line Interface
 ******************************************************************************/
#include "cli.h"


// Elevator settings
#define MIN_VEL 5
#define MAX_VEL 20
#define MIN_ACC 1
#define MAX_ACC 4


/**
 * Private Variables
 */
// Common CLI Messages
static const char taskListHdr[] = "Name\t\tStat\tPri\tTCB\r\n";
static const char runTimeStatsMsg[] = "Everything is groovy, brah!\r\n";
extern struct elevator E1;
QueueHandle_t e1_queue;
uint8_t q_mess; // Need address


// CLI commands
// TODO: Do these need their own function, or can I call an already used one?
static const xCommandLineInput xChangeMaxSpeedCommand = {"S",
        "S <n>: Change max Speed to n feet per second\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvChangeMaxSpeedCommand,
        1};

static const xCommandLineInput xChangeAccCommand = {"AP",
        "AP <n>: Change acceleration to n feet per squared second\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvChangeAccCommand,
        1};

static const xCommandLineInput xSendToFloorCommand = {"SF",
        "SF <1/2/3>: Send elevator to corresponding floor\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvSendToFloorCommand,
        1};

static const xCommandLineInput xEmergencyStopCommand = {"ES",
        "ES: Emergency Stop\r\n",
        (pdCOMMAND_LINE_CALLBACK)prvEmergencyStopCommand,
        0};

static const xCommandLineInput xEmergencyClearCommand = {"EC",
        "EC: Emergency Clear\r\n",
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

// This is the only function that modifies this variable; no race conditions
portBASE_TYPE prvChangeMaxSpeedCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    int8_t *param;
    portBASE_TYPE param_len;
    uint8_t newVel;
    
    // Get param, convert to int, and set if valid
    param = FreeRTOS_CLIGetParameter(pcCommandString, 1, &param_len);
    param[param_len] = 0;
    
    newVel = atoi(param);
    
    if((newVel > MIN_VEL) && (newVel < MAX_VEL)) {
        E1.abs_vel = newVel;
    }
    
    return pdFALSE;
}

// Just set it, breh
portBASE_TYPE prvChangeAccCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    int8_t *param;
    portBASE_TYPE param_len;
    uint8_t newAcc;
    
    param = FreeRTOS_CLIGetParameter(pcCommandString, 1, &param_len);
    param[param_len] = 0;
    
    newAcc = atoi(param);

    if((newAcc > MIN_ACC) && (newAcc < MAX_ACC)) {
        E1.abs_acc = newAcc;
    }
    
    return pdFALSE;
}

// Send the elevator to this floor
portBASE_TYPE prvSendToFloorCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    int8_t *param;
    portBASE_TYPE param_len, result;
    uint8_t floor;
    
    param = FreeRTOS_CLIGetParameter(pcCommandString, 1, &param_len);
    param[param_len] = 0;
    
    floor = atoi(param);
    
    switch(floor) {
        case 1:
            q_mess = GD_CALL;
            break;
        case 2:
            q_mess = P1_CALL;
            break;
        case 3:
            q_mess = P2_CALL;
            break;
        default:
            return pdFALSE;
    }
    
    if(e1_queue != NULL) {
        xQueueSendToBack(e1_queue, (void*)&q_mess, (TickType_t)portMAX_DELAY);
    }
    
    return pdFALSE;
}

// Hammer time
portBASE_TYPE prvEmergencyStopCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    q_mess = EMER_STP;
    if(e1_queue != NULL) {
        xQueueSendToBack(e1_queue, (void*)&q_mess, (TickType_t)portMAX_DELAY);
    }
    
    return pdFALSE;
}

// We good now
portBASE_TYPE prvEmergencyClearCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    q_mess = EMER_CLR;
    if(e1_queue != NULL) {
        xQueueSendToBack(e1_queue, (void*)&q_mess, (TickType_t)portMAX_DELAY);
    }
    
    return pdFALSE;
}

// Write task stats
portBASE_TYPE prvTaskStatsCommand(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
    sprintf(pcWriteBuffer, taskListHdr);
    pcWriteBuffer += strlen(taskListHdr);
    vTaskList(pcWriteBuffer);

    return pdFALSE;
}

// Write RTS
portBASE_TYPE prvRunTimeStats(int8_t *pcWriteBuffer, 
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{
#if 0
    vTaskGetRunTimeStats(pcWriteBuffer);
#else
    sprintf(pcWriteBuffer, runTimeStatsMsg);
#endif
    
    return pdFALSE;
}
