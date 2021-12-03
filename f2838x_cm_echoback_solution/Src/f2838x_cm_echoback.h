//###########################################################################
//
// FILE:   f2838x_cm_echoback.h
//
// TITLE:  F2838x CM Echoback Header
//
//###########################################################################
// $TI Release: F2838x EtherCAT Software v2.01.00.00 $
// $Release Date: August 31 2020 $
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2838X_CM_ECHO_BACK_H
#define F2838X_CM_ECHO_BACK_H

//
// Included Files
//
#include "ecat_def.h"
#include "ecatappl.h"
#include "f2838x_cm_echobackobjects.h"

#endif // F2838X_CM_ECHO_BACK_H

//
// Defines
//
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif

#define BIT_MASK  0x1U
#define BYTE_MASK 0xFFU

//
// Function Prototypes
//

//*****************************************************************************
//
// Mainloop Application Function
//
// This function for this application loops back the output data to the input
// data for the EtherCAT Master to read.
//
// Returns - None
//
//*****************************************************************************
PROTO void APPL_Application(void);

//*****************************************************************************
//
// Get Device ID
//
// This function returns the explicit device ID.
//
// Returns - Explicit device ID
//
//*****************************************************************************
#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

//*****************************************************************************
//
// Acknowledge Error Function
//
// stateTrans indicates the current state transition
//
// This function for this application performs no action however it will get
// called when the master acknowledges an error.
//
// Returns - None
//
//*****************************************************************************
PROTO void APPL_AckErrorInd(UINT16 stateTrans);

//*****************************************************************************
//
// Start Mailbox Handler
//
// This function is called during the state transition from INIT to PREOP and
// performs no action for this application.
//
// Returns - Application Layer Status Code - ALSTATUSCODE_NOERROR
//
//*****************************************************************************
PROTO UINT16 APPL_StartMailboxHandler(void);

//*****************************************************************************
//
// Stop Mailbox Handler
//
// This function is called during the state transition from PREOP to INIT and
// performs no action for this application.
//
// Returns - Application Layer Status Code - ALSTATUSCODE_NOERROR
//
//*****************************************************************************
PROTO UINT16 APPL_StopMailboxHandler(void);

//*****************************************************************************
//
// Start Input Handler
//
// pIntMask is current value of the AL Event Mask
//
// This function is called during the state transition from PREOP to SAFEOP and
// performs no action for this application.
//
// Returns - Application Layer Status Code - ALSTATUSCODE_NOERROR
//
//*****************************************************************************
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);

//*****************************************************************************
//
// Stop Input Handler
//
// This function is called during the state transition from SAFEOP to PREOP and
// performs no action for this application.
//
// Returns - Application Layer Status Code - ALSTATUSCODE_NOERROR
//
//*****************************************************************************
PROTO UINT16 APPL_StopInputHandler(void);

//*****************************************************************************
//
// Start Output Handler
//
// This function is called during the state transition from SAFEOP to OP and
// performs no action for this application.
//
// Returns - Application Layer Status Code - ALSTATUSCODE_NOERROR
//
//*****************************************************************************
PROTO UINT16 APPL_StartOutputHandler(void);

//*****************************************************************************
//
// Stop Output Handler
//
// This function is called during the state transition from OP to SAFEOP and
// performs no action for this application.
//
// Returns - Application Layer Status Code - ALSTATUSCODE_NOERROR
//
//*****************************************************************************
PROTO UINT16 APPL_StopOutputHandler(void);

//*****************************************************************************
//
// Calculate the Process Data Sizes
//
// pInputSize is a pointer to store the input process data size
// pOutputSize is a pointer to store the output process data size
//
// This function is called during the state transition from PREOP to SAFEOP and
// calculates the process data size in bytes for both input and output process
// data.
//
// Returns - Application Layer Status Codes
//           ALSTATUSCODE_NOERROR - No error
//           ALSTATUSCODE_INVALIDOUTPUTMAPPING - Output mapping error
//           ALSTATUSCODE_INVALIDINPUTMAPPING - Input mapping error
//
//*****************************************************************************
PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize, UINT16 *pOutputSize);

//*****************************************************************************
//
// Maps the Input Process Data to Generic Stack
//
// pIntMask is the pointer to the input process data destination
//
// This function is called after the application call to map the input process
// data from local device memory to the generic stack (ESC memory).
//
// Returns - None
//
//*****************************************************************************
PROTO void APPL_InputMapping(UINT16 *pData);

//*****************************************************************************
//
// Maps the Output Process Data to Generic Stack
//
// pIntMask is the pointer to the output process data
//
// This function is called before the application call to copy the output
// process data from the generic stack (ESC memory) to local device memory.
//
// Returns - None
//
//*****************************************************************************
PROTO void APPL_OutputMapping(UINT16 *pData);

#undef PROTO

//
// End of File
//
