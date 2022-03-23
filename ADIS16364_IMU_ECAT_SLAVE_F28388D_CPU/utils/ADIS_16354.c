/*
 * ADIS16354.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Stergios
 */

#include "ADIS_16354.h"

unsigned short int active_page = 0x0;


float32_t SensorRead(uint16_t reg)
{
    float32_t sens;
    uint16_t mask;

    uint16_t raw_data = RegisterRead(reg);
    mask = 0xFFFF<<(15);

    sens = (raw_data & mask)?(-1.0 * (~(raw_data) + 1) ):(1.0 * raw_data);

    return sens*0.8192;
}

uint16_t RegisterRead(uint16_t reg)
{
    PageCheck(reg);
    uint16_t raw_data;

    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, reg);
    DEVICE_DELAY_US(25);
    SPI_writeDataNonBlocking(SUS_SPI_BASE, 0x0000);
    DEVICE_DELAY_US(25);
    raw_data = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);
    return raw_data;
}

uint16_t RegisterWrite(uint16_t Reg, uint16_t Value)
{
    //
    // Initialize Register's Write Command Variable
    //
    uint16_t Cmd = 0x0000U;

    //
    // Check & Change, if necessary, current Register Page
    //
    PageCheck(Reg);

    //
    // Combine value & Register's address to a single Write Command
    //
    Cmd = ((Reg & 0xFF00U) | (Value & 0x00FFU)) | 0x8000U;

    //
    // Execute SPI Transfer
    //
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, Cmd);

    //
    // Data Ready Delay
    //
    DEVICE_DELAY_US((25U));

    //
    // Write Operation Successful
    //
    return 1;

}   // End Of RegWrite()

uint16_t ResetIMU(void)
{
    //
    // Result Variable Initialization
    //
    uint16_t Result = 1U;

    //
    // Execute the required SPI Transfers to Reset IMU
    //
    Result *= RegisterWrite(ADIS16375_REG_GLOB_CMD, 0x80U);
    Result *= RegisterWrite(ADIS16375_REG_GLOB_CMD + 0x0100U, 0x00U);

    //
    // System Ready Delay
    //
    DEVICE_DELAY_US((500000UL));
    //
    return Result;

}   // End Of ResetIMU()

uint16_t IMUCommsCheck(void)
{
    //
    // IMU Startup Reset
    //
    ResetIMU();

    //
    // Check if the Prescribed Product ID matches with the Acquired one.
    //
    volatile uint16_t ProdID = RegisterRead(ADIS16375_REG_PROD_ID);

    //return (uint16_t)(ProdID == (uint16_t)ADIS16375_ID);
    return (uint16_t) ProdID;

}   // End Of IMUCommsCheck()

//***************************************************
//pageflag = 0: Page Unchanged
//pageflag = 1: Page Changed

unsigned short PageCheck(uint16_t page)
{
    uint16_t page_flag=0;

    page &= 0x00FF;
    if (page != active_page) {
        active_page = page;
        page_flag=1;
        page |=(0x8000);
        SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE,page);
        DEVICE_DELAY_US(25);
    }
    return page_flag;
}
