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
#define _ADIS16364__F28388_D__IMU__SLAVE__CPU1_ 1
#include <ADIS16364_F28388D_IMU_SLAVE_CPU1.h>
#undef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_
#include "CLA_shared.h"
#include "math.h"
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
#pragma DATA_SECTION(g_SensBurst, "Cla1ToCpuMsgRAM")
float g_SensBurst[11] = { 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f };

#pragma DATA_SECTION(g_Attitude, "Cla1ToCpuMsgRAM")
float g_Attitude[3] = { 0.0f, 0.0f, 0.0f };

uint32_t g_biascounter[1] = {0};
uint32_t CycleTime;
uint32_t CycleFreq;

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
 \brief    This function resets the input PDOs to zero.

*////////////////////////////////////////////////////////////////////////////////////////

void    InputPDO_Reset()
{
    LAE_SENSE0x6000.XGyro = 0;
    LAE_SENSE0x6000.YGyro = 0;
    LAE_SENSE0x6000.ZGyro = 0;

    LAE_SENSE0x6000.XAcc = 0;
    LAE_SENSE0x6000.YAcc = 0;
    LAE_SENSE0x6000.ZAcc = 0;

    LAE_SENSE0x6000.XTemp = 0;
    LAE_SENSE0x6000.YTemp = 0;
    LAE_SENSE0x6000.ZTemp = 0;

    LAE_ESTIMATE0x6002.XAngle = 0;
    LAE_ESTIMATE0x6002.YAngle = 0;
    LAE_ESTIMATE0x6002.ZAngle = 0;
} // End InputPDO_Reset()


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function performs a forward pass of EtherCAT Input PDOs.

*////////////////////////////////////////////////////////////////////////////////////////
void    InputPDO_ForwardPass()
{
    LAE_SENSE0x6000.XGyro = g_SensBurst[1];
    LAE_SENSE0x6000.YGyro = g_SensBurst[2];
    LAE_SENSE0x6000.ZGyro = g_SensBurst[3];

    LAE_SENSE0x6000.XAcc = g_SensBurst[4];
    LAE_SENSE0x6000.YAcc = g_SensBurst[5];
    LAE_SENSE0x6000.ZAcc = g_SensBurst[6];

    LAE_SENSE0x6000.XTemp = 25.0f+g_SensBurst[7];
    LAE_SENSE0x6000.YTemp = 25.0f+g_SensBurst[8];
    LAE_SENSE0x6000.ZTemp = 25.0f+g_SensBurst[9];

    LAE_ESTIMATE0x6002.XAngle = g_Attitude[0];
    LAE_ESTIMATE0x6002.YAngle = g_Attitude[1];
    LAE_ESTIMATE0x6002.ZAngle = g_Attitude[2];
} // End InputPDO_ForwardPass()

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
    //Gyroscopes Sense
    memcpy(pTmpData, &LAE_SENSE0x6000.XGyro, SIZEOF(LAE_SENSE0x6000.XGyro));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_SENSE0x6000.YGyro, SIZEOF(LAE_SENSE0x6000.YGyro));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_SENSE0x6000.ZGyro, SIZEOF(LAE_SENSE0x6000.ZGyro));
    pTmpData += 2U;

    //Accelerometers Sense
    memcpy(pTmpData, &LAE_SENSE0x6000.XAcc, SIZEOF(LAE_SENSE0x6000.XAcc));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_SENSE0x6000.YAcc, SIZEOF(LAE_SENSE0x6000.YAcc));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_SENSE0x6000.ZAcc, SIZEOF(LAE_SENSE0x6000.ZAcc));
    pTmpData += 2U;

    //Temperatures Sense
    memcpy(pTmpData, &LAE_SENSE0x6000.XTemp, SIZEOF(LAE_SENSE0x6000.XTemp));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_SENSE0x6000.YTemp, SIZEOF(LAE_SENSE0x6000.YTemp));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_SENSE0x6000.ZTemp, SIZEOF(LAE_SENSE0x6000.ZTemp));
    pTmpData += 2U;


    //Angles Estimate
    memcpy(pTmpData, &LAE_ESTIMATE0x6002.XAngle, SIZEOF(LAE_ESTIMATE0x6002.XAngle));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_ESTIMATE0x6002.YAngle, SIZEOF(LAE_ESTIMATE0x6002.YAngle));
    pTmpData += 2U;
    memcpy(pTmpData, &LAE_ESTIMATE0x6002.ZAngle, SIZEOF(LAE_ESTIMATE0x6002.ZAngle));
    pTmpData += 2U;
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
    memcpy(&LAE_CONTROL0x7000.IMU_flags, pTmpData, SIZEOF(LAE_CONTROL0x7000.IMU_flags));
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
    // Calculating current EtherCAT cycle time and frequency
    CycleTime = sSyncManOutPar.u32Sync0CycleTime;
    CycleFreq = 1000000000.0f / CycleTime;

    // Only working synchronously.
    if (bDcSyncActive)
    {
        //
        // Case switch statement base on the user command
        //
        switch (LAE_CONTROL0x7000.IMU_flags)
        {
            //
            // For the first 30 seconds (counter<=75000) ADIS 16364 performs
            // the internal null bias calibration of the gyroscopes.
            //
            case IMU_BIAS_CALIBRATION_MODE:
                //
                // Checking to perform SPI transaction only once.
                // 0xBE10 is the null bias calibration SPI code for the IMU.
                //
                if (g_biascounter[0]<ADIS16364_BIAS_RESET_DELAY*CycleFreq)
                {
                    if (!g_biascounter[0])
                    {
                        SPI_writeDataBlockingNonFIFO(SPI_config.spi_base, ADIS16364_NULL_BIAS_COMMAND);
                    }
                    // Send zero for all registers.
                    InputPDO_Reset();

                    // Increment bias calibration state counter.
                    g_biascounter[0]++;
                }
                else
                {
                    //
                    // After the first 30 seconds have passed CLA Task 1 carries the MCU-IMU SPI communication
                    // and attitude estimation internally.
                    //
                    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);

                    // Send all read registers via EtherCAT
                    InputPDO_ForwardPass();
                }

                break;

            case IMU_ONLINE_MODE:
                //
                // ADIS 16364 Supports full burst mode. CLA Task 1 carries the MCU-IMU SPI communication
                // and attitude estimation internally.
                //
                CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);

                // Send all read registers via EtherCAT
                InputPDO_ForwardPass();
                break;

            case IMU_OFFLINE_MODE:
                //
                // When offline do not perform any SPI transactions just send zeros.
                //
                InputPDO_Reset();
                break;
        }
    }
    else
    {
        GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
        GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);
    }
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
    uint16_t HW_Check = HW_Init();
    //
    // If Hardware Initialization was successful, reset LED1/LED2 to use them later.
    //
    if (!HW_Check)
    {
        GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
        GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);
    }

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
