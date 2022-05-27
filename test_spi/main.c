#include "SPI_init.h"
#include "SCI_init.h"
#include "ADIS16364.h"
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
    //SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, 0xBE01);
    SPI_writeDataBlockingNonFIFO(SUS_SPI_BASE, 0xBE10);

    while(1)
    {
/*

        //xg = RawToReal(SensorRead(XACCL_OUT, SBITS14), g_AcclScale,SBITS14, 1);
        //yg = RawToReal(SensorRead(YACCL_OUT, SBITS14), g_AcclScale,SBITS14, 1);
        yg = RawToReal(SensorRead(YGYRO_OUT, SBITS14), g_GyroScale, SBITS14, 1);
        //sprintf(buffer,"%d\r\n",(int16_t)xg);
        //SCI_writeCharArray(SCIA_BASE, (uint16_t*)buffer, 128);
*/
    }

}
