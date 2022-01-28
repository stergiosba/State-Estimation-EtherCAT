#include "SPI_init.h"
#include "SCI_init.h"
#include "ADIS_16354.h"
#include <stdio.h>


float32_t xg=0;
float32_t yg=0;
float32_t zg=0;
char buffer[128];
uint16_t imu_check;
int main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    SPI_init();
    SCI_init();
    EINT;
    ERTM;

    imu_check=IMUCommsCheck();

    while(1)
    {
        xg = SensorRead(ADIS16375_REG_X_ACCL_OUT);
        yg = SensorRead(ADIS16375_REG_Y_ACCL_OUT);
        zg = SensorRead(ADIS16375_REG_Z_ACCL_OUT);
        //sprintf(buffer,"%d\r\n",(int16_t)xg);
        //SCI_writeCharArray(SCIA_BASE, (uint16_t*)buffer, 128);

    }

}
