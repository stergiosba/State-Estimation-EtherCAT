/*
 * \file ICM_20649.h
 *
 * \brief This is the header file for the ICM-20649 6 DoF
 * IMU sensor from InvenSense. It contains all function and
 * parameters definitions found on the sensor manual.
 *
 * Author: Stergios Bachoumas
 *
 * Revision History
 * Version 0.1.0 | 2022 | Stergios Bachoumas
 *
 * (C) Copyright 2020, NTUA CSL-EP Legged Robots Team
 */

#ifndef SPI_ICM_20649_H_
#define SPI_ICM_20649_H_


#include "stdint.h"
#include "SPI_init.h"
/*
 *
 * Definitions
 *
 */
#define ICM20649_ID                         0xE1
#define WAKE_UP_CMD                         0x01
#define BANK_BIT_OFFSET                     0x04
#define READ_CMD_CODE                       0x80


typedef struct
{
    uint16_t bank;
    uint16_t address;
    uint16_t value;
} Register;


/*
 *
 * User Bank 0 Registers' Address Symbols
 *
 */
#define ICM20649_WHO_AM_I                   0x00
#define ICM20649_USER_CTRL                  0x03
#define ICM20649_LP_CONFIG                  0x05
#define ICM20649_PWR_MGMT_1                 0x06
#define ICM20649_PWR_MGMT_2                 0x07
#define ICM20649_INT_PIN_CFG                0x0F
#define ICM20649_INT_ENABLE                 0x10
#define ICM20649_INT_ENABLE_1               0x11
#define ICM20649_INT_ENABLE_2               0x12
#define ICM20649_INT_ENABLE_3               0x13
#define ICM20649_I2C_MST_STATUS             0x17
#define ICM20649_INT_STATUS                 0x19
#define ICM20649_INT_STATUS_1               0x1A
#define ICM20649_INT_STATUS_2               0x1B
#define ICM20649_INT_STATUS_3               0x1C
#define ICM20649_DELAY_TIME_H               0x28
#define ICM20649_DELAY_TIME_L               0x29
#define ICM20649_ACCEL_XOUT_H               0x2D
#define ICM20649_ACCEL_XOUT_L               0x2E
#define ICM20649_ACCEL_YOUT_H               0x2F
#define ICM20649_ACCEL_YOUT_L               0x30
#define ICM20649_ACCEL_ZOUT_H               0x31
#define ICM20649_ACCEL_ZOUT_L               0x32
#define ICM20649_GYRO_XOUT_H                0x33
#define ICM20649_GYRO_XOUT_L                0x34
#define ICM20649_GYRO_YOUT_H                0x35
#define ICM20649_GYRO_YOUT_L                0x36
#define ICM20649_GYRO_ZOUT_H                0x37
#define ICM20649_GYRO_ZOUT_L                0x38
#define ICM20649_TEMP_OUT_H                 0x39
#define ICM20649_TEMP_OUT_L                 0x3A
#define ICM20649_EXT_SLV_SENS_DATA_00       0x3B
#define ICM20649_EXT_SLV_SENS_DATA_01       0x3C
#define ICM20649_EXT_SLV_SENS_DATA_02       0x3D
#define ICM20649_EXT_SLV_SENS_DATA_03       0x3E
#define ICM20649_EXT_SLV_SENS_DATA_04       0x3F
#define ICM20649_EXT_SLV_SENS_DATA_05       0x40
#define ICM20649_EXT_SLV_SENS_DATA_06       0x41
#define ICM20649_EXT_SLV_SENS_DATA_07       0x42
#define ICM20649_EXT_SLV_SENS_DATA_08       0x43
#define ICM20649_EXT_SLV_SENS_DATA_09       0x44
#define ICM20649_EXT_SLV_SENS_DATA_10       0x45
#define ICM20649_EXT_SLV_SENS_DATA_11       0x46
#define ICM20649_EXT_SLV_SENS_DATA_12       0x47
#define ICM20649_EXT_SLV_SENS_DATA_13       0x48
#define ICM20649_EXT_SLV_SENS_DATA_14       0x49
#define ICM20649_EXT_SLV_SENS_DATA_15       0x4A
#define ICM20649_EXT_SLV_SENS_DATA_16       0x4B
#define ICM20649_EXT_SLV_SENS_DATA_17       0x4C
#define ICM20649_EXT_SLV_SENS_DATA_18       0x4D
#define ICM20649_EXT_SLV_SENS_DATA_19       0x4E
#define ICM20649_EXT_SLV_SENS_DATA_20       0x4F
#define ICM20649_EXT_SLV_SENS_DATA_21       0x50
#define ICM20649_EXT_SLV_SENS_DATA_22       0x51
#define ICM20649_EXT_SLV_SENS_DATA_23       0x52
#define ICM20649_FIFO_EN_1                  0x66
#define ICM20649_FIFO_EN_2                  0x67
#define ICM20649_FIFO_RST                   0x68
#define ICM20649_FIFO_MODE                  0x69
#define ICM20649_FIFO_COUNTH                0x70
#define ICM20649_FIFO_COUNTL                0x71
#define ICM20649_FIFO_R_W                   0x72
#define ICM20649_DATA_RDY_STATUS            0x74
#define ICM20649_FIFO_CFG                   0x76
#define ICM20649_REG_BANK_SEL               0x7F

/*
 *
 * User Bank 1 Registers' Address Symbols
 *
 */
#define ICM20649_SELF_TEST_X_GYRO           0x02
#define ICM20649_SELF_TEST_Y_GYRO           0x03
#define ICM20649_SELF_TEST_Z_GYRO           0x04
#define ICM20649_SELF_TEST_X_ACCEL          0x0E
#define ICM20649_SELF_TEST_Y_ACCEL          0x0F
#define ICM20649_SELF_TEST_Z_ACCEL          0x10
#define ICM20649_XA_OFFS_H                  0x14
#define ICM20649_XA_OFFS_L                  0x15
#define ICM20649_YA_OFFS_H                  0x17
#define ICM20649_YA_OFFS_L                  0x18
#define ICM20649_ZA_OFFS_H                  0x1A
#define ICM20649_ZA_OFFS_L                  0x1B
#define ICM20649_TIMEBASE_CORRECTION_PLL    0x28

/*
 *
 * User Bank 2 Registers' Address Symbols
 *
 */
#define ICM20649_GYRO_SMPLRT_DIV            0x00
#define ICM20649_GYRO_CONFIG_1              0x01
#define ICM20649_GYRO_CONFIG_2              0x02
#define ICM20649_XG_OFFS_USRH               0x03
#define ICM20649_XG_OFFS_USRL               0x04
#define ICM20649_YG_OFFS_USRH               0x05
#define ICM20649_YG_OFFS_USRL               0x06
#define ICM20649_ZG_OFFS_USRH               0x07
#define ICM20649_ZG_OFFS_USRL               0x08
#define ICM20649_ODR_ALIGN_EN               0x09
#define ICM20649_ACCEL_SMPLRT_DIV_1         0x10
#define ICM20649_ACCEL_SMPLRT_DIV_2         0x11
#define ICM20649_ACCEL_INTEL_CTRL           0x12
#define ICM20649_ACCEL_WOM_THR              0x13
#define ICM20649_ACCEL_CONFIG               0x14
#define ICM20649_ACCEL_CONFIG_2             0x15
#define ICM20649_FSYNC_CONFIG               0x52
#define ICM20649_TEMP_CONFIG                0x53
#define ICM20649_MOD_CTRL_USR               0x54

//  User Bank 3
#define ICM20649_I2C_MST_ODR_CONFIG         0x00
#define ICM20649_I2C_MST_CTRL               0x01
#define ICM20649_I2C_MST_DELAY_CTRL         0x02
#define ICM20649_I2C_SLV0_ADDR              0x03
#define ICM20649_I2C_SLV0_REG               0x04
#define ICM20649_I2C_SLV0_CTRL              0x05
#define ICM20649_I2C_SLV0_DO                0x06
#define ICM20649_I2C_SLV1_ADDR              0x07
#define ICM20649_I2C_SLV1_REG               0x08
#define ICM20649_I2C_SLV1_CTRL              0x09
#define ICM20649_I2C_SLV1_DO                0x0A
#define ICM20649_I2C_SLV2_ADDR              0x0B
#define ICM20649_I2C_SLV2_REG               0x0C
#define ICM20649_I2C_SLV2_CTRL              0x0D
#define ICM20649_I2C_SLV2_DO                0x0E
#define ICM20649_I2C_SLV3_ADDR              0x0F
#define ICM20649_I2C_SLV3_REG               0x10
#define ICM20649_I2C_SLV3_CTRL              0x11
#define ICM20649_I2C_SLV3_DO                0x12
#define ICM20649_I2C_SLV4_ADDR              0x13
#define ICM20649_I2C_SLV4_REG               0x14
#define ICM20649_I2C_SLV4_CTRL              0x15
#define ICM20649_I2C_SLV4_DO                0x16
#define ICM20649_I2C_SLV4_DI                0x17


/*
 *
 * Global Function Definitions
 *
 */
extern void setBank(Register* reg);
extern uint16_t IMUCommsCheck();
extern uint16_t ReadRegister(uint16_t reg_addr);
//extern float ReadSensor(uint16_t reg_addr, float sensor_scale);
extern float ReadSensor(uint16_t reg_addr_h, uint16_t reg_addr_l, float sensor_scale);
extern void WriteRegister(uint16_t reg_addr, uint16_t value);
extern void IMUWakeUp(void);


#endif /* SPI_ICM_20649_H_ */
