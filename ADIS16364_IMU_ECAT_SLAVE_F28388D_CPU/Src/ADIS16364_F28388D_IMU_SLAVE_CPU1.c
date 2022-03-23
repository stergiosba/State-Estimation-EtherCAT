/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup ADIS16364_F28388D_IMU_SLAVE_CPU1 ADIS16364_F28388D_IMU_SLAVE_CPU1
@{
*/

/**
\file ADIS16364_F28388D_IMU_SLAVE_CPU1.c
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
#include "device.h"

#define _ADIS16364__F28388_D__IMU__SLAVE__CPU1_ 1
#include "ADIS16364_F28388D_IMU_SLAVE_CPU1.h"
#undef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_
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

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
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

*////////////////////////////////////////////////////////////////////////////////////////

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

*////////////////////////////////////////////////////////////////////////////////////////

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
*////////////////////////////////////////////////////////////////////////////////////////

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

*////////////////////////////////////////////////////////////////////////////////////////

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
*////////////////////////////////////////////////////////////////////////////////////////

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

*////////////////////////////////////////////////////////////////////////////////////////

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
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;
   
#if MAX_PD_OUTPUT_SIZE > 0
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
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
    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
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
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
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
*////////////////////////////////////////////////////////////////////////////////////////
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
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16 *pData)
{
    uint16_t *pTmpData = pData;
    memcpy(&SUS_CONTROL0x7000.IMU_flags, pTmpData, SIZEOF(SUS_CONTROL0x7000.IMU_flags));
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application1(int16_t* counter)
{
    const uint16_t DC_MODE = bDcSyncActive;

    // Data from IMU to EtherCAT (sensing)
    SUS_SENSE0x6000.XGyro_sense = (*counter>0)?(*counter):0;
    SUS_SENSE0x6000.YGyro_sense = 2;
    SUS_SENSE0x6000.ZGyro_sense = 3;

    SUS_SENSE0x6000.XAcc_sense = 0;
    SUS_SENSE0x6000.YAcc_sense = 0;
    SUS_SENSE0x6000.ZAcc_sense = 0;

    SUS_SENSE0x6000.XAngle_calc = 7;
    SUS_SENSE0x6000.YAngle_calc = 8;
    SUS_SENSE0x6000.ZAngle_calc = 9;

    SUS_SENSE0x6000.XLinVel_calc = 10;
    SUS_SENSE0x6000.YLinVel_calc = 11;
    SUS_SENSE0x6000.ZLinVel_calc = 12;
    *counter = -(*counter);
    //DEVICE_DELAY_US(370);

}

void APPL_Application2(void)
{
    const uint16_t DC_MODE = bDcSyncActive;

    // Data from IMU to EtherCAT (sensing)
    SUS_SENSE0x6000.XGyro_sense = 0;
    SUS_SENSE0x6000.YGyro_sense = 0;
    SUS_SENSE0x6000.ZGyro_sense = 0;

    SUS_SENSE0x6000.XAcc_sense = 1;
    SUS_SENSE0x6000.YAcc_sense = 2;
    SUS_SENSE0x6000.ZAcc_sense = 3;

    SUS_SENSE0x6000.XAngle_calc = 7;
    SUS_SENSE0x6000.YAngle_calc = 8;
    SUS_SENSE0x6000.ZAngle_calc = 9;

    SUS_SENSE0x6000.XLinVel_calc = 10;
    SUS_SENSE0x6000.YLinVel_calc = 11;
    SUS_SENSE0x6000.ZLinVel_calc = 12;

    DEVICE_DELAY_US(500);
}

void APPL_Application3(void)
{
    const uint16_t DC_MODE = bDcSyncActive;

    // Data from IMU to EtherCAT (sensing)
    SUS_SENSE0x6000.XGyro_sense = 1;
    SUS_SENSE0x6000.YGyro_sense = 2;
    SUS_SENSE0x6000.ZGyro_sense = 3;

    SUS_SENSE0x6000.XAcc_sense = 4;
    SUS_SENSE0x6000.YAcc_sense = 5;
    SUS_SENSE0x6000.ZAcc_sense = 6;

    SUS_SENSE0x6000.XAngle_calc = 7;
    SUS_SENSE0x6000.YAngle_calc = 8;
    SUS_SENSE0x6000.ZAngle_calc = 9;

    SUS_SENSE0x6000.XLinVel_calc = 10;
    SUS_SENSE0x6000.YLinVel_calc = 11;
    SUS_SENSE0x6000.ZLinVel_calc = 12;
    DEVICE_DELAY_US(500);
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Read the Explicit Device ID (from an external ID switch)
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
   #pragma message ("Warning: Implement explicit Device ID latching")
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

*////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
    /* initialize the Hardware and the EtherCAT Slave Controller */

    HW_Init();
    MainInit();
    bRunApplication = TRUE;
    do
    {
        MainLoop();
        
    } while (bRunApplication == TRUE);

    HW_Release();
}
#endif //#if USE_DEFAULT_MAIN
/** @} */

