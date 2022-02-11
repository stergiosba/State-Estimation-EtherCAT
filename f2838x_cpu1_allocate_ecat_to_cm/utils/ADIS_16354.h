/*
 * ADIS_16354.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Stergios
 */

#include "SPI_init.h"

#ifndef SPI_ADIS_16354_H_
#define SPI_ADIS_16354_H_

#define ADIS16375_ID                            0x3FF7

#define ADIS16375_REG(page, reg) (((reg << 8) & 0x7F00) + (page))


#define ADIS16375_REG_SEQ_CNT                   ADIS16375_REG(0x00, 0x06)
#define ADIS16375_REG_SYS_E_FLAG                ADIS16375_REG(0x00, 0x08)
#define ADIS16375_REG_DIAG_STS                  ADIS16375_REG(0x00, 0x0A)
#define ADIS16375_REG_ALM_STS                   ADIS16375_REG(0x00, 0x0C)
#define ADIS16375_REG_TEMP_OUT                  ADIS16375_REG(0x00, 0x0E)
#define ADIS16375_REG_X_GYRO_OUT                ADIS16375_REG(0x00, 0x12)
#define ADIS16375_REG_X_GYRO_LOW                ADIS16375_REG(0x00, 0x10)
#define ADIS16375_REG_Y_GYRO_OUT                ADIS16375_REG(0x00, 0x16)
#define ADIS16375_REG_Y_GYRO_LOW                ADIS16375_REG(0x00, 0x14)
#define ADIS16375_REG_Z_GYRO_OUT                ADIS16375_REG(0x00, 0x1A)
#define ADIS16375_REG_Z_GYRO_LOW                ADIS16375_REG(0x00, 0x18)
#define ADIS16375_REG_X_ACCL_OUT                ADIS16375_REG(0x00, 0x1E)
#define ADIS16375_REG_X_ACCL_LOW                ADIS16375_REG(0x00, 0x1C)
#define ADIS16375_REG_Y_ACCL_OUT                ADIS16375_REG(0x00, 0x22)
#define ADIS16375_REG_Y_ACCL_LOW                ADIS16375_REG(0x00, 0X20)
#define ADIS16375_REG_Z_ACCL_OUT                ADIS16375_REG(0x00, 0x26)
#define ADIS16375_REG_Z_ACCL_LOW                ADIS16375_REG(0x00, 0x24)
#define ADIS16375_REG_PROD_ID                   ADIS16375_REG(0x00, 0x7E)
#define ADIS16375_REG_GLOB_CMD                  ADIS16375_REG(0x03U, 0x02U)
#define ADIS16375_REG_SLP_CNT                   ADIS16375_REG(0x03U, 0x10U)

extern float32_t SensorRead(uint16_t reg);
extern uint16_t RegisterRead(uint16_t);
extern uint16_t RegisterWrite(uint16_t Reg, uint16_t Value);
extern uint16_t IMUCommsCheck(void);
extern uint16_t ResetIMU(void);
extern unsigned short PageCheck(uint16_t page);

#endif /* SPI_ADIS_16354_H_ */
