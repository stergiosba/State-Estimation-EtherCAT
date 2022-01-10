/*
 * SPI_init.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Stergios
 */

#ifndef SPI_DEFS_H_
#define SPI_DEFS_H_

#include "inc/hw_memmap.h"
#include "sysctl.h"
#include "gpio.h"
#include "pin_map.h"
#include "device.h"

/*
 * Definitions for SPI Communication
 * ------------------------------------
 *    for MCU TMS320F28388D in C2000Ware.
 *    based on Table 6-7. GPIO Muxed Pins pages 74~76
 */

// SPI Interfaces (A/B/C/D)
#define PE_SPI_BASE SPIA_BASE
#define PE_SPI_BITRATE 500000

/* SPI Pin definitions */

#if PE_SPI_BASE==SPIA_BASE
    #define PE_SPI_CLK             GPIO_18_SPIA_CLK
    #define PE_SPI_STEN            GPIO_19_SPIA_STEN
    #define PE_SPI_SIMO            GPIO_16_SPIA_SIMO
    #define PE_SPI_SOMI            GPIO_17_SPIA_SOMI
#elif PE_SPI_BASE==SPIB_BASE
    #define PE_SPI_CLK             GPIO_26_SPIB_CLK
    #define PE_SPI_STEN            GPIO_27_SPIB_STEN
    #define PE_SPI_SIMO            GPIO_24_SPIB_SIMO
    #define PE_SPI_SOMI            GPIO_25_SPIB_SOMI

#elif PE_SPI_BASE==SPIC_BASE
    #define PE_SPI_CLK             GPIO_52_SPIC_CLK
    #define PE_SPI_STEN            GPIO_53_SPIC_STEN
    #define PE_SPI_SIMO            GPIO_50_SPIC_SIMO
    #define PE_SPI_SOMI            GPIO_51_SPIC_SOMI

#elif PE_SPI_BASE==SPID_BASE
    #define PE_SPI_CLK             GPIO_32_SPID_CLK
    #define PE_SPI_STEN            GPIO_33_SPID_STEN
    #define PE_SPI_SIMO            GPIO_30_SPID_SIMO
    #define PE_SPI_SOMI            GPIO_31_SPID_SOMI

#endif


void SPI_init();


#endif /* SPI_DEFS_H_ */
