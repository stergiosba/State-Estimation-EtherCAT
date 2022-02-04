/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
 * \addtogroup ADIS16364F28388DIMUECATSlave ADIS16364 F28388D IMU ECAT Slave
 * @{
 */

/**
\file ADIS16364 F28388D IMU ECAT Slave.h
\brief ADIS16364 F28388D IMU ECAT Slave function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _ADIS16364_F28388_D_IMU_ECAT_SLAVE_H_
#define _ADIS16364_F28388_D_IMU_ECAT_SLAVE_H_


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

#endif //_ADIS16364_F28388_D_IMU_ECAT_SLAVE_H_

//include custom application object dictionary 
#include "ADIS16364 F28388D IMU ECAT SlaveObjects.h"


#if defined(_ADIS16364_F28388_D_IMU_ECAT_SLAVE_) && (_ADIS16364_F28388_D_IMU_ECAT_SLAVE_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif

#define BIT_MASK        0x1U

typedef struct
{
    BOOL XGyro_on;
    BOOL YGyro_on;
    BOOL ZGyro_on;
    BOOL XAcc_on;
    BOOL YAcc_on;
    BOOL ZAcc_on;
    BOOL XAngle_on;
    BOOL YAngle_on;
    BOOL ZAngle_on;
    BOOL XLinVel_on;
    BOOL YLinVel_on;
    BOOL ZLinVel_on;
    BOOL Temp_on;
}IMU_ECAT_CtrlNode_t;

typedef struct
{
    REAL32 XGyro_sence;
    REAL32 YGyro_sence;
    REAL32 ZGyro_sence;
    REAL32 XAcc_sence;
    REAL32 YAcc_sence;
    REAL32 ZAcc_sence;
    REAL32 XAngle_calc;
    REAL32 YAngle_calc;
    REAL32 ZAngle_calc;
    REAL32 XLinVel_calc;
    REAL32 YLinVel_calc;
    REAL32 ZLinVel_calc;
}IMU_ECAT_StatusNode_t;

//
// IPC Struct
//
typedef struct
{
    uint16_t                exchangeDataFlag;
    uint16_t                exchangeDataNum;
    IMU_ECAT_CtrlNode_t     ctrlNode;
}ECAT_IPC_PutDataBuffer;

typedef struct
{
    uint16_t                exchangeDataFlag;
    uint16_t                exchangeDataNum;
    IMU_ECAT_StatusNode_t   statusNode;
}ECAT_IPC_GetDataBuffer;

extern ECAT_IPC_PutDataBuffer ipcCMToCPUDataBuffer;
extern ECAT_IPC_GetDataBuffer ipcCPUToCMDataBuffer;


PROTO void APPL_Application(void);
#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

PROTO void   APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16* pData);
PROTO void APPL_OutputMapping(UINT16* pData);
PROTO void PDO_ResetOutputs(void);

#undef PROTO
/** @}*/

