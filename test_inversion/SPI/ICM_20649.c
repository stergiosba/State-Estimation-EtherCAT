/*
 * ICM_20649.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Stergios
 */


#include "ICM_20649.h"

/*
void setBank(Register* reg) {
    uint16_t bank_value = (reg->bank & 0x03)<<BANK_BIT_OFFSET;
    WriteRegister(ICM20649_REG_BANK_SEL, bank_value);
}*/


void WriteRegister(uint16_t reg_addr, uint16_t value)
{
    uint16_t cmd[2] = { reg_addr<<8 , 0xFFU & value };
    //
    // Combine value & Register's address to a single Write Command
    //
    //cmd |= reg;

    //
    // Left Shift Register's Value to comply with IMU's SPI Transfer Form
    //
    //cmd <<= 8U;

    //
    // Form the Register's Write Command
    //
    //cmd |= (0x00FFU & value);

    SPI_writeDataNonBlocking(SUS_SPI_BASE, cmd[0] | cmd[1]);
    DEVICE_DELAY_US((30U));
}


float ReadSensor(uint16_t reg_addr_h, uint16_t reg_addr_l, float sensor_scale)
{
    uint16_t RawH = ReadRegister(reg_addr_h);
    uint16_t RawL = ReadRegister(reg_addr_l);
    uint16_t Raw = ((RawH<<8) | RawL);
    //uint16_t Raw = RawH<<8;
    uint16_t SignMask = 0xFFFF<<15;

    float value = (Raw & SignMask)
            ?(-sensor_scale * (~Raw + 1.0f)):
            (sensor_scale * Raw);
    return value;
}

uint16_t ReadRegister(uint16_t reg_addr)
{
    //setBank(reg);
    uint16_t Raw = 0x0000;

    uint16_t cmd = (READ_CMD_CODE| reg_addr) <<8;

    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, cmd);
    DEVICE_DELAY_US((50U));

    Raw = SPI_readDataBlockingNonFIFO(SUS_SPI_BASE);
    return Raw;
}

uint16_t IMUCommsCheck()
{
    //
    // IMU Startup Reset
    //
    //ResetIMU();

    //
    // Check if the Prescribed Product ID matches with the Acquired one.
    //
    uint16_t code = ReadRegister(ICM20649_WHO_AM_I);

    return (uint16_t)(code == (uint16_t)ICM20649_ID);

}

void IMUWakeUp()
{
    //
    // IMU starts in sleep mode and so we flip the wake up bit (6th) in ICM20649_PWR_MGMT_1
    //
    WriteRegister(ICM20649_PWR_MGMT_1, WAKE_UP_CMD);
    DEVICE_DELAY_US((1000U));
}

