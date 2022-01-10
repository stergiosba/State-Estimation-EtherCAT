/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
 * \addtogroup NEWECATSlave NEWECAT Slave
 * @{
 */

/**
\file NEWECAT Slave.h
\brief NEWECAT Slave function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _NEWECAT_SLAVE_H_
#define _NEWECAT_SLAVE_H_


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

#endif //_NEWECAT_SLAVE_H_

//include custom application object dictionary 
#include "NEWECAT SlaveObjects.h"


#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif

typedef struct
{
    REAL64 sw1;
    REAL64 sw2;
    REAL64 sw3;
    REAL64 sw4;
}ECAT_CtrlNode_t;

typedef struct
{
    REAL64 led1;
    REAL64 led2;
    REAL64 led3;
    REAL64 led4;
}ECAT_StatusNode_t;

//
// IPC Struct
//
typedef struct
{
    uint16_t        exchangeDataFlag;
    uint16_t        exchangeDataNum;
    ECAT_CtrlNode_t ctrlNode;
}ECAT_IPC_PutDataBuffer;

typedef struct
{
    uint16_t          exchangeDataFlag;
    uint16_t          exchangeDataNum;
    ECAT_StatusNode_t statusNode;
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

#undef PROTO
/** @}*/
