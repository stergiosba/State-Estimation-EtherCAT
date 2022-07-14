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

//#pragma DATA_SECTION(g_SensBurst, "Cla1ToCpuMsgRAM")
float g_SensBurst[11] = { 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f };

//#pragma DATA_SECTION(g_Attitude, "Cla1ToCpuMsgRAM")
float g_Attitude[3] = { 0.0f, 0.0f, 0.0f };
float QGL[4] = { 1.0f, 0.0f, 0.0f, 0.0f };

//#pragma DATA_SECTION(g_ActiveMode, "CpuToCla1MsgRAM")
ADIS16364_IMU_OperationModes g_ActiveMode;

//#pragma DATA_SECTION(g_ActiveTaps, "CpuToCla1MsgRAM")
volatile uint16_t g_ActiveTaps = 0;

uint16_t g_ActiveDRng = 4;
uint32_t g_ActiveModeTimeCounter[1] = {0};

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

//
// Perform an Internal Reset
//
void Internal_Reset()
{
    memset(g_SensBurst, 0, 11 * sizeof(float));
    memset(g_Attitude, 0, 3 * sizeof(float));
    memset(QGL, 0, 4 * sizeof(float));
    QGL[0] = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function sends zeros for all values in the EtherCAT Input PDOs.

*////////////////////////////////////////////////////////////////////////////////////////
void InputPDO_Zeros()
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
} // End InputPDO_Zeros()

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function performs a forward pass of EtherCAT Input PDOs.

*////////////////////////////////////////////////////////////////////////////////////////
void InputPDO_ForwardPass()
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
 \brief    This function controls the response of the system, when calibration mode is selected the timer runs until 30 seconds have elapsed
           In data acquisition mode the system responds to a change of the Dynamic range of the FIR filter taps within one EtherCAT cycle.

*////////////////////////////////////////////////////////////////////////////////////////
//TODO fast find
void Application_Delay_Control(float delay, uint32_t CycleFreq)
{
    //
    // Checking to perform SPI transaction only once.
    //
    if (g_ActiveModeTimeCounter[0]<delay*CycleFreq)
    {
        //
        // Performing the new setup command only once.
        //
        if (!g_ActiveModeTimeCounter[0])
        {
            Internal_Reset();
            //
            // CLA Task 2 performs the FIR Taps change and if the mode is set
            // as IMU_BIAS_CALIBRATION_MODE then CLA Task 2 will also perform the
            // null bias calibration SPI process for the IMU.
            //
            CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_2);
        }

        // Send zero for all registers.
        InputPDO_Zeros();

        // Increment bias calibration state counter.
        g_ActiveModeTimeCounter[0]++;
    }
    else
    {
        //
        // After 30 seconds have passed CLA Task 1 carries the MCU-IMU SPI communication
        // and attitude estimation internally.
        //
        CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);

        // Send all read registers via EtherCAT
        InputPDO_ForwardPass();
    }
} // End Application_Delay_Control()

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
//TODO fast find
void APPL_Application(void)
{
    // Calculating current EtherCAT cycle time and frequency
    uint32_t CycleTime = sSyncManOutPar.u32Sync0CycleTime;
    uint32_t CycleFreq = 1000000000.0f / CycleTime;
    volatile uint16_t Taps;

    // Only working synchronously.
    if (bDcSyncActive)
    {
        //
        // Extracting bits [2:0] from user command. These bits represent the FIR filter taps.
        //
        Taps = (LAE_CONTROL0x7000.IMU_flags & 0x7);

        //
        // Extracting bits [6:4] from user command. These bits represent the dynamic range.
        //
        g_ActiveDRng = (LAE_CONTROL0x7000.IMU_flags & 0x70)>>4;

        //
        // Extracting high byte from user command and casting it to ADIS16364_IMU_OperationModes type.
        //
        uint16_t Mode = (LAE_CONTROL0x7000.IMU_flags & 0xFF00)>>8;


        if ((Taps!=g_ActiveTaps) || (Mode!= g_ActiveMode))
        {
            //
            // If taps have changed zero out counter.
            //
            g_ActiveModeTimeCounter[0]=0;
            g_ActiveTaps = Taps;
            g_ActiveMode = (ADIS16364_IMU_OperationModes) Mode;
        }


        //
        // Case switch statement base on the user command
        //
        switch (g_ActiveMode)
        {
            //
            // For the first 30 seconds (counter<=75000) ADIS 16364 performs
            // the internal null bias calibration of the gyroscopes.
            //
            case IMU_BIAS_CALIBRATION_MODE:
                Application_Delay_Control(ADIS16364_BIAS_RESET_DELAY, CycleFreq);
                break;

            case IMU_ONLINE_MODE:
                Application_Delay_Control(0.005, CycleFreq);
                break;

            default:
                //
                // When offline do not perform any SPI transactions just send zeros and perform internal reset.
                //
                Internal_Reset();
                InputPDO_Zeros();
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
