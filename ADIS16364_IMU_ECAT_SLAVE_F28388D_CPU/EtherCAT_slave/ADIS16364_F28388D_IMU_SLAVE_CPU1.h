/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
 * \addtogroup ADIS16364_F28388D_IMU_SLAVE_CPU1 ADIS16364_F28388D_IMU_SLAVE_CPU1
 * @{
 */

/**
\file ADIS16364_F28388D_IMU_SLAVE_CPU1.h
\brief ADIS16364_F28388D_IMU_SLAVE_CPU1 function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_H_
#define _ADIS16364__F28388_D__IMU__SLAVE__CPU1_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"
#include "ecatappl.h"
#include "applInterface.h"
#include "device.h"
#include "ADIS16364.h"
/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/

#endif //_ADIS16364__F28388_D__IMU__SLAVE__CPU1_H_

//include custom application object dictionary 
#include "ADIS16364_F28388D_IMU_SLAVE_CPU1Objects.h"


#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif

PROTO void APPL_Application(void);

#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

PROTO void   Application_Delay_Control(float delay, uint32_t CycleFreq, uint16_t Taps);
PROTO void   Internal_Reset(void);
PROTO void   InputPDO_Zeros(void);
PROTO void   InputPDO_ForwardPass(void);
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

