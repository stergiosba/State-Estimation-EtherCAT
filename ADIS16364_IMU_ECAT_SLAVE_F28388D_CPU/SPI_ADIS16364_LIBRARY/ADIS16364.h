/** \addtogroup ADIS16364_Drivers ADIS16364 Drivers
* @{
*
* \file ADIS16364.h
*
* \brief This is the header file of ADIS16364 Firmware Drivers.
*
* Specifically, it contains all the necessary definitions of\n
* ADIS16364_utilities.c & SpiConfig.c
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
#ifndef ADIS16364_H_
#define ADIS16364_H_

/*****************************************************************************
*
* Include Files
*
*****************************************************************************/
#include "driverlib.h"

/*****************************************************************************
*
* Definitions and Commands
*
*****************************************************************************/

#define SBITS16                     16U     //!< Full 16 Significant Bits.
#define SBITS14                     14U     //!< 14 Lowest Significant Bits.
#define SBITS12                     12U     //!< 12 Lowest Significant Bits.
#define ADIS16364_ID                0x3FEC  //!< ADIS 16364 Identification Number.
#define ADIS16364_NULL_COMMAND      0x0000  //!< ADIS 16364 Null SPI command.
#define ADIS16364_BURST_COMMAND     0x3E00  //!< ADIS 16364 Burst-Read SPI command.
#define ADIS16364_DATA_READY_DELAY  DEVICE_DELAY_US(20U) //!< ADIS 16364 Data Ready Delay.
#define ADIS16364_SYS_READY_DELAY   DEVICE_DELAY_US(200*1000U) //!< ADIS 16364 Data Ready Delay.
#define ADIS16364_BIAS_RESET_DELAY  DEVICE_DELAY_US(50*1000U) //!< ADIS 16364 Bias Reset Delay.
#define ADIS16364_DEF_SMPL          819     //!< ADIS16364 Default Sampling Rate [Hz]
#define SUPPLY                      0       //!< Supply Voltage's Burst-Read Position.
#define XGYRO                       1       //!< X-Gyroscope Reading's Burst-Read Position.
#define YGYRO                       2       //!< Y-Gyroscope Reading's Burst-Read Position.
#define ZGYRO                       3       //!< Z-Gyroscope Reading's Burst-Read Position.
#define XACCEL                      4       //!< X-Accelerometer Reading's Burst-Read Position.
#define YACCEL                      5       //!< Y-Accelerometer Reading's Burst-Read Position.
#define ZACCEL                      6       //!< Z-Accelerometer Reading's Burst-Read Position.
#define XTEMP                       7       //!< X-Temperature Reading's Burst-Read Position.
#define YTEMP                       8       //!< Y-Temperature Reading's Burst-Read Position.
#define ZTEMP                       9       //!< Z-Temperature Reading's Burst-Read Position.
#define ANALOG                      10      //!< ADC Reading's Burst-Read Position.

/*****************************************************************************
*
* ADIS16374 Register Addresses
*
*****************************************************************************/
#define FLASH_CNT   0x00    //!< Flash memory write count
#define SUPPLY_OUT  0x02    //!< Power supply measurement
#define XGYRO_OUT   0x04    //!< X-axis gyroscope output
#define YGYRO_OUT   0x06    //!< Y-axis gyroscope output
#define ZGYRO_OUT   0x08    //!< Z-axis gyroscope output
#define XACCL_OUT   0x0A    //!< X-axis accelerometer output
#define YACCL_OUT   0x0C    //!< Y-axis accelerometer output
#define ZACCL_OUT   0x0E    //!< Z-axis accelerometer output
#define XTEMP_OUT   0x10    //!< X-axis gyroscope temperature output
#define YTEMP_OUT   0x12    //!< Y-axis gyroscope temperature output
#define ZTEMP_OUT   0x14    //!< Z-axis gyroscope temperature output
#define AUX_ADC     0x16    //!< Auxiliary ADC output
#define XGYRO_OFF   0x1A    //!< X-axis gyroscope bias offset
#define YGYRO_OFF   0x1C    //!< Y-axis gyroscope bias offset
#define ZGYRO_OFF   0x1E    //!< Z-axis gyroscope bias offset
#define XACCL_OFF   0x20    //!< X-axis acceleration bias offset
#define YACCL_OFF   0x22    //!< Y-axis acceleration bias offset
#define ZACCL_OFF   0x24    //!< Z-axis acceleration bias offset
#define ALM_MAG1    0x26    //!< Alarm 1 amplitude threshold
#define ALM_MAG2    0x28    //!< Alarm 2 amplitude threshold
#define ALM_SMPL1   0x2A    //!< Alarm 1 sample size
#define ALM_SMPL2   0x2C    //!< Alarm 2 sample size
#define ALM_CTRL    0x2E    //!< Alarm control
#define AUX_DAC     0x30    //!< Auxiliary DAC data
#define GPIO_CTRL   0x32    //!< Auxiliary digital input/output control
#define MSC_CTRL    0x34    //!< Data ready, self-test, miscellaneous
#define SMPL_PRD    0x36    //!< Internal sample period (rate) control
#define SENS_AVG    0x38    //!< Dynamic range and digital filter control
#define SLP_CNT     0x3A    //!< Sleep mode control
#define DIAG_STAT   0x3C    //!< System status
#define GLOB_CMD    0x3E    //!< System commands
#define PROD_ID     0x56    //!< Product Identification Address

/*****************************************************************************
*
* Global Variable Definitions
*
*****************************************************************************/
extern const float g_SupplyOutScale; //!< Power Supply Voltage [mV per LSB]
extern float g_GyroScale; //!< Gyroscope Registers' Scales [deg/s per LSB]
extern const float g_AcclScale; //!< Accelerometer Registers' Scales [deg/s per LSB]
extern const float g_TempScale; //!< Temperature Register Scale [C per LSB]  -- 0x0 -> 25 C
extern const float g_AdcScale; //!< Auxialiary ADC (Analog to Digital Converter) Data Bits Scale [mV per LSB]
extern uint16_t g_ActiveDRng; //!< Active Dynamic Range Option
extern uint16_t g_ActiveTaps; //!< Active Filtering Taps Option
extern uint16_t g_MinTaps; //!< Minimum Taps for each Dynamic Range Variable
extern float g_SensBurst[11]; //!< Sensor Burst-Mode Read Vector

/*****************************************************************************
*
* Global Function Prototypes
*
*****************************************************************************/
extern void BurstRead(void);
extern uint16_t SensorRead(uint16_t Reg, uint16_t NumBits);
extern float RawToReal(uint16_t Raw, float RegScale, uint16_t NumBits, uint16_t Sign);
extern float RawToRealSign(uint16_t Raw, float RegScale);
extern uint16_t RegisterWrite(uint16_t Reg, uint16_t Value);
extern uint16_t ResetIMU(void);
extern uint16_t DRngFIRCtrl(uint16_t Range);
extern uint16_t TapFIRCtrl(uint16_t Taps);
extern uint16_t IMUCommsCheck(void);
extern uint16_t ADISConfig(void);
extern void IMUGyroBiasNullCalibration(void);

#endif  // ADIS16364_H_

/** @}*/

//
//  End Of File
//
//
