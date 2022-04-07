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

#define SUS_SPI_BASE                      SPIA_BASE //!< SPI Interfaces (A/B/C/D).
#define SUS_SPI_BITRATE                   1000000UL //!< SPI Bitrate.
#define SUS_SPI_DATAWIDTH                 16U       //!< SPI Datawidth.

//Based on SPI_TransferProtocol enumeration from c2000ware spi.h
#define SUS_SPI_TRANSFER_PROTOCOL_OPT     SPI_PROT_POL1PHA0 //!< SPI Transfer Protocol Option.
#define SUS_SPI_LOOPBACK_OPT              0         //!< SPI Loopback option (OFF=0/ON=1).
#define SUS_SPI_FIFO_OPT                  0         //!< SPI FIFO option (OFF=0/ON=1).
//Based on SPI_Mode enumeration from c2000ware spi.h
#define SUS_SPI_MODE_OPT                  SPI_MODE_MASTER //!< SPI Modes (MASTER/SLAVE).

// Based on SPI_EmulationMode enumeration from c2000ware spi.h
#define SUS_SPI_EMULATION_OPT             SPI_EMULATION_FREE_RUN //!< SPI Emulation mode option.

#define SUS_SPI_INTERRUPTS_OPT            0         //!< SPI Interrupt mode (OFF=0/ON=1).

/* SPI Pin definitions */

#if SUS_SPI_BASE==SPIA_BASE
    #define SUS_SPI_SIMO                  GPIO_16_SPIA_SIMO //!< SPI SIMO Pin Map.
    #define SUS_GPIO_SPI_SIMO             16                //!< SPI SIMO Pin Number.
    #define SUS_SPI_SOMI                  GPIO_17_SPIA_SOMI //!< SPI SOMI Pin Map.
    #define SUS_GPIO_SPI_SOMI             17                //!< SPI SOMI Pin Number.
    #define SUS_SPI_CLK                   GPIO_18_SPIA_CLK  //!< SPI CLK Pin Map.
    #define SUS_GPIO_SPI_CLK              18                //!< SPI CLK Pin Number.
    #define SUS_SPI_STEN                  GPIO_19_SPIA_STEN //!< SPI STEN(CS) Pin Map.
    #define SUS_GPIO_SPI_STEN             19                //!< SPI STEN(CS) Pin Number.

#elif SUS_SPI_BASE==SPIB_BASE
    #define SUS_SPI_SIMO                  GPIO_24_SPIB_SIMO //!< SPI SIMO Pin Map.
    #define SUS_GPIO_SPI_SIMO             24                //!< SPI SIMO Pin Number.
    #define SUS_SPI_SOMI                  GPIO_25_SPIB_SOMI //!< SPI SOMI Pin Map.
    #define SUS_GPIO_SPI_SOMI             25                //!< SPI SOMI Pin Number.
    #define SUS_SPI_CLK                   GPIO_26_SPIB_CLK  //!< SPI CLK Pin Map.
    #define SUS_GPIO_SPI_CLK              26                //!< SPI CLK Pin Number.
    #define SUS_SPI_STEN                  GPIO_27_SPIB_STEN //!< SPI STEN(CS) Pin Map.
    #define SUS_GPIO_SPI_STEN             27                //!< SPI STEN(CS) Pin Number.

#elif SUS_SPI_BASE==SPIC_BASE
    #define SUS_SPI_SIMO                  GPIO_50_SPIC_SIMO //!< SPI SIMO Pin Map.
    #define SUS_GPIO_SPI_SIMO             50                //!< SPI SIMO Pin Number.
    #define SUS_SPI_SOMI                  GPIO_51_SPIC_SOMI //!< SPI SOMI Pin Map.
    #define SUS_GPIO_SPI_SOMI             51                //!< SPI SOMI Pin Number.
    #define SUS_SPI_CLK                   GPIO_52_SPIC_CLK  //!< SPI CLK Pin Map.
    #define SUS_GPIO_SPI_CLK              52                //!< SPI CLK Pin Number.
    #define SUS_SPI_STEN                  GPIO_53_SPIC_STEN //!< SPI STEN(CS) Pin Map.
    #define SUS_GPIO_SPI_STEN             53                //!< SPI STEN(CS) Pin Number.

#elif SUS_SPI_BASE==SPID_BASE
    #define SUS_SPI_SIMO                  GPIO_30_SPID_SIMO //!< SPI SIMO Pin Map.
    #define SUS_GPIO_SPI_SIMO             30                //!< SPI SIMO Pin Number.
    #define SUS_SPI_SOMI                  GPIO_31_SPID_SOMI //!< SPI SOMI Pin Map.
    #define SUS_GPIO_SPI_SOMI             31                //!< SPI SOMI Pin Number.
    #define SUS_SPI_CLK                   GPIO_32_SPID_CLK  //!< SPI CLK Pin Map.
    #define SUS_GPIO_SPI_CLK              32                //!< SPI CLK Pin Number.
    #define SUS_SPI_STEN                  GPIO_33_SPID_STEN //!< SPI STEN(CS) Pin Map.
    #define SUS_GPIO_SPI_STEN             33                //!< SPI STEN(CS) Pin Number.

#endif


void SPI_init();
void SPI_PinMuxOptions();

#endif /* SPI_DEFS_H_ */
