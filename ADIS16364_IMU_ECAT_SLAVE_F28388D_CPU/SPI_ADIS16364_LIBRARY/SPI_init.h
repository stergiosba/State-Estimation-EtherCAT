/** \addtogroup F28388D_Drivers F28388D Drivers
* @{
*
* \file SPI_init.h
*
* \brief This file contains all of the necessary macro definitions that are used for the SPI
* peripheral initialization of the TMS320F28388D MCU.
*
*
* Author:      Stergios Bachoumas\n
* Maintainer:  Konstantinos Machairas
*
* Revision History\n
* Version 00.01.00 | 2022 | Bachoumas
*
* (C) Copyright 2022, NTUA CSL-EP Legged Robots Team
*
*****************************************************************************/

#ifndef SPI_DEFS_H_
#define SPI_DEFS_H_

#include "device.h"

/*
 * Definitions for SPI Communication with ADIS IMU
 * ------------------------------------
 *    for MCU TMS320F28388D in C2000Ware.
 *    based on Table 6-7. GPIO Muxed Pins pages 74~76
 *    All definitions from Pegasus Package carry the SUS prefix
 */

typedef struct SPI_Pin
{
    uint32_t map;
    uint16_t num;
}SPI_Pin;

typedef struct SPI_Config
{
    //
    // SPI Bare Minimum Configuration
    //
    uint32_t spi_base;
    uint32_t spi_clockrate;
    uint32_t spi_datawidth;
    SysCtl_PeripheralPCLOCKCR spi_periph_clk;
    GPIO_CoreSelect spi_master_core;
    SPI_TransferProtocol spi_protocol;
    SPI_Mode spi_mode;
    SPI_EmulationMode spi_emulationmode;
    SPI_endianess spi_endianess;

    //
    // SPI Extra Options
    bool spi_opt_loopback;
    bool spi_opt_fifo;
    bool spi_opt_interrupts;

    //
    // SPI Explicit Pinout
    //
    SPI_Pin spi_simo;
    SPI_Pin spi_somi;
    SPI_Pin spi_clk;
    SPI_Pin spi_sten;

}SPI_Config;

//
// Global SPI configuration struct
//
extern SPI_Config SPI_config;

void SPI_configure(uint32_t base,uint32_t clockrate, uint32_t datawidth, SPI_Config *spi_config);
void SPI_init(SPI_Config* spi_config);
void SPI_PinMuxOptions(SPI_Config* spi_config);

#endif /* SPI_DEFS_H_ */
