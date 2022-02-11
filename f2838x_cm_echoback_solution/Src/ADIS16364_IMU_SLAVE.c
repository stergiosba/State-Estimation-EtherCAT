/*
 * This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
 * The corresponding license agreement applies. This hint shall not be removed.
 */

/**
\addtogroup ADIS16364_IMU_SLAVE ADIS16364_IMU_SLAVE
@{
*/

/**
\file ADIS16364_IMU_SLAVE.c
\brief Implementation
 Created with SSC Tool application parser 1.6.2.0
\version 0.0.0.1
*/

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "applInterface.h"

#define _ADIS16364__IMU__SLAVE_ 1
#include "ADIS16364_IMU_SLAVE.h"
#undef _ADIS16364__IMU__SLAVE_

/*--------------------------------------------------------------------------------------
------
------    global types and defines
------
--------------------------------------------------------------------------------------*/

#pragma DATA_SECTION(ipcCMToCPUDataBuffer, "MSGRAM_CM_TO_CPU1_ECAT")
ECAT_IPC_PutDataBuffer ipcCMToCPUDataBuffer;

#pragma DATA_SECTION(ipcCPUToCMDataBuffer, "MSGRAM_CPU1_TO_CM_ECAT")
ECAT_IPC_GetDataBuffer ipcCPUToCMDataBuffer;

/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*/
///////////////////////////////////////////////////////////////////////////////////////

void APPL_AckErrorInd(UINT16 stateTrans)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*/
///////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*/
///////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                       register (0x204) when this function is succeeded. The event mask can be adapted
                       in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete
           the transition by calling ECAT_StateChange.
*/
///////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*/
///////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete
           the transition by calling ECAT_StateChange.
*/
///////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*/
///////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*/
///////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize, UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM *pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;

#if MAX_PD_OUTPUT_SIZE > 0
    /*Scan object 0x1C12 RXPDO assign*/
    for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if (pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for (PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt + 1), pPDO) >> 4)); // goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16)((*pPDOEntry) & 0xFF);
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;
#endif

#if MAX_PD_INPUT_SIZE > 0
    if (result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if (pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for (PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt + 1), pPDO) >> 4)); // goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16)((*pPDOEntry) & 0xFF);
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;
#endif

#else
#if _WIN32
#pragma message("Warning: Define 'InputSize' and 'OutputSize'.")
#else
#warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*/
///////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16 *pData)
{
    uint16_t *pTmpData = pData;
    //Gyroscope Sense
    memcpy(pTmpData, &SUS_SENSE0x6000.XGyro_sense, SIZEOF(SUS_SENSE0x6000.XGyro_sense));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.YGyro_sense, SIZEOF(SUS_SENSE0x6000.YGyro_sense));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.ZGyro_sense, SIZEOF(SUS_SENSE0x6000.ZGyro_sense));
    pTmpData += 2U;

    //Accelerometer Sense
    memcpy(pTmpData, &SUS_SENSE0x6000.XAcc_sense, SIZEOF(SUS_SENSE0x6000.XAcc_sense));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.YAcc_sense, SIZEOF(SUS_SENSE0x6000.YAcc_sense));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.ZAcc_sense, SIZEOF(SUS_SENSE0x6000.ZAcc_sense));
    pTmpData += 2U;

    //Temperature Sense
    memcpy(pTmpData, &SUS_SENSE0x6000.Temp_sense, SIZEOF(SUS_SENSE0x6000.Temp_sense));
    pTmpData += 2U;

    //Angle Calculation
    memcpy(pTmpData, &SUS_SENSE0x6000.XAngle_calc, SIZEOF(SUS_SENSE0x6000.XAngle_calc));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.YAngle_calc, SIZEOF(SUS_SENSE0x6000.YAngle_calc));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.ZAngle_calc, SIZEOF(SUS_SENSE0x6000.ZAngle_calc));
    pTmpData += 2U;

    //Linear Velocity Calculation
    memcpy(pTmpData, &SUS_SENSE0x6000.XLinVel_calc, SIZEOF(SUS_SENSE0x6000.XLinVel_calc));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.YLinVel_calc, SIZEOF(SUS_SENSE0x6000.YLinVel_calc));
    pTmpData += 2U;
    memcpy(pTmpData, &SUS_SENSE0x6000.ZLinVel_calc, SIZEOF(SUS_SENSE0x6000.ZLinVel_calc));
    /*
    uint16_t *pTmpData = (uint16_t *)pData;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.XGyro_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.YGyro_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.ZGyro_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.XAcc_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.YAcc_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.ZAcc_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.Temp_sense;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.XAngle_calc;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.YAngle_calc;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.ZAngle_calc;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.XLinVel_calc;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.YLinVel_calc;
    pTmpData += 2;
    *(volatile float *)pTmpData = SUS_SENSE0x6000.ZLinVel_calc;*/
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*/
///////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16 *pData)
{
    uint16_t *pTmpData = pData;
    //TODO CHANGE TO BOOLS AND TEST- kanoo
    SUS_CONTROL0x7000.XGyro_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.YGyro_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.ZGyro_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.XAcc_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.YAcc_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.ZAcc_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.XAngle_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.YAngle_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.ZAngle_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.XLinVel_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.YLinVel_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.ZLinVel_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.Temp_on = *(volatile UINT16 *)pTmpData;
    pTmpData += 1U;
    SUS_CONTROL0x7000.HP_on = *(volatile UINT16 *)pTmpData;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR
            or from the mainloop if no synchronisation is supported
*/
///////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
    // Data from EtherCAT to IMU (control checks)
    ipcCMToCPUDataBuffer.ctrlNode.XGyro_on = SUS_CONTROL0x7000.XGyro_on;
    ipcCMToCPUDataBuffer.ctrlNode.YGyro_on = SUS_CONTROL0x7000.YGyro_on;
    ipcCMToCPUDataBuffer.ctrlNode.ZGyro_on = SUS_CONTROL0x7000.ZGyro_on;

    ipcCMToCPUDataBuffer.ctrlNode.XAcc_on = SUS_CONTROL0x7000.XAcc_on;
    ipcCMToCPUDataBuffer.ctrlNode.YAcc_on = SUS_CONTROL0x7000.YAcc_on;
    ipcCMToCPUDataBuffer.ctrlNode.ZAcc_on = SUS_CONTROL0x7000.ZAcc_on;

    ipcCMToCPUDataBuffer.ctrlNode.XAngle_on = SUS_CONTROL0x7000.XAngle_on;
    ipcCMToCPUDataBuffer.ctrlNode.YAngle_on = SUS_CONTROL0x7000.YAngle_on;
    ipcCMToCPUDataBuffer.ctrlNode.ZAngle_on = SUS_CONTROL0x7000.ZAngle_on;

    ipcCMToCPUDataBuffer.ctrlNode.XLinVel_on = SUS_CONTROL0x7000.XLinVel_on;
    ipcCMToCPUDataBuffer.ctrlNode.YLinVel_on = SUS_CONTROL0x7000.YLinVel_on;
    ipcCMToCPUDataBuffer.ctrlNode.ZLinVel_on = SUS_CONTROL0x7000.ZLinVel_on;

    // Data from IMU to EtherCAT (sensing)
    SUS_SENSE0x6000.XGyro_sense = ipcCPUToCMDataBuffer.statusNode.XGyro_sense;
    SUS_SENSE0x6000.YGyro_sense = ipcCPUToCMDataBuffer.statusNode.YGyro_sense;
    SUS_SENSE0x6000.ZGyro_sense = ipcCPUToCMDataBuffer.statusNode.ZGyro_sense;

    SUS_SENSE0x6000.XAcc_sense = ipcCPUToCMDataBuffer.statusNode.XAcc_sense;
    SUS_SENSE0x6000.YAcc_sense = ipcCPUToCMDataBuffer.statusNode.YAcc_sense;
    SUS_SENSE0x6000.ZAcc_sense = ipcCPUToCMDataBuffer.statusNode.ZAcc_sense;

    SUS_SENSE0x6000.XAngle_calc = ipcCPUToCMDataBuffer.statusNode.XAngle_calc;
    SUS_SENSE0x6000.YAngle_calc = ipcCPUToCMDataBuffer.statusNode.YAngle_calc;
    SUS_SENSE0x6000.ZAngle_calc = ipcCPUToCMDataBuffer.statusNode.ZAngle_calc;

    SUS_SENSE0x6000.XLinVel_calc = ipcCPUToCMDataBuffer.statusNode.XLinVel_calc;
    SUS_SENSE0x6000.YLinVel_calc = ipcCPUToCMDataBuffer.statusNode.YLinVel_calc;
    SUS_SENSE0x6000.ZLinVel_calc = ipcCPUToCMDataBuffer.statusNode.ZLinVel_calc;
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Read the Explicit Device ID (from an external ID switch)
*/
///////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
#pragma message("Warning: Implement explicit Device ID latching")
#else
#warning "Implement explicit Device ID latching"
#endif
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif

#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*/
///////////////////////////////////////////////////////////////////////////////////////
#if _PIC24 && EL9800_HW
int main(void)
#elif _WIN32
int main(int argc, char *argv[])
#else
void main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
#if FC1100_HW
#if _WIN32
    u16FcInstance = 0;
    if (argc > 1)
    {
        u16FcInstance = atoi(argv[1]);
    }
#endif
    if (HW_Init())
    {
        HW_Release();
        return;
    }
#else
    HW_Init();
#endif
    MainInit();

    bRunApplication = TRUE;
    do
    {
        MainLoop();

    } while (bRunApplication == TRUE);

    HW_Release();
#if _PIC24
    return 0;
#endif
}
#endif //#if USE_DEFAULT_MAIN
/** @} */
