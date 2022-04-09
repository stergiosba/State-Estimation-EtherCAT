/*
 * SPI_init.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Stergios
 *      Package: Pegasus (https://github.com/stergiosba/Pegasus)
 */

#ifndef SPI_DEFS_H_
#define SPI_DEFS_H_

#include "device.h"

/*
 * Definitions for SPI Communication
 * ------------------------------------
 *    for MCU TMS320F28388D in C2000Ware.
 *    based on Table 6-7. GPIO Muxed Pins pages 74~76
 *    All definitions from Pegasus Package carry the SUS prefix
 */

// SPI Interfaces (A/B/C/D)
#define SUS_SPI_BASE                      SPIA_BASE
#define SUS_SPI_BITRATE                   1000000UL
#define SUS_SPI_DATAWIDTH                 16U

// SPI Transfer Protocol Option (SPI_TransferProtocol enumeration in spi.h)
#define SUS_SPI_TRANSFER_PROTOCOL_OPT     SPI_PROT_POL1PHA0
// SPI Loopback option (OFF=0/ON=1)
#define SUS_SPI_LOOPBACK_OPT              0
// SPI FIFO option (OFF=0/ON=1)
#define SUS_SPI_FIFO_OPT                  0
// SPI Modes (SPI_Mode enumeration in spi.h)
#define SUS_SPI_MODE_OPT                  SPI_MODE_MASTER
// SPI Emulation mode option (SPI_EmulationMode enumeration in spi.h)
#define SUS_SPI_EMULATION_OPT             SPI_EMULATION_FREE_RUN
// SPI Interrupt mode (OFF=0/ON=1)
#define SUS_SPI_INTERRUPTS_OPT            0

/* SPI Pin definitions */

#if SUS_SPI_BASE==SPIA_BASE
    #define SUS_SPI_SIMO                  GPIO_16_SPIA_SIMO
    #define SUS_GPIO_SPI_SIMO             16
    #define SUS_SPI_SOMI                  GPIO_17_SPIA_SOMI
    #define SUS_GPIO_SPI_SOMI             17
    #define SUS_SPI_CLK                   GPIO_18_SPIA_CLK
    #define SUS_GPIO_SPI_CLK              18
    #define SUS_SPI_STEN                  GPIO_19_SPIA_STEN
    #define SUS_GPIO_SPI_STEN             19

#elif SUS_SPI_BASE==SPIB_BASE
    #define SUS_SPI_SIMO                  GPIO_24_SPIB_SIMO
    #define SUS_GPIO_SPI_SIMO             24
    #define SUS_SPI_SOMI                  GPIO_25_SPIB_SOMI
    #define SUS_GPIO_SPI_SOMI             25
    #define SUS_SPI_CLK                   GPIO_26_SPIB_CLK
    #define SUS_GPIO_SPI_CLK              26
    #define SUS_SPI_STEN                  GPIO_27_SPIB_STEN
    #define SUS_GPIO_SPI_STEN             27

#elif SUS_SPI_BASE==SPIC_BASE
    #define SUS_SPI_SIMO                  GPIO_50_SPIC_SIMO
    #define SUS_GPIO_SPI_SIMO             50
    #define SUS_SPI_SOMI                  GPIO_51_SPIC_SOMI
    #define SUS_GPIO_SPI_SOMI             51
    #define SUS_SPI_CLK                   GPIO_52_SPIC_CLK
    #define SUS_GPIO_SPI_CLK              52
    #define SUS_SPI_STEN                  GPIO_53_SPIC_STEN
    #define SUS_GPIO_SPI_STEN             53

#elif SUS_SPI_BASE==SPID_BASE
    #define SUS_SPI_SIMO                  GPIO_30_SPID_SIMO
    #define SUS_GPIO_SPI_SIMO             30
    #define SUS_SPI_SOMI                  GPIO_31_SPID_SOMI
    #define SUS_GPIO_SPI_SOMI             31
    #define SUS_SPI_CLK                   GPIO_32_SPID_CLK
    #define SUS_GPIO_SPI_CLK              32
    #define SUS_SPI_STEN                  GPIO_33_SPID_STEN
    #define SUS_GPIO_SPI_STEN             33

#endif


void SPI_init();
void SPI_PinMuxOptions();

#endif /* SPI_DEFS_H_ */
