#include "SPI_init.h"
#include "ADIS_16354.h"
#include <stdio.h>


int main(void)
{

    uint16_t sData = 0;                  // Send data
    uint16_t rData = 0;                  // Receive data
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    SPI_init();
    SCI_init();
    EINT;
    ERTM;

    while(1)
    {
        // Transmit data
        SPI_writeDataNonBlocking(SUS_SPI_BASE, sData);

        // Block until data is received and then return it
        rData = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);

        // Check received data against sent data
        if(rData != sData)
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }

        sData++;

    }

}
