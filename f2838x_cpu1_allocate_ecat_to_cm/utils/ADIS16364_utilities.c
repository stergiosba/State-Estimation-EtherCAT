//
//! \addtogroup ADIS16364_Drivers ADIS16364 Drivers
//! @{
//
//*****************************************************************************
//
//! \file ADIS16364_utilities.c
//!
//! \brief This file contains the function definitions used in ADIS16364
//! EtherCAT Slave Application.
//!
//! Specifically, it is contains ADIS16364 IMU Drivers' routines.
//!
// Author:      Aristotelis Papatheodorou
// Maintainer:  Konstantinos Machairas
//
// Revision History
// Version 00.01.00 | 2020 | Papatheodorou
//
// (C) Copyright 2020, NTUA CSL-EP Legged Robots Team
//
//*****************************************************************************

//*****************************************************************************
//
// Include Files
//
//*****************************************************************************
#include <math.h>
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
// Accelerometer Registers' Scales [mg per LSB]
//
//*****************************************************************************
const float g_AcclScale = 1.0f;

const float g_a = 0.001f;
//*****************************************************************************
//
// Temperature Register Scale [C per LSB]  -- 0x0 -> 25 C
//
//*****************************************************************************
const float g_TempScale = 0.136f;

//*****************************************************************************
//
// Power Supply Voltage [uV per LSB]
//
//*****************************************************************************
const float g_AdcScale = 805.8f;

//*****************************************************************************
//
// Sensor Burst-Mode Read Vector
//
//*****************************************************************************
float g_SensBurst[11] = { 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f };

float g_SensBurst2[7] = { 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f};

//*****************************************************************************
//
// Active Dynamic Range Option
//
//*****************************************************************************
uint16_t g_ActiveDRng = 4U;

//*****************************************************************************
//
// Active Filtering Taps Option
//
//*****************************************************************************
uint16_t g_ActiveTaps = 0U;

//*****************************************************************************
//
// Minimum Taps for each Dynamic Range Variable
//
//*****************************************************************************
uint16_t g_MinTaps = 0U;

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
//! \param[in] NumBits unsigned short int Register's Number of Significant
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
    uint16_t Sensrd = 0x0000U;

    //
    // Left Shift Register's Value to comply with IMU's SPI Transfer Form
    //
    Reg <<= 8U;

    //
    // Request the specified Register's Contents
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, Reg);

    //
    // Data Ready Delay
    //
    ACTION_DELAY;

    //
    // Dummy Transfer to update SPI's incoming register
    //
    SPI_writeDataNonBlocking(SUS_SPI_BASE, 0x0000U);

    //
    // Data Ready Delay
    //
    ACTION_DELAY;

    //
    // Acquire SPI incoming Register's Contents
    //
    Sensrd = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);

    //
    // Isolate the Register's Significant Bits
    //
    Sensrd &= (0xFFFFU >> (16U - NumBits));

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
    uint16_t Burst[11] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

    //
    // Loop Counter Initialization
    //
    uint16_t i = 0x0U;

    //
    // Burst Registers' Sign Types
    //
    const uint16_t Sign[11] = { 0U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 0U };

    //
    // Burst Registers' Scales
    //
    const float RegScale[11] = { g_SupplyOutScale, g_GyroScale, g_GyroScale,
                                 g_GyroScale, g_AcclScale, g_AcclScale,
                                 g_AcclScale, g_TempScale, g_TempScale,
                                 g_TempScale, g_AdcScale };

    //
    // Burst Read Pointer Initialization
    //
    volatile float *BurstPtr = NULL;

    //
    // Assign SensBurst Address to Burst Read Pointer
    //
    BurstPtr = g_SensBurst;

    //
    // Execute Burst Command SPI Tranfer
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, 0x3E00);

    //
    // Data Ready Delay
    //
    ACTION_DELAY;

    //
    // Acquire Burst Mode Readings
    //
    for (i = 0U; i <= 10U; i++)
    {
        //
        // Dummy Transfer to update SPI's incoming register
        //
        SPI_writeDataNonBlocking(SUS_SPI_BASE, 0x0000U);

        //
        // Data Ready Delay
        //
        ACTION_DELAY;

        //
        // Acquire SPI incoming Register's Contents
        //
        Burst[i] = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);

        //
        // Isolate the Register's Significant Bits
        //
        Burst[i] &= (0xFFFFU >> (16U - SBits[i]));
    }

    //
    // Iterate the Acquired Raw Readings
    //
    for (i = 0U; i <= 10U; i++)
    {
        //
        // Translate Raw Readings to the Actual ones
        //
        *(BurstPtr + i) = RawToReal(Burst[i], RegScale[i], SBits[i], Sign[i]);
    }
}   // End Of BurstRead()


void BurstRead2(void)
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
    uint16_t Burst[11] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

    //
    // Loop Counter Initialization
    //
    uint8_t i = 0x0U;

    //
    // Execute Burst Command SPI Tranfer
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, 0x3E00);

    //
    // Data Ready Delay
    //
    ACTION_DELAY;

    //
    // Acquire Burst Mode Readings
    //
    for (i = 0U; i <= 10U; i++)
    {
        //
        // Dummy Transfer to update SPI's incoming register
        //
        SPI_writeDataNonBlocking(SUS_SPI_BASE, 0x0000U);

        //
        // Data Ready Delay
        //
        ACTION_DELAY;

        //
        // Acquire SPI incoming Register's Contents
        //
        Burst[i] = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);

        //
        // Isolate the Register's Significant Bits
        //
        Burst[i] &= (0xFFFFU >> (16U - SBits[i]));
    }

    ipcCPUToCMDataBuffer.statusNode.XGyro_sense = RawToRealSign(Burst[1], g_GyroScale);
    ipcCPUToCMDataBuffer.statusNode.YGyro_sense = RawToRealSign(Burst[2], g_GyroScale);
    ipcCPUToCMDataBuffer.statusNode.ZGyro_sense = RawToRealSign(Burst[3], g_GyroScale);
    ipcCPUToCMDataBuffer.statusNode.XAcc_sense = RawToRealSign(Burst[4], g_AcclScale);
    ipcCPUToCMDataBuffer.statusNode.YAcc_sense = RawToRealSign(Burst[5], g_AcclScale);
    ipcCPUToCMDataBuffer.statusNode.ZAcc_sense = RawToRealSign(Burst[6], g_AcclScale);

}   // End Of BurstRead()

//*****************************************************************************
//
//! \brief Executes a Single Register Write.
//!
//! \param[in] Reg uint16_t Register's Address.
//! \param[in] Value unsigned short int value to be written to the Register.
//!
//! This function performs the required SPI transfers to read the register of
//! the specified address.
//!
//! \return Status unsigned short int Operation Status (0: Fail | 1: Success)
//
//*****************************************************************************
uint16_t SensorWrite(uint16_t Reg, uint16_t Value)
{
    //
    // Initialize Register's Write Command Variable
    //
    uint16_t Cmd = 0x0000U;

    //
    // Combine value & Register's address to a single Write Command
    //
    Cmd |= Reg;

    //
    // Left Shift Register's Value to comply with IMU's SPI Transfer Form
    //
    Cmd <<= 8U;

    //
    // Form the Register's Write Command
    //
    Cmd |= (0x8000U | (0x00FFU & Value));

    //
    // Execute SPI Transfer
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, Cmd);

    //
    // Data Ready Delay
    //
    ACTION_DELAY;

    //
    // Write Operation Successful
    //
    return 1U;

}   // End Of SensorWrite()

//*****************************************************************************
//
//! \brief Translates Raw IMU Register's Data to the actual readings.
//!
//! \param[in] Raw uint16_t Raw Register's Data.
//! \param[in] RegScale float Register's Scale.
//! \param[in] NumBits unsigned short int Register's Number of Significant
//! Bits.
//! \param[in] Sign unsigned char Data sign definition.
//!
//! \return Reading float Register's Actual Value.
//
//*****************************************************************************
float RawToReal(uint16_t Raw, float RegScale, uint16_t NumBits,
                uint16_t Sign)
{
    //
    // Initialize Mask
    //
    uint16_t Mask = 0x0000U;

    //
    // Signed Floating Point Unscaled Reading Initialization
    //
    float Sens;

    //
    // Mask for Significant Bits
    //
    Mask = 0xFFFFU << (NumBits - 1U);

    //
    // Register's Value is Signed
    //
    if (Sign == 1U)
    {
        //
        // Make Sign Negatvie & Reading Floating Point
        //
        Sens = (Raw & Mask) ?
                        (-1.0f * (~(Raw | 0xFFFFU << NumBits) + 1.0f)) :
                        (1.0f * Raw);
    }

    //
    // Register's Value is Unsigned
    //
    else
    {
        Sens = (float)Raw;
    }

    return Sens * RegScale;

}   // End Of RawToReal()

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

}   // End Of RawToReal()

//*****************************************************************************
//
//! \brief Translates a floating point value to two-complements usigned
//! integer.
//!
//! \param[in] Num float Number to be translated
//!
//! \return Raw uint16_t Two Complements integer Value.
//
//*****************************************************************************
uint16_t TwosComp(float Num)
{
    uint16_t Raw = 0x0000U;

    //
    // Value is Negative
    //
    if (Num < 0U)
    {
        Raw = ~((uint16_t)(-Num) - 1U);
    }

    //
    // Value is Positive
    //
    else
    {
        Raw = (uint16_t)Num;
    }

    //
    // Return Two Complements Integer Value
    //
    return Raw;

}   // End Of TwosComp

//*****************************************************************************
//
//! \brief Executes Software Reset of ADIS16364 IMU.
//!
//! \return Result unsigned short int operation status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t ResetIMU(void)
{
    //
    // Operation Result Variable
    //
    uint16_t Result = 1U;

    //
    // Execute the required SPI Write Transfer to Reset IMU
    //
    Result *= SensorWrite(GLOB_CMD, 0x80U);

    //
    // System Ready Delay
    //
    DEVICE_DELAY_US((200 * 1000UL));

    //
    // Return Reset Operation Status
    //
    return Result;

}   // End Of ResetIMU()

//*****************************************************************************
//
//! \brief Changes Number of Taps.
//!
//! param[in] Taps unsigned short int Desired Number of Taps.
//!
//! Specifically it sets m to N = 2^(m) of Taps. Valid Range: 0 to 7
//!
//! \return Result unsigned short int Operation Status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t TapFIRCtrl(uint16_t Taps)
{
    //
    // Operation Result Variable
    //
    uint16_t Result = 1U;

    //
    // Invalid Number of Taps
    //
    if (Taps > 7U)
    {
        //
        // Return Failed Status
        //
        Result = 0U;
    }

    //
    // Valid Number of Taps
    //
    else
    {
        //
        // Acquire Current Register's Value
        //
        uint16_t RegValue = SensorRead(SENS_AVG, 16U);

        //
        // Create the Desired Taps' Set Command
        //
        uint16_t Cmd = ((RegValue & 0xFFF8U) | (uint16_t)Taps);


        //
        // Execute the requires SPI Transfers to set the Taps
        //
        Result *= SensorWrite(SENS_AVG, (0x00FFU & Cmd));
        Result *= SensorWrite(SENS_AVG + 0x0001U, ((0xFF00U & Cmd) >> 8U));

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
//! \param[in] Range unsigned short int Desired Dynamic Range Option.
//!
//! Available Options:
//!     - Max Absolute angular Velocity 300 [deg/s]  (4)  -- Default Option
//!     - Max Absolute angular Velocity 150 [deg/s]  (2)
//!     - Max Absolute angular Velocity  75 [deg/s]  (1)
//!
//! \return Result unsigned short int Operation Status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t DRngFIRCtrl(uint16_t Range)
{
    //
    // Operation Result Variable
    //
    uint16_t Result = 1U;

    //
    // Invalid Range
    //
    if (Range == 0U || Range == 3U || Range > 4U)
    {
        //
        // Return Failed Status
        //
        Result = 0U;
    }

    //
    // Valid Range
    //
    else
    {
        //
        // Set Status to Success
        //
        Result = 1U;

        //
        // Desired Range is (1)
        //
        if (Range == 1U)
        {
            //
            // Minimum Taps Allowed
            //
            g_MinTaps = 4U;

            //
            // Change Gyroscopes' Scaling
            //
            g_GyroScale = 0.0125f;
        }

        //
        // Desired Range is (2)
        //
        else if (Range == 2U)
        {
            //
            // Minimum Taps Allowed
            //
            g_MinTaps = 2U;

            //
            // Change Gyroscopes' Scaling
            //
            g_GyroScale = 0.025f;
        }
        else
        {
            //
            // Minimum Taps Allowed
            //
            g_MinTaps = 0U;

            //
            // Change Gyroscopes' Scaling
            //
            g_GyroScale = 0.05f;
        }

        //
        // Change Active Taps
        //
        Result *= TapFIRCtrl((uint16_t)CpuSat((float)g_ActiveTaps,
                                                   7.0f, (float)g_MinTaps));

        //
        // Read Current Register's Value
        //
        uint16_t RegValue = SensorRead(SENS_AVG, 16U);

        //
        // Create Desired Active Range's Command
        //
        uint16_t Cmd = ((RegValue & 0x0007) | ((uint16_t)Range << 8));

        //
        // Execute the requires SPI Transfers to set the Dynamic Range
        //
        Result *= SensorWrite(SENS_AVG, (0x00FFU & Cmd));
        Result *= SensorWrite(SENS_AVG + 0x0001U, ((0xFF00U & Cmd) >> 8U));

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
//! \return Status unsigned short int ID Match
//! (0: Mismatching IDs | 1: Matching IDs).
//
//*****************************************************************************
uint16_t IMUCommsCheck(void)
{
    ResetIMU();
    //
    // Check if the Prescribed Product ID matches with the Acquired one.
    //
    volatile uint16_t ProdID = SensorRead(PROD_ID, 16U);
    return  (uint16_t)(ProdID == (uint16_t)ADIS16364_ID);

}   // End Of IMUCommsCheck()

//*****************************************************************************
//
//! \brief Configures the IMU to the Default Setup.
//!
//! \return Result unsigned short int Operation Status (0: Fail | 1: Success).
//
//*****************************************************************************
uint16_t ADISConfig(void)
{
    //
    // Default Command for Setup
    //
    uint16_t Cmd = 0x00C2U;

    //
    // Current Register's Value Variable Initialization
    //
    uint16_t RegValue = 0x000U;

    //
    // Operation Status Variable Initialization
    //
    uint16_t Result = 1U;

    //
    // Acquire Current Register's Value
    //
    RegValue = SensorRead(MSC_CTRL, 16U);

    //
    // Change the Command to leave other Options Unchanged
    //
    Cmd |= (0xFF00U & RegValue);


    //
    // Execute the SPI Transfers to Set the Default IMU Setup
    //
    Result *= SensorWrite(MSC_CTRL, (0x00FFU & Cmd));
    Result *= SensorWrite(MSC_CTRL + 0x0001U, ((0xFF00U & Cmd) >> 8U));

    //
    // Reset Filtering Options
    //
    Result *= DRngFIRCtrl(g_ActiveDRng);

    //
    // Return Operation Status
    //
    return Result;

}   // End Of ADISConfig()

//
// End Of File
//
