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
// Version 00.02.00 | 2022 | Bachoumas
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

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************
#define WRDLEN          16      // SPI Transfer Word Size
#define SPIOPFRQ        500000  // 500 kHz SPI Operational Frequency
#define SBITS14         14U     // 14 Significant Bits
#define SBITS12         12U     // 14 Significant Bits
#define ADIS16364_ID    0x3FEC  // ADIS16375 ID Number
#define ADIS_SMPL       819     // ADIS16375 Sampling Frequency [Hz]
#define SUPPLY          0       // Supply Voltage's Burst-Read Position
#define XGYRO           1       // X-Gyroscope Reading's Burst-Read Pos.
#define YGYRO           2       // Y-Gyroscope Reading's Burst-Read Pos.
#define ZGYRO           3       // Z-Gyroscope Reading's Burst-Read Pos.
#define XACCEL          4       // X-Accelerometer Reading's Burst-Read Pos.
#define YACCEL          5       // Y-Accelerometer Reading's Burst-Read Pos.
#define ZACCEL          6       // Z-Accelerometer Reading's Burst-Read Pos.
#define XTEMP           7       // X-Temperature Reading's Burst-Read Pos.
#define YTEMP           8       // Y-Temperature Reading's Burst-Read Pos.
#define ZTEMP           9       // Z-Temperature Reading's Burst-Read Pos.
#define ANALOG          10      // ADC Reading's Burst-Read Pos.

//*****************************************************************************
//
// ADIS16374 Register Addresses
//
//*****************************************************************************
#define FLASH_CNT   0x00    // Flash memory write count
#define SUPPLY_OUT  0x02    // Power supply measurement
#define XGYRO_OUT   0x04    // X-axis gyroscope output
#define YGYRO_OUT   0x06    // Y-axis gyroscope output
#define ZGYRO_OUT   0x08    // Z-axis gyroscope output
#define XACCL_OUT   0x0A    // X-axis accelerometer output
#define YACCL_OUT   0x0C    // Y-axis accelerometer output
#define ZACCL_OUT   0x0E    // Z-axis accelerometer output
#define XTEMP_OUT   0x10    // X-axis gyroscope temperature output
#define YTEMP_OUT   0x12    // Y-axis gyroscope temperature output
#define ZTEMP_OUT   0x14    // Z-axis gyroscope temperature output
#define AUX_ADC     0x16    // Auxiliary ADC output
#define XGYRO_OFF   0x1A    // X-axis gyroscope bias offset
#define YGYRO_OFF   0x1C    // Y-axis gyroscope bias offset
#define ZGYRO_OFF   0x1E    // Z-axis gyroscope bias offset
#define XACCL_OFF   0x20    // X-axis acceleration bias offset
#define YACCL_OFF   0x22    // Y-axis acceleration bias offset
#define ZACCL_OFF   0x24    // Z-axis acceleration bias offset
#define ALM_MAG1    0x26    // Alarm 1 amplitude threshold
#define ALM_MAG2    0x28    // Alarm 2 amplitude threshold
#define ALM_SMPL1   0x2A    // Alarm 1 sample size
#define ALM_SMPL2   0x2C    // Alarm 2 sample size
#define ALM_CTRL    0x2E    // Alarm control
#define AUX_DAC     0x30    // Auxiliary DAC data
#define GPIO_CTRL   0x32    // Auxiliary digital input/output control
#define MSC_CTRL    0x34    // Data ready, self-test, miscellaneous
#define SMPL_PRD    0x36    // Internal sample period (rate) control
#define SENS_AVG    0x38    // Dynamic range and digital filter control
#define SLP_CNT     0x3A    // Sleep mode control
#define DIAG_STAT   0x3C    // System status
#define GLOB_CMD    0x3E    // System commands
#define PROD_ID     0x56    // Product Identification Address

//*****************************************************************************
//
// Global Variable Definitions
//
//*****************************************************************************
extern const float g_SupplyOutScale;
extern float g_GyroScale;
extern const float g_AcclScale;
extern const float g_TempScale;
extern const float g_AdcScale;
extern float g_SensBurst[11];
extern unsigned short int g_ActiveDRng;
extern unsigned short int g_ActiveTaps;
extern unsigned short int g_MinTaps;

//*****************************************************************************
//
// Global Function Prototypes
//
//*****************************************************************************
extern void InitSpiA(void);
extern void InitSpiB(void);
extern void BurstRead(void);
extern uint16_t SensorRead(uint16_t Reg, unsigned short int NumBits);
extern float RawToReal(uint16_t Raw, float RegScale,
                       unsigned short int NumBits, unsigned short int Sign);
unsigned short int SensorWrite(unsigned short int Reg,
                               unsigned short int Value);
extern uint16_t TwosComp(float Num);
extern unsigned short int ResetIMU(void);
extern unsigned short int DRngFIRCtrl(unsigned short int Range);
extern unsigned short int TapFIRCtrl(unsigned short int Taps);
unsigned short int IMUCommsCheck(void);
unsigned short int ADISConfig(void);
char IMUPowerMode(void);
uint16_t IMUPerformSelfTest(void);

#endif  // ADIS16364_H_

//! @}

//
//  End Of File
//
//
