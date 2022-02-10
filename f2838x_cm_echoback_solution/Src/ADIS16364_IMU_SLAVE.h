/*
 * This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
 * The corresponding license agreement applies. This hint shall not be removed.
 */

/**
 * \addtogroup ADIS16364_IMU_SLAVE ADIS16364_IMU_SLAVE
 * @{
 */

/**
\file ADIS16364_IMU_SLAVE.h
\brief ADIS16364_IMU_SLAVE function prototypes and defines

\version 1.0.0.11
 */

#ifndef _ADIS16364__IMU__SLAVE_H_
#define _ADIS16364__IMU__SLAVE_H_

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "ecatappl.h"

/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/

#endif //_ADIS16364__IMU__SLAVE_H_

// include custom application object dictionary
#include "ADIS16364_IMU_SLAVEObjects.h"

#if defined(_ADIS16364__IMU__SLAVE_) && (_ADIS16364__IMU__SLAVE_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
#define BIT_MASK 0x1U

typedef struct
{
    UINT16 XGyro_on;
    UINT16 YGyro_on;
    UINT16 ZGyro_on;
    UINT16 XAcc_on;
    UINT16 YAcc_on;
    UINT16 ZAcc_on;
    UINT16 XAngle_on;
    UINT16 YAngle_on;
    UINT16 ZAngle_on;
    UINT16 XLinVel_on;
    UINT16 YLinVel_on;
    UINT16 ZLinVel_on;
    UINT16 Temp_on;
    UINT16 HP_on;
} IMU_ECAT_CtrlNode_t;

typedef struct
{
    REAL32 XGyro_sense;
    REAL32 YGyro_sense;
    REAL32 ZGyro_sense;
    REAL32 XAcc_sense;
    REAL32 YAcc_sense;
    REAL32 ZAcc_sense;
    REAL32 XAngle_calc;
    REAL32 YAngle_calc;
    REAL32 ZAngle_calc;
    REAL32 XLinVel_calc;
    REAL32 YLinVel_calc;
    REAL32 ZLinVel_calc;
} IMU_ECAT_StatusNode_t;

//
// IPC Struct
//
typedef struct
{
    uint16_t exchangeDataFlag;
    uint16_t exchangeDataNum;
    IMU_ECAT_CtrlNode_t ctrlNode;
} ECAT_IPC_PutDataBuffer;

typedef struct
{
    uint16_t exchangeDataFlag;
    uint16_t exchangeDataNum;
    IMU_ECAT_StatusNode_t statusNode;
} ECAT_IPC_GetDataBuffer;

extern ECAT_IPC_PutDataBuffer ipcCMToCPUDataBuffer;
extern ECAT_IPC_GetDataBuffer ipcCPUToCMDataBuffer;

PROTO void APPL_Application(void);
#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

PROTO void APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize, UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16 *pData);
PROTO void APPL_OutputMapping(UINT16 *pData);

#undef PROTO
/** @}*/
