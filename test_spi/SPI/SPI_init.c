/*
 * SPI_init.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Stergios
 *      Package: Pegasus (https://github.com/stergiosba/Pegasus)
 */

#include "SPI_init.h"

void SPI_init()
{
    EALLOW;
    SPI_PinMuxOptions();

    //SPi initialization
    SPI_disableModule(SUS_SPI_BASE);

    SPI_setConfig(SUS_SPI_BASE, DEVICE_LSPCLK_FREQ, SUS_SPI_TRANSFER_PROTOCOL_OPT,
                  SUS_SPI_MODE_OPT, SUS_SPI_BITRATE, SUS_SPI_DATAWIDTH);

    #if SUS_SPI_LOOPBACK_OPT == 1
        SPI_enableLoopback(SUS_SPI_BASE);
    #else
        SPI_disableLoopback(SUS_SPI_BASE);
    #endif

    SPI_setEmulationMode(SUS_SPI_BASE, SUS_SPI_EMULATION_OPT);

    #if SUS_SPI_FIFO_OPT == 1
        SPI_enableFIFO(SUS_SPI_BASE);
        SPI_setFIFOInterruptLevel(SUS_SPI_BASE, SPI_FIFO_TX2, SPI_FIFO_RX2);
    #else
        SPI_disableFIFO(SUS_SPI_BASE);
    #endif

    #if SUS_SPI_INTERRUPTS_OPT == 1
        SPI_clearInterruptStatus(SUS_SPI_BASE, SPI_INT_TXFF | SPI_INT_RXFF);
        SPI_enableInterrupt(SUS_SPI_BASE, SPI_INT_RXFF | SPI_INT_TXFF);
    #endif

    SPI_enableModule(SUS_SPI_BASE);
    EDIS;
}



void SPI_PinMuxOptions()
{
    //
    // SPI Pinmux
    //
    GPIO_setMasterCore(SUS_GPIO_SPI_SIMO, GPIO_CORE_CPU1);
    GPIO_setPinConfig(SUS_SPI_SIMO);
    GPIO_setPadConfig(SUS_GPIO_SPI_SIMO, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(SUS_GPIO_SPI_SIMO, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(SUS_GPIO_SPI_SOMI, GPIO_CORE_CPU1);
    GPIO_setPinConfig(SUS_SPI_SOMI);
    GPIO_setPadConfig(SUS_GPIO_SPI_SOMI, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(SUS_GPIO_SPI_SOMI, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(SUS_GPIO_SPI_CLK, GPIO_CORE_CPU1);
    GPIO_setPinConfig(SUS_SPI_CLK);
    GPIO_setPadConfig(SUS_GPIO_SPI_CLK, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(SUS_GPIO_SPI_CLK, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(SUS_GPIO_SPI_STEN, GPIO_CORE_CPU1);
    GPIO_setPinConfig(SUS_SPI_STEN);
    GPIO_setPadConfig(SUS_GPIO_SPI_STEN, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(SUS_GPIO_SPI_STEN, GPIO_QUAL_ASYNC);
}
