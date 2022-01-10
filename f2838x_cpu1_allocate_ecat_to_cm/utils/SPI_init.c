/*
 * SPI_init.c
 *
 *  Created on: Jan 9, 2022
 *      Author: Stergios
 */

#include "SPI_init.h"

void SPI_init()
{
    GPIO_setPinConfig(PE_SPI_CLK);
    GPIO_setPinConfig(PE_SPI_STEN);
    GPIO_setPinConfig(PE_SPI_SIMO);
    GPIO_setPinConfig(PE_SPI_SOMI);

    //SPIA_slave initialization
    SPI_disableModule(PE_SPI_BASE);
    SPI_setConfig(PE_SPI_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_SLAVE, PE_SPI_BITRATE,   16);
    SPI_disableFIFO(PE_SPI_BASE);
    SPI_disableLoopback(PE_SPI_BASE);
    SPI_setEmulationMode(PE_SPI_BASE, SPI_EMULATION_FREE_RUN);
    SPI_enableModule(PE_SPI_BASE);
}
