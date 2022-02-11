/*
 * ECAT_init.h
 *
 *  Created on: 8 December 2021
 *      Author: Stergios Bachoumas
 */

#ifndef ECAT_INIT_H_
#define ECAT_INIT_H_

#include "device.h"


#define ESCSS_LOOP_TIMEOUT       0x300U
#define ALLOCATE_TO_CM           0x1U
#define ESC_USE_INT_PHY_CLK      0x1U

#define BOOT_KEY                 0x5A000000UL
#define CM_BOOT_FREQ_125MHZ      0x7D00U
#define BOOTMODE_BOOT_TO_WAIT    0x0U
#define BOOTMODE_BOOT_TO_RAM     0x5U
#define BOOTMODE_BOOT_TO_FLASH   0x3U

#define CCARD_LED_1_GPIO         31U
#define CCARD_LED_2_GPIO         34U
#define CCARD_ECAT_RUN_LED_GPIO  146U
#define CCARD_ECAT_ERR_LED_GPIO  145U

typedef struct
{
    uint16_t XGyro_on;
    uint16_t YGyro_on;
    uint16_t ZGyro_on;
    uint16_t XAcc_on;
    uint16_t YAcc_on;
    uint16_t ZAcc_on;
    uint16_t XAngle_on;
    uint16_t YAngle_on;
    uint16_t ZAngle_on;
    uint16_t XLinVel_on;
    uint16_t YLinVel_on;
    uint16_t ZLinVel_on;
    uint16_t Temp_on;
    uint16_t HP_on;
}IMU_ECAT_CtrlNode_t;

typedef struct
{
    float XGyro_sense;
    float YGyro_sense;
    float ZGyro_sense;
    float XAcc_sense;
    float YAcc_sense;
    float ZAcc_sense;
    float Temp_sense;
    float XAngle_calc;
    float YAngle_calc;
    float ZAngle_calc;
    float XLinVel_calc;
    float YLinVel_calc;
    float ZLinVel_calc;
}IMU_ECAT_StatusNode_t;

//
// IPC Struct
//
typedef struct
{
    uint16_t        exchangeDataFlag;
    uint16_t        exchangeDataNum;
    IMU_ECAT_CtrlNode_t ctrlNode;
}IMU_ECAT_IPC_GetDataBuffer;

typedef struct
{
    uint16_t          exchangeDataFlag;
    uint16_t          exchangeDataNum;
    IMU_ECAT_StatusNode_t statusNode;
}IMU_ECAT_IPC_PutDataBuffer;

/*extern ECAT_IPC_PutDataBuffer ipcCMToCPUDataBuffer;
extern ECAT_IPC_GetDataBuffer ipcCPUToCMDataBuffer;
*/


void ECAT_init(void);
void setupESCGPIOs(void);

#endif /* ECAT_INIT_H_ */
