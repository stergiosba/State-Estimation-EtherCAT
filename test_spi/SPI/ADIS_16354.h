/*
 * ADIS_16354.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Stergios
 */

#include "device.h"

#ifndef SPI_ADIS_16354_H_
#define SPI_ADIS_16354_H_

#define SUPPLY_OUT 0x02
#define XGYRO_OUT 0x04
#define YGYRO_OUT 0x06
#define ZGYRO_OUT 0x08
#define XACCL_OUT 0x0A
#define YACCL_OUT 0x0C
#define ZACCL_OUT 0x0E
#define XTEMP_OUT 0x10
#define YTEMP_OUT 0x12
#define ZTEMP_OUT 0x14
#define AUX_ADC 0x16

#define XGYRO_OFF 0x1A
#define YGYRO_OFF 0x1C
#define ZGYRO_OFF 0x1E
#define XACCL_OFF 0x20
#define YACCL_OFF 0x22
#define ZACCL_OFF 0x24
#define ALM_MAG1 0x26
#define ALM_MAG2 0x28
#define ALM_SMPL1 0x2A
#define ALM_SMPL2 0x2C
#define ALM_CTRL 0x2E
#define AUX_DAC 0x30

#define GPIO_CTRL 0x32
#define MSC_CTRL 0x34
#define SMPL_PRD 0x36 // TS = TB x (NS + 1)

#define SENS_AVG 0x38
#define SLP_CNT 0x3A
#define STATUS 0x3C
#define COMMAND 0x3E

void RegisterRead(uint16_t);
uint16_t TwosComplement(float32_t);

#endif /* SPI_ADIS_16354_H_ */
