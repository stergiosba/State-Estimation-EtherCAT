//
//! \addtogroup ADIS16364_Drivers ADIS16364 Drivers
//! @{
//
//*****************************************************************************
//
//! \file ADIS16364.h
//!
//! \brief This is the header file of ADIS16364 Firmware Drivers.
//!
//! Specifically, it contains all the necessary definitions of
//! ADIS16364_utilities.c & SpiConfig.c
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
#ifndef ADIS16364_H_
#define ADIS16364_H_

//*****************************************************************************
//
// Include Files
//
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "SPI_init.h"

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************
#define WRDLEN          16U      // SPI Transfer Word Size
#define SPIOPFRQ        600000UL // 600 kHz SPI Operational Frequency
#define SBITS14         14U      // 14 Significant Bits
#define SBITS12         12U      // 12 Significant Bits
#define ADIS16364_ID    0x3FEC  // ADIS16375 ID Number
#define ADIS_SMPL       819.0f   // ADIS16375 Sampling Frequency [Hz]
#define SUPPLY          0U       // Supply Voltage's Burst-Read Position
#define XGYRO           1U       // X-Gyroscope Reading's Burst-Read Pos.
#define YGYRO           2U       // Y-Gyroscope Reading's Burst-Read Pos.
#define ZGYRO           3U       // Z-Gyroscope Reading's Burst-Read Pos.
#define XACCEL          4U       // X-Accelerometer Reading's Burst-Read Pos.
#define YACCEL          5U       // Y-Accelerometer Reading's Burst-Read Pos.
#define ZACCEL          6U       // Z-Accelerometer Reading's Burst-Read Pos.
#define XTEMP           7U       // X-Temperature Reading's Burst-Read Pos.
#define YTEMP           8U       // Y-Temperature Reading's Burst-Read Pos.
#define ZTEMP           9U       // Z-Temperature Reading's Burst-Read Pos.
#define ANALOG          10U      // ADC Reading's Burst-Read Pos.3
#define ACTION_DELAY    DEVICE_DELAY_US(30U)
#define MIN_DELAY       DEVICE_DELAY_US(5U)


//*****************************************************************************
//
// ADIS16374 Register Addresses
//
//*****************************************************************************
#define FLASH_CNT   0x00U    // Flash memory write count
#define SUPPLY_OUT  0x02U    // Power supply measurement
#define XGYRO_OUT   0x04U    // X-axis gyroscope output
#define YGYRO_OUT   0x06U    // Y-axis gyroscope output
#define ZGYRO_OUT   0x08U    // Z-axis gyroscope output
#define XACCL_OUT   0x0A00U    // X-axis accelerometer output
#define YACCL_OUT   0x0C00U    // Y-axis accelerometer output
#define ZACCL_OUT   0x0E00U    // Z-axis accelerometer output
#define XTEMP_OUT   0x10U    // X-axis gyroscope temperature output
#define YTEMP_OUT   0x12U    // Y-axis gyroscope temperature output
#define ZTEMP_OUT   0x14U    // Z-axis gyroscope temperature output
#define AUX_ADC     0x16U    // Auxiliary ADC output
#define XGYRO_OFF   0x1AU    // X-axis gyroscope bias offset
#define YGYRO_OFF   0x1CU    // Y-axis gyroscope bias offset
#define ZGYRO_OFF   0x1EU    // Z-axis gyroscope bias offset
#define XACCL_OFF   0x20U    // X-axis acceleration bias offset
#define YACCL_OFF   0x22U    // Y-axis acceleration bias offset
#define ZACCL_OFF   0x24U    // Z-axis acceleration bias offset
#define ALM_MAG1    0x26U    // Alarm 1 amplitude threshold
#define ALM_MAG2    0x28U    // Alarm 2 amplitude threshold
#define ALM_SMPL1   0x2AU    // Alarm 1 sample size
#define ALM_SMPL2   0x2CU    // Alarm 2 sample size
#define ALM_CTRL    0x2EU    // Alarm control
#define AUX_DAC     0x30U    // Auxiliary DAC data
#define GPIO_CTRL   0x32U    // Auxiliary digital input/output control
#define MSC_CTRL    0x34U    // Data ready, self-test, miscellaneous
#define SMPL_PRD    0x36U    // Internal sample period (rate) control
#define SENS_AVG    0x38U    // Dynamic range and digital filter control
#define SLP_CNT     0x3AU    // Sleep mode control
#define DIAG_STAT   0x3CU    // System status
#define GLOB_CMD    0x3EU    // System commands
#define PROD_ID     0x56U    // Product Identification Address

//*****************************************************************************
//
// Global Variable Definitions
//
//*****************************************************************************
extern const float g_SupplyOutScale;
extern float g_GyroScale;
extern const float g_AcclScale;
extern const float g_a;
extern const float g_TempScale;
extern const float g_AdcScale;
extern float g_SensBurst[11];
extern uint16_t g_ActiveDRng;
extern uint16_t g_ActiveTaps;
extern uint16_t g_MinTaps;

//*****************************************************************************
//
// Global Function Prototypes
//
//*****************************************************************************
extern void BurstRead(void);
extern void BurstRead2(void);
extern uint16_t SensorRead(uint16_t Reg, uint16_t NumBits);
extern float RawToReal(uint16_t Raw, float RegScale, uint16_t NumBits, uint16_t Sign);
extern float RawToRealSign(uint16_t Raw, float RegScale);
extern uint16_t SensorWrite(uint16_t Reg, uint16_t Value);
extern uint16_t TwosComp(float Num);
extern uint16_t ResetIMU(void);
extern uint16_t DRngFIRCtrl(uint16_t Range);
extern uint16_t TapFIRCtrl(uint16_t Taps);
extern uint16_t IMUCommsCheck(void);
extern uint16_t ADISConfig(void);

#endif  // ADIS16364_H_

//! @}

//
//  End Of File
//
//
