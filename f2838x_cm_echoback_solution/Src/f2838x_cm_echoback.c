//
// Included Files
//
#include <stdint.h>
#include "ecat_def.h"
#include "applInterface.h"
#include "cm.h"
#include "ipc.h"


#define _F2838X_ECHOBACK_ 1
#include "f2838x_cm_echoback.h"
#undef _F2838X_ECHOBACK_

//
// PDO_ResetOutputs - Resets the Output data to zero
//
void PDO_ResetOutputs(void)
{
    LEDS0x7000.LED1 = 0x0U;
    LEDS0x7000.LED2 = 0x0U;
    LEDS0x7000.LED3 = 0x0U;
    LEDS0x7000.LED4 = 0x0U;
    LEDS0x7000.LED5 = 0x0U;
    LEDS0x7000.LED6 = 0x0U;
    LEDS0x7000.LED7 = 0x0U;
    LEDS0x7000.LED8 = 0x0U;

    DatafromMaster0x7010.DatafromMaster = 0x0UL;
    TargetMode0x7012.Mode = 0x0U;
    TargetSpeedPosReq0x7014.SpeedPosReq = 0x0UL;
}

//
// APPL_AckErrorInd - Called when error state was acknowledged by the master
//
void APPL_AckErrorInd(UINT16 stateTrans)
{
    //
    // No implementation for this application
    //
}

//
// APPL_StartMailboxHandler - Informs application of state transition from INIT
//                            to PREOP
//
UINT16 APPL_StartMailboxHandler(void)
{
    return(ALSTATUSCODE_NOERROR);
}

//
// APPL_StopMailboxHandler - Informs application of state transition from PREOP
//                           to INIT
//
UINT16 APPL_StopMailboxHandler(void)
{
    return(ALSTATUSCODE_NOERROR);
}

//
// APPL_StartInputHandler - Informs application of state transition from PREOP
//                          to SAFEOP
//
UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return(ALSTATUSCODE_NOERROR);
}

//
// APPL_StopInputHandler - Informs application of state transition from SAFEOP
//                         PREOP
//
UINT16 APPL_StopInputHandler(void)
{
    return(ALSTATUSCODE_NOERROR);
}

//
// APPL_StartOutputHandler - Informs application of state transition from SAFEOP
//                           to OP
//
UINT16 APPL_StartOutputHandler(void)
{
    return(ALSTATUSCODE_NOERROR);
}

//
// APPL_StopOutputHandler - Informs application of state transition from OP to
//                          SAFEOP
//
UINT16 APPL_StopOutputHandler(void)
{
    //
    // Reset output data to zero
    //
    PDO_ResetOutputs();

    return(ALSTATUSCODE_NOERROR);
}

//
// APPL_GenerateMapping - Calculates the input and output process data sizes
//
UINT16 APPL_GenerateMapping(UINT16 *pInputSize, UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 inputSize = 0U;
    UINT16 outputSize = 0U;
    UINT16 PDOAssignEntryCnt = 0U;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT8 PDOSubindex0 = 0U;
    UINT8 *pPDOEntry = NULL;
    UINT8 PDOEntryCnt = 0U;

    //
    // Scan Object 0x1C12 (SyncManager 2)
    // (Sums up sizes of all SyncManager assigned RxPDOs subindexes)
    //
    for(PDOAssignEntryCnt = 0U; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0;
        PDOAssignEntryCnt++)
    {
        //
        // Get object handle for specified RxPDO assigned to SyncManager
        //
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);

        //
        // Confirm that Object isn't NULL before continuing
        //
        if(pPDO != NULL)
        {
            //
            // Get number of Object Entry subindexes
            //
            PDOSubindex0 = *((UINT8 *)pPDO->pVarPtr);

            //
            // Add up sizes of all the Object Entry subindexes
            //
            for(PDOEntryCnt = 0U; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = ((UINT8 *)pPDO->pVarPtr +
                             (OBJ_GetEntryOffset((PDOEntryCnt + 1U),
                                                 pPDO) >> 3U));
                //
                // Increment the expected output size
                // depending on the mapped entry
                //
                outputSize += (UINT16)(*pPDOEntry);
            }
        }
        else
        {
            //
            // Assigned PDO was not found in object dictionary.
            // Return invalid mapping status.
            //
            outputSize = 0U;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    outputSize = (outputSize + 7U) >> 3U;

    //
    // Continue scanning of TXPDO if no error during RXPDO scanning
    //
    if(result == ALSTATUSCODE_NOERROR)
    {
        //
        // Scan Object 0x1C13 (SyncManager 3)
        // (Sums up sizes of all SyncManager assigned TXPDO subindexes)
        //
        for(PDOAssignEntryCnt = 0U;
            PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0;
            PDOAssignEntryCnt++)
        {
            //
            // Get object handle for specified TxPDO assigned to SyncManager
            //
            pPDO =
             OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);

            //
            // Confirm that Object isn't NULL before continuing
            //
            if(pPDO != NULL)
            {
                //
                // Get number of Object Entry subindexes
                //
                PDOSubindex0 = *((UINT8 *)pPDO->pVarPtr);

                //
                // Add up sizes of all the Object Entry subindexes
                //
                for(PDOEntryCnt = 0U; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = ((UINT8 *)pPDO->pVarPtr +
                                 (OBJ_GetEntryOffset((PDOEntryCnt + 1U),
                                                     pPDO) >> 3U));
                    //
                    // Increment the expected output size
                    // depending on the mapped entry
                    //
                    inputSize += (UINT16)(*pPDOEntry);
                }
            }
            else
            {
                //
                // Assigned PDO was not found in object dictionary.
                // Return invalid mapping status.
                //
                inputSize = 0U;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }

    inputSize = (inputSize + 7U) >> 3U;

    //
    // Assign calculated sizes
    //
    *pInputSize = inputSize;
    *pOutputSize = outputSize;

    return(result);
}

//
// APPL_InputMapping - Copies the input data from local device memory to ESC
//                     memory
//
void APPL_InputMapping(UINT16 *pData)
{
    UINT16 j = 0U;
    UINT8 *pTmpData = (UINT8 *)pData;
    UINT8 data;

    //
    // Loop through all TxPDO entries and write out data
    //
    for(j = 0U; j < sTxPDOassign.u16SubIndex0; j++)
    {
        switch(sTxPDOassign.aEntries[j])
        {
            //
            // TxPDO 0 (Data from ESC to master)
            //
            case 0x1A00U:
                //
                // Switches (8-bit (Byte) Data)
                //
                data = ((Switches0x6000.Switch8 << 7U) |
                        (Switches0x6000.Switch7 << 6U) |
                        (Switches0x6000.Switch6 << 5U) |
                        (Switches0x6000.Switch5 << 4U) |
                        (Switches0x6000.Switch4 << 3U) |
                        (Switches0x6000.Switch3 << 2U) |
                        (Switches0x6000.Switch2 << 1U) |
                        Switches0x6000.Switch1);

                *(volatile UINT8 *)pTmpData = data;
                pTmpData++;
                break;
            //
            // TxPDO 1 (Data from ESC to master)
            //
            case 0x1A01U:
                //
                // DataToMaster (32 bits Data)
                //
                *(volatile UINT32 *)pTmpData =
                 DataToMaster0x6010.DataToMaster;
                pTmpData += 4U;

                //
                // ModeResponse (16 bits Data)
                //
                *(volatile UINT16 *)pTmpData =
                 TargetModeResponse0x6012.ModeResponse;
                pTmpData += 2U;

                //
                // SpeedPosFbk (32 bits Data)
                //
                *(volatile UINT32 *)pTmpData =
                 TargetSpeedPosFeedback0x6014.SpeedPosFbk;
                break;
        }
    }
}

//
// APPL_OutputMapping - Copies the output data from ESC memory to local device
//                      memory
//
void APPL_OutputMapping(UINT16 *pData)
{
    UINT16 j = 0U;
    UINT8 *pTmpData = (UINT8 *)pData;
    UINT8 data = 0U;

    //
    // Loop through all RxPDO entries and read in data
    //
    for(j = 0U; j < sRxPDOassign.u16SubIndex0; j++)
    {
        switch(sRxPDOassign.aEntries[j])
        {
            //
            // RxPDO 0 (Data from Master to ESC)
            //
            case 0x1600U:
                //
                // LEDS (8-bit (Byte) Data)
                //
                data = (*(volatile UINT8 *)pTmpData);

                (LEDS0x7000.LED1) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED2) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED3) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED4) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED5) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED6) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED7) = data & BIT_MASK;
                data = data >> 1U;
                (LEDS0x7000.LED8) = data & BIT_MASK;

                pTmpData++;
                break;
            //
            // RxPDO 1 (Data from Master to ESC)
            //
            case 0x1601U:
                //
                // DatafromMaster (32 bits Data)
                //
                DatafromMaster0x7010.DatafromMaster =
                 *(volatile UINT32 *)pTmpData;
                pTmpData += 4U;

                //
                // Mode (16 bits Data)
                //
                TargetMode0x7012.Mode = *(volatile UINT16 *)pTmpData;
                pTmpData += 2U;

                //
                // SpeedPosReq (32 bits Data)
                //
                TargetSpeedPosReq0x7014.SpeedPosReq =
                 *(volatile UINT32 *)pTmpData;
                break;
        }
    }
}

//
// APPL_Application - Called as part of main stack loop. Assigns the output
//                    values to the input values for EtherCAT master
//
void APPL_Application(void)
{

    Switches0x6000.Switch1 = LEDS0x7000.LED1;
    Switches0x6000.Switch2 = LEDS0x7000.LED2;
    Switches0x6000.Switch3 = LEDS0x7000.LED3;
    Switches0x6000.Switch4 = LEDS0x7000.LED4;

    Switches0x6000.Switch5 = LEDS0x7000.LED5;
    Switches0x6000.Switch6 = LEDS0x7000.LED6;
    Switches0x6000.Switch7 = LEDS0x7000.LED7;
    Switches0x6000.Switch8 = LEDS0x7000.LED8;

    DataToMaster0x6010.DataToMaster = DatafromMaster0x7010.DatafromMaster;

    TargetModeResponse0x6012.ModeResponse = TargetMode0x7012.Mode;

    TargetSpeedPosFeedback0x6014.SpeedPosFbk = TargetSpeedPosReq0x7014.SpeedPosReq;





}

#if EXPLICIT_DEVICE_ID
//
// APPL_GetDeviceID - Return explicit device ID for F2838x.CM
//
UINT16 APPL_GetDeviceID(void)
{
    return(0x5U);
}
#endif // EXPLICIT_DEVICE_ID

#if USE_DEFAULT_MAIN
//
// Main Echoback Function
//
int main(void)
{
    //
    // Initialize device hardware and EtherCAT slave controller
    //
    HW_Init();

    //
    // Initialize Slave Stack
    //
    MainInit();

    bRunApplication = TRUE;
    do
    {
        //
        // Run Slave Stack
        //
        MainLoop();
    } while(bRunApplication == TRUE);

    //
    // De-Initialize device and resources
    //
    HW_Release();

    return(0U);
}
#endif // USE_DEFAULT_MAIN

//
// End of File
//
