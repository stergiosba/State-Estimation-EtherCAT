/** \addtogroup F28388D_Drivers F28388D Drivers
* @{
*
* \file SPI_init.c
*
* \brief This file contains a generic SPI initialization function for the TMS320F28388D MCU.
*
* This file should not be changed directly, the user should change definitions inside SPI_init.h
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

#include "SPI_init.h"

void SPI_configure(uint32_t base,uint32_t clockrate, uint32_t datawidth, SPI_Config *spi_config)
{
    spi_config->spi_base            = base;
    spi_config->spi_clockrate       = clockrate;
    spi_config->spi_datawidth       = datawidth;
    spi_config->spi_master_core     = GPIO_CORE_CPU1;
    spi_config->spi_mode            = SPI_MODE_MASTER;
    spi_config->spi_protocol        = SPI_PROT_POL1PHA0;
    spi_config->spi_emulationmode   = SPI_EMULATION_FREE_RUN;
    spi_config->spi_endianess       = SPI_DATA_BIG_ENDIAN;

    spi_config->spi_opt_loopback    = 0x0;
    spi_config->spi_opt_fifo        = 0x0;
    spi_config->spi_opt_interrupts  = 0x0;

    switch (spi_config->spi_base)
    {
        case SPIA_BASE:
            spi_config->spi_periph_clk  = SYSCTL_PERIPH_CLK_SPIA;
            spi_config->spi_simo.map    = GPIO_16_SPIA_SIMO;
            spi_config->spi_simo.num    = 16U;
            spi_config->spi_somi.map    = GPIO_17_SPIA_SOMI;
            spi_config->spi_somi.num    = 17U;
            spi_config->spi_clk.map     = GPIO_18_SPIA_CLK;
            spi_config->spi_clk.num     = 18U;
            spi_config->spi_sten.map    = GPIO_19_SPIA_STEN;
            spi_config->spi_sten.num    = 19U;
            break;

        case SPIB_BASE:
            spi_config->spi_periph_clk  = SYSCTL_PERIPH_CLK_SPIB;
            spi_config->spi_simo.map    = GPIO_24_SPIB_SIMO;
            spi_config->spi_simo.num    = 24U;
            spi_config->spi_somi.map    = GPIO_25_SPIB_SOMI;
            spi_config->spi_somi.num    = 25U;
            spi_config->spi_clk.map     = GPIO_26_SPIB_CLK;
            spi_config->spi_clk.num     = 26U;
            spi_config->spi_sten.map    = GPIO_27_SPIB_STEN;
            spi_config->spi_sten.num    = 27U;
            break;

        case SPIC_BASE:
            spi_config->spi_periph_clk  = SYSCTL_PERIPH_CLK_SPIC;
            spi_config->spi_simo.map    = GPIO_50_SPIC_SIMO;
            spi_config->spi_simo.num    = 50U;
            spi_config->spi_somi.map    = GPIO_51_SPIC_SOMI;
            spi_config->spi_somi.num    = 51U;
            spi_config->spi_clk.map     = GPIO_52_SPIC_CLK;
            spi_config->spi_clk.num     = 52U;
            spi_config->spi_sten.map    = GPIO_53_SPIC_STEN;
            spi_config->spi_sten.num    = 53U;
            break;
        case SPID_BASE:
            spi_config->spi_periph_clk  = SYSCTL_PERIPH_CLK_SPID;
            spi_config->spi_simo.map    = GPIO_30_SPID_SIMO;
            spi_config->spi_simo.num    = 30U;
            spi_config->spi_somi.map    = GPIO_31_SPID_SOMI;
            spi_config->spi_somi.num    = 31U;
            spi_config->spi_clk.map     = GPIO_32_SPID_CLK;
            spi_config->spi_clk.num     = 32U;
            spi_config->spi_sten.map    = GPIO_33_SPID_STEN;
            spi_config->spi_sten.num    = 33U;
            break;
    }
} // End SPI_configure()


void SPI_init(SPI_Config* spi_config)
{
    //
    //SPI initialization
    //
    SysCtl_enablePeripheral(spi_config->spi_periph_clk);
    EALLOW;

    SPI_disableModule(spi_config->spi_base);

    SPI_setConfig(spi_config->spi_base, DEVICE_LSPCLK_FREQ, spi_config->spi_protocol ,
                  spi_config->spi_mode , spi_config->spi_clockrate, spi_config->spi_datawidth);

    if (spi_config->spi_opt_loopback)
    {
        SPI_enableLoopback(spi_config->spi_base);
    }
    else
    {
        SPI_disableLoopback(spi_config->spi_base);
    }

    SPI_setEmulationMode(spi_config->spi_base, spi_config->spi_emulationmode);

    if (spi_config->spi_opt_interrupts)
    {
        SPI_clearInterruptStatus(spi_config->spi_base, SPI_INT_TXFF | SPI_INT_RXFF);
        SPI_enableInterrupt(spi_config->spi_base, SPI_INT_RXFF | SPI_INT_TXFF);
    }

    if (spi_config->spi_opt_fifo)
    {
        SPI_enableFIFO(spi_config->spi_base);
        SPI_setFIFOInterruptLevel(spi_config->spi_base, SPI_FIFO_TX2, SPI_FIFO_RX2);
    }
    else
    {
        SPI_disableFIFO(spi_config->spi_base);
    }

    SPI_enableModule(spi_config->spi_base);
    EDIS;

} // End SPI_init()

void SPI_PinMuxOptions(SPI_Config* spi_config)
{
    //
    // SPI Pinmux
    //
    GPIO_setMasterCore(spi_config->spi_simo.num, spi_config->spi_master_core);
    GPIO_setPinConfig(spi_config->spi_simo.map);
    GPIO_setPadConfig(spi_config->spi_simo.num, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(spi_config->spi_simo.num, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(spi_config->spi_somi.num, spi_config->spi_master_core);
    GPIO_setPinConfig(spi_config->spi_somi.map);
    GPIO_setPadConfig(spi_config->spi_somi.num, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(spi_config->spi_somi.num, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(spi_config->spi_clk.num, spi_config->spi_master_core);
    GPIO_setPinConfig(spi_config->spi_clk.map);
    GPIO_setPadConfig(spi_config->spi_clk.num, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(spi_config->spi_clk.num, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(spi_config->spi_sten.num, spi_config->spi_master_core);
    GPIO_setPinConfig(spi_config->spi_sten.map);
    GPIO_setPadConfig(spi_config->spi_sten.num, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(spi_config->spi_sten.num, GPIO_QUAL_ASYNC);

} // End SPI_PinMuxOptions()
