/** \addtogroup ADIS16364_Drivers ADIS16364 Drivers
* @{
*
* \file ADIS16364_utilities.c
*
* \brief This file contains the function definitions used in ADIS16364
* EtherCAT Slave Application.
*
* Specifically, it contains ADIS16364 IMU Drivers' routines.
*
* Author:      Aristotelis Papatheodorou\n
* Maintainer:  Konstantinos Machairas
*
* Revision History\n
* Version 00.01.00 | 2020 | Papatheodorou\n
* Version 00.02.00 | 2022 | Bachoumas
*
* (C) Copyright 2022, NTUA CSL-EP Legged Robots Team
*
*****************************************************************************/

//*****************************************************************************
//
// Include Files
//
//*****************************************************************************
#include <math.h>
#include <SPI_init.h>
#include "ADIS16364.h"

//*****************************************************************************
//
// Power Supply Voltage [mV per LSB]
//
//*****************************************************************************
const float g_SupplyOutScale = 2.418f;

//*****************************************************************************
//
// Gyroscope Registers' Scales [deg/s per LSB]
//
//*****************************************************************************
float g_GyroScale = 0.05f;

//*****************************************************************************
//
// Accelerometer Registers' Scales [deg/s per LSB]
//
//*****************************************************************************
const float g_AcclScale = 1.0f;

//*****************************************************************************
//
// Temperature Register Scale [C per LSB]  -- 0x0 -> 25 C
//
//*****************************************************************************
const float g_TempScale = 0.136f;

//*****************************************************************************
//
// Auxialiary ADC (Analog to Digital Converter) Data Bits Scale [mV per LSB]
//
//*****************************************************************************
const float g_AdcScale = 805.8f;

//*****************************************************************************
//
// Sensor Burst-Mode Read Vector
//
//*****************************************************************************
#pragma DATA_SECTION(g_SensBurst, "Cla1DataRam")
float g_SensBurst[11] = { 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f };

//*****************************************************************************
//
// Active Dynamic Range Option
//
//*****************************************************************************
uint16_t g_ActiveDRng = 4;

//*****************************************************************************
//
// Active Filtering Taps Option
//
//*****************************************************************************
uint16_t g_ActiveTaps = 0;

//*****************************************************************************
//
// Minimum Taps for each Dynamic Range Variable
//
//*****************************************************************************
uint16_t g_MinTaps = 0;

uint16_t g_VinDelay = 790U;
uint16_t g_Gyro1Delay = 790U;
uint16_t g_Gyro23Delay = 39U;
uint16_t g_AccDelay = 39U;
uint16_t g_TempDelay = 39U;
uint16_t g_AdcDelay = 39U;


//*****************************************************************************
//
//! \brief Saturates floating point Values in a Prescribed Range.
//!
//! \param[in] x floating point is the value to be saturated.
//! \param[in] xMax floating point is the Upper Limit of the saturated
//! value.
//! \param[in] xMin floating point is the Lower Limit of the saturated
//! value.
//!
//! \return x floating point Value after Saturation.
//
//*****************************************************************************
static inline float CpuSat(float x, float xMax, float xMin)
{
    return fminf(fmaxf(x, xMin), xMax);

}   // End Of CpuSat()

//*****************************************************************************
//
//! \brief Executes a Single Register Read.
//!
//! \param[in] Reg uint16_t Register's Address.
//! \param[in] NumBits uint16_t Register's Number of Significant
//! Bits.
//!
//! This function performs the required SPI transfers to read the register of
//! the specified address.
//!
//! \return Sensrd uint16_t contents of the specified register.
//
//*****************************************************************************
uint16_t SensorRead(uint16_t Reg, uint16_t NumBits)
{
    //
    // Initialize Results' Variable
    //
    uint16_t Sensrd = 0x0000;

    //
    // Left Shift Register's Value to comply with IMU's SPI Transfer Form
    //
    Reg <<= 8;

    //
    // Request the specified Register's Contents
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, Reg);

    //
    // Data Ready Delay
    //
    ADIS16364_DATA_READY_DELAY;

    //
    // Dummy Transfer to update SPI's incoming register
    //
    SPI_writeDataNonBlocking(SUS_SPI_BASE, ADIS16364_NULL_COMMAND);

    //
    // Data Ready Delay
    //
    ADIS16364_DATA_READY_DELAY;

    //
    // Acquire SPI incoming Register's Contents
    //
    Sensrd = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);

    //
    // Isolate the Register's Significant Bits
    //
    Sensrd &= (0xFFFF >> (SBITS16 - NumBits));

    //
    // Acquire SPI incoming Register's Contents
    //
    return Sensrd;

}   // End Of SensorRead()

//*****************************************************************************
//
//! \brief Executes Multiple Register Reads in Burst-Mode.
//!
//! This function performs the IMU Burst-Read Functionality. Consult the
//! ADIS16364 IMU's Datasheet for more information.
//!
//! \return None.
//
//*****************************************************************************
void BurstRead(void)
{
    //
    // Burst Registers' Significant Bits
    //
    uint16_t SBits[11] = { SBITS12, SBITS14, SBITS14, SBITS14,
                           SBITS14, SBITS14, SBITS14, SBITS12,
                           SBITS12, SBITS12, SBITS12 };

    //
    // Raw Burst Readings' Vector
    //
    uint16_t Burst[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    //
    // Custom Delays
    //
    //uint16_t DelayScalers[11] = { g_VinDelay, g_Gyro1Delay, g_Gyro23Delay, g_Gyro23Delay,
    //                       g_AccDelay, g_AccDelay, g_AccDelay, g_TempDelay,
    //                       g_TempDelay, g_TempDelay, g_AdcDelay };

    //
    // Loop Counter Initialization
    //
    uint16_t i;

    //
    // Burst Registers' Sign Types
    //
    uint16_t Sign[11] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };

    //
    // Burst Registers' Scales
    //
    float RegScale[11] = { g_SupplyOutScale, g_GyroScale, g_GyroScale,
                           g_GyroScale, g_AcclScale, g_AcclScale,
                           g_AcclScale, g_TempScale, g_TempScale,
                           g_TempScale, g_AdcScale };

    //
    // Burst Read Pointer Initialization
    //
    float *BurstPtr = NULL;

    //
    // Assign SensBurst Address to Burst Read Pointer
    //
    BurstPtr = g_SensBurst;

    //
    // Execute Burst Command SPI Tranfer
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, ADIS16364_BURST_COMMAND);

    //
    // Data Ready Delay
    //
    //ADIS16364_ACCE_DELAY;
    ADIS16364_DATA_READY_DELAY;

    //
    // Acquire Burst Mode Readings
    //
    for (i = 0; i <= 10; i++)
    {
        //
        // Dummy Transfer to update SPI's incoming register
        //
        SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, ADIS16364_NULL_COMMAND);

        //
        // Data Ready Delay
        //

        //SysCtl_delay(DelayScalers[i]);
        ADIS16364_DATA_READY_DELAY;

        //
        // Acquire SPI incoming Register's Contents
        //
        Burst[i] = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);

        //
        // Isolate the Register's Significant Bits
        //
        Burst[i] &= (0xFFFF >> (SBITS16 - SBits[i]));
    }

    //
    // Iterate the Acquired Raw Readings
    //
    for (i = 0; i <= 10; i++)
    {
        //
        // Translate Raw Readings to the Actual ones
        //
        *(BurstPtr + i) = RawToReal(Burst[i], RegScale[i], SBits[i], Sign[i]);
    }

    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);
}   // End Of BurstRead()

//*****************************************************************************
//
//! \brief Executes a Single Register Write.
//!
//! \param[in] Reg uint16_t Register's Address.
//! \param[in] Value uint16_t value to be written to the Register.
//!
//! This function performs the required SPI transfers to read the register of
//! the specified address.
//!
//! \return Status uint16_t Operation Status (0: Fail | 1: Success)
//
//*****************************************************************************
uint16_t RegisterWrite(uint16_t Reg, uint16_t Value)
{
    //
    // Initialize Register's Write Command Variable
    //
    uint16_t Cmd = ADIS16364_NULL_COMMAND;

    //
    // Combine value & Register's address to a single Write Command
    //
    Cmd |= Reg;

    //
    // Left Shift Register's Value to comply with IMU's SPI Transfer Form
    //
    Cmd <<= 8;

    //
    // Form the Register's Write Command
    //
    Cmd |= (0x8000 | Value);

    //
    // Execute SPI Transfer
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, Cmd);

    //
    // Data Ready Delay
    //
    ADIS16364_DATA_READY_DELAY;

    //
    // Write Operation Successful
    //
    return 1;

}   // End Of RegisterWrite()

//*****************************************************************************
//
//! \brief Translates Raw IMU Register's Data to the actual readings.
//!
//! \param[in] Raw uint16_t Raw Register's Data.
//! \param[in] RegScale float Register's Scale.
//! \param[in] NumBits uint16_t Register's Number of Significant
//! Bits.
//! \param[in] Sign unsigned char Data sign definition.
//!
//! \return Reading float Register's Actual Value.
//
//*****************************************************************************
float RawToReal(uint16_t Raw, float RegScale, uint16_t NumBits, uint16_t Sign)
{
    //
    // Mask for Significant Bits
    //
    uint16_t Mask = 0xFFFF << (NumBits - 1);

    //
    // Signed Floating Point Unscaled Reading Initialization
    //
    float Sens;

    //
    // Register's Value is Signed
    //
    if (Sign)
    {
        //
        // Make Sign Negative & Reading Floating Point
        //
        Sens = (Raw & Mask) ?
                        (-RegScale * (~(Raw | 0xFFFF << NumBits) + 1.0f)) :
                        (RegScale * Raw);
    }

    //
    // Register's Value is Unsigned
    //
    else
    {
        Sens = (float)Raw;
    }

    return Sens;

}   // End Of RawToReal()

//*****************************************************************************
//
//! \brief Translates Raw IMU Register's Data to the actual readings.
//!
//! \param[in] Raw uint16_t Raw Register's Data.
//! \param[in] RegScale float Register's Scale.
//! \param[in] NumBits uint16_t Register's Number of Significant
//! Bits.
//! \param[in] Sign unsigned char Data sign definition.
//!
//! \return Reading float Register's Actual Value.
//
//*****************************************************************************
float RawToRealSign(uint16_t Raw, float RegScale)
{
    //
    // Mask for significant bits
    //
    uint16_t Mask = 0xE000U;

    //
    // Signed Floating Point Unscaled Reading Initialization
    //
    float Sens;

    //
    // Register's Value is Signed
    //
    Sens = (Raw & Mask) ?
            (-RegScale * (~(Raw | 0xC000U) + 1.0f)) :
            (RegScale * Raw);

    return Sens;

}   // End Of RawToRealSign()

//*****************************************************************************
//
//! \brief Executes Software Reset of ADIS16364 IMU.
//!
//! \return Result uint16_t operation status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t ResetIMU()
{
    //
    // Operation Result Variable
    //
    uint16_t Result = 1;

    //
    // Execute the required SPI Write Transfer to Reset IMU
    //
    Result *= RegisterWrite(GLOB_CMD, 0x80);

    //
    // System Ready Delay
    //
    DEVICE_DELAY_US(ADIS16364_SYS_READY_DELAY);

    //
    // Return Reset Operation Status
    //
    return Result;

}   // End Of ResetIMU()

//*****************************************************************************
//
//! \brief Changes Number of Taps.
//!
//! param[in] Taps uint16_t Desired Number of Taps.
//!
//! Specifically it sets m to N = 2^(m) of Taps. Valid Range: 0 to 7
//!
//! \return Result uint16_t Operation Status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t TapFIRCtrl(uint16_t Taps)
{
    //
    // Operation Result Variable
    //
    uint16_t Result = 1;

    //
    // Invalid Number of Taps
    //
    if (Taps > 7)
    {
        //
        // Return Failed Status
        //
        Result = 0;
    }

    //
    // Valid Number of Taps
    //
    else
    {
        //
        // Acquire Current Register's Value
        //
        uint16_t RegValue = SensorRead(SENS_AVG, SBITS16);

        //
        // Create the Desired Taps' Set Command
        //
        uint16_t Cmd = ((RegValue & 0xFFF8) | (uint16_t)Taps);

        //
        // Execute the requires SPI Transfers to set the Taps
        //
        Result *= RegisterWrite(SENS_AVG, (0x00FF & Cmd));
        Result *= RegisterWrite(SENS_AVG + 0x0001, ((0xFF00 & Cmd) >> 8));

        //
        // Update Active Taps Number
        //
        g_ActiveTaps = Taps;
    }

    //
    // Return Taps' Change Status
    //
    return Result;

}   // End Of TapFIRCtrl()

//*****************************************************************************
//
//! \brief Changes the Gyroscopes' Active Dynamic Range.
//!
//! \param[in] Range uint16_t Desired Dynamic Range Option.
//!
//! Available Options:
//!     - Max Absolute angular Velocity 300 [deg/s]  (4)  -- Default Option
//!     - Max Absolute angular Velocity 150 [deg/s]  (2)
//!     - Max Absolute angular Velocity  75 [deg/s]  (1)
//!
//! \return Result uint16_t Operation Status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t DRngFIRCtrl(uint16_t Range)
{
    //
    // Operation Result Variable
    //
    uint16_t Result = 1;

    //
    // Invalid Range
    //
    if (Range == 0 || Range == 3 || Range > 4)
    {
        //
        // Return Failed Status
        //
        Result = 0;
    }

    //
    // Valid Range
    //
    else
    {
        //
        // Set Status to Success
        //
        Result = 1;

        //
        // Desired Range is (1)
        //
        if (Range == 1)
        {
            //
            // Minimum Taps Allowed
            //
            g_MinTaps = 4;

            //
            // Change Gyroscopes' Scaling
            //
            g_GyroScale = 0.0125;
        }

        //
        // Desired Range is (2)
        //
        else if (Range == 2)
        {
            //
            // Minimum Taps Allowed
            //
            g_MinTaps = 2;

            //
            // Change Gyroscopes' Scaling
            //
            g_GyroScale = 0.025;
        }
        else
        {
            //
            // Minimum Taps Allowed
            //
            g_MinTaps = 0;

            //
            // Change Gyroscopes' Scaling
            //
            g_GyroScale = 0.05;
        }

        //
        // Change Active Taps
        //
        Result *= TapFIRCtrl(
                        (uint16_t)CpuSat((float)g_ActiveTaps,
                                                   7.0f, (float)g_MinTaps));

        //
        // Read Current Register's Value
        //
        uint16_t RegValue = SensorRead(SENS_AVG, SBITS16);

        //
        // Create Desired Active Range's Command
        //
        uint16_t Cmd = ((RegValue & 0x0007) | ((uint16_t)Range << 8));

        //
        // Execute the requires SPI Transfers to set the Dynamic Range
        //
        Result *= RegisterWrite(SENS_AVG, (0x00FF & Cmd));
        Result *= RegisterWrite(SENS_AVG + 0x0001, ((0xFF00 & Cmd) >> 8));

        //
        // Update Active Taps Number
        //
        g_ActiveDRng = Range;
    }

    //
    // Return Active Range's Change Status
    //
    return Result;

}   // End Of DRngFIRCtrl()

//*****************************************************************************
//
//! \brief Checks IMU's Product ID and works as a communication test.
//!
//! \return Status uint16_t ID Match
//! (0: Mismatching IDs | 1: Matching IDs).
//
//*****************************************************************************
uint16_t IMUCommsCheck(void)
{
    //
    // IMU Startup Reset
    //
    //ResetIMU();

    //
    // Check if the Prescribed Product ID matches with the Acquired one.
    //
    volatile uint16_t ProdID = SensorRead(PROD_ID, SBITS16);

    return (uint16_t)(ProdID == (uint16_t)ADIS16364_ID);

}   // End Of IMUCommsCheck()

//*****************************************************************************
//
//! \brief Configures the IMU to the Default Setup.
//!
//! \return Result uint16_t Operation Status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t ADISConfig(void)
{
    //
    // Default Command for Setup
    //
    uint16_t Cmd = 0x00C2;

    //
    // Current Register's Value Variable Initialization
    //
    uint16_t RegValue = 0x000;

    //
    // Operation Status Variable Initialization
    //
    uint16_t Result = 1;

    //
    // Acquire Current Register's Value
    //
    RegValue = SensorRead(MSC_CTRL, SBITS16);

    //
    // Change the Command to leave other Options Unchanged
    //
    Cmd |= (0xFF00 & RegValue);

    //
    // Execute the SPI Transfers to Set the Default IMU Setup
    //
    Result *= RegisterWrite(MSC_CTRL, (0x00FF & Cmd));
    Result *= RegisterWrite(MSC_CTRL + 0x0001, ((0xFF00 & Cmd) >> 8));

    //
    // Reset Filtering Options
    //
    Result *= DRngFIRCtrl(g_ActiveDRng);

    //
    // Return Operation Status
    //
    return Result;

}   // End Of ADISConfig()



void IMUGyroBiasNullCalibration(void)
{
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, 0xBE01);

    //
    // IMU Bias Reset Delay
    //
    DEVICE_DELAY_US(ADIS16364_BIAS_RESET_DELAY);
}

/** @}*/

//
// End Of File
//
