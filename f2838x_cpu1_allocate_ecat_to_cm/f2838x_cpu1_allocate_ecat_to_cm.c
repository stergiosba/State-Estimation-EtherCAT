//TODO RENAME FILE AND PROJECT

// Included Files
//
#include "SCI_init.h"
#include "ECAT_init.h"
#include <math.h>
#include "SPI_init.h"
#include <stdio.h>
#include "ADIS16364.h"
//#include "ADIS_16354.h"

#define DEBUG_MODE 1

//
// Function Prototypes
//
//TODO Make a IPC header file
void ECAT_exchangeDataCPUandCM(void);
#pragma DATA_SECTION(ipcCMToCPUDataBuffer, "MSGRAM_CM_TO_CPU_ECAT")
IMU_ECAT_IPC_GetDataBuffer ipcCMToCPUDataBuffer;

#pragma DATA_SECTION(ipcCPUToCMDataBuffer, "MSGRAM_CPU_TO_CM_ECAT")
IMU_ECAT_IPC_PutDataBuffer ipcCPUToCMDataBuffer;

#if DEBUG_MODE
        char* msg;
#endif
uint16_t imu_check;
char mode;
uint16_t selftest = 0;
uint16_t tests;
#if DEBUG_MODE == 2
        char* buffer;
        //long Ecat_Sw1_Return;
#endif


#define TEST_VALUE 157

//
// Main
//
void main(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

#ifdef _FLASH
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: Flash_initModule();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif

    //
    // Set up device clock
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Make sure the LSPCLK divider is set to the default (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

    //
    // Turn on all peripherals and initialize GPIOs
    //
    Device_enableAllPeripherals();
    Device_initGPIO();

    //
    // Setup AUX Clock for ECAT and CM
    // Configured to 500MHz raw ((25 * 20 IMULT) /1)
    //
    SysCtl_setAuxClock(SYSCTL_AUXPLL_ENABLE | SYSCTL_AUXPLL_OSCSRC_XTAL |
                       SYSCTL_AUXPLL_IMULT(20) | SYSCTL_AUXPLL_FMULT_0 |
                       SYSCTL_AUXPLL_DIV_1);

    Interrupt_initModule();
    Interrupt_initVectorTable();
    //
    // Setup GPIOs for SPI/EtherCAT
    //
    SPI_init();
    ECAT_init();
    //imu_check=IMUCommsCheck();
    //mode = IMUPowerMode();
    //selftest = IMUPerformSelfTest();
#if DEBUG_MODE
    SCI_init();
    GPIO_setPadConfig(CCARD_LED_1_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(CCARD_LED_1_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(CCARD_LED_2_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(CCARD_LED_2_GPIO, GPIO_DIR_MODE_OUT);
    msg = "\r\n?SUS>Board Initialization Success!\0\n";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 42);
    msg = (imu_check) ? "\r\n?SUS>IMU Initialization Success\0\n":"\r\nIMU Initialization Failed!\0\n";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 39);
#endif
    EINT;
    ERTM;
    //
    // Wait Forever
    //
    float i=1;


    while(1)
    {
#if DEBUG_MODE == 2
        sprintf(buffer,"%.4f\r\n",ipcCPUToCMDataBuffer.statusNode.led2);
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)buffer, 50);
#endif

        ECAT_exchangeDataCPUandCM();
#if DEBUG_MODE
        //GPIO_writePin(CCARD_LED_1_GPIO, !ipcCPUToCMDataBuffer.statusNode.led1);
        //GPIO_writePin(CCARD_LED_2_GPIO, !ipcCMToCPUDataBuffer.ctrlNode.sw2);
        //DEVICE_DELAY_US(5000);
#endif
        i++;
    }
}
/*
void ECAT_exchangeDataCPUandCM()
{
    // CPU to CM data
    ipcCPUToCMDataBuffer.statusNode.XGyro_sense = (ipcCMToCPUDataBuffer.ctrlNode.XGyro_on)
            ? SensorRead(ADIS16375_REG_X_GYRO_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.YGyro_sense = (ipcCMToCPUDataBuffer.ctrlNode.YGyro_on)
            ? SensorRead(ADIS16375_REG_Y_GYRO_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.ZGyro_sense = (ipcCMToCPUDataBuffer.ctrlNode.ZGyro_on)
            ? SensorRead(ADIS16375_REG_Z_GYRO_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.XAcc_sense = (ipcCMToCPUDataBuffer.ctrlNode.XAcc_on)
            ? SensorRead(ADIS16375_REG_X_ACCL_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.YAcc_sense = (ipcCMToCPUDataBuffer.ctrlNode.YAcc_on)
            ? SensorRead(ADIS16375_REG_Y_ACCL_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.ZAcc_sense = (ipcCMToCPUDataBuffer.ctrlNode.ZAcc_on)
            ? SensorRead(ADIS16375_REG_Z_ACCL_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.Temp_sense = (ipcCMToCPUDataBuffer.ctrlNode.Temp_on)
            ? SensorRead(ADIS16375_REG_TEMP_OUT):0.0f;

    ipcCPUToCMDataBuffer.statusNode.XAngle_calc = (ipcCMToCPUDataBuffer.ctrlNode.XAngle_on)
            ? TEST_VALUE:0.0f;

    ipcCPUToCMDataBuffer.statusNode.YAngle_calc = (ipcCMToCPUDataBuffer.ctrlNode.YAngle_on)
            ? TEST_VALUE:0.0f;


    ipcCPUToCMDataBuffer.statusNode.ZAngle_calc = (ipcCMToCPUDataBuffer.ctrlNode.ZAngle_on)
            ? TEST_VALUE:0.0f;

    ipcCPUToCMDataBuffer.statusNode.XLinVel_calc = (ipcCMToCPUDataBuffer.ctrlNode.XLinVel_on)
            ? TEST_VALUE:0.0f;


    ipcCPUToCMDataBuffer.statusNode.YLinVel_calc = (ipcCMToCPUDataBuffer.ctrlNode.YLinVel_on)
            ? TEST_VALUE:0.0f;

    ipcCPUToCMDataBuffer.statusNode.ZLinVel_calc = (ipcCMToCPUDataBuffer.ctrlNode.ZLinVel_on)
            ? TEST_VALUE:0.0f;
}
*/
void ECAT_exchangeDataCPUandCM()
{

    // CPU to CM data
    ipcCPUToCMDataBuffer.statusNode.XGyro_sense = (ipcCMToCPUDataBuffer.ctrlNode.XGyro_on)
            ? SensorRead(XGYRO_OUT, SBITS14):0.0f;

    ipcCPUToCMDataBuffer.statusNode.YGyro_sense = (ipcCMToCPUDataBuffer.ctrlNode.YGyro_on)
            ? RawToReal(SensorRead(YGYRO_OUT, SBITS14), g_GyroScale, SBITS14, 1):0.0f;

    ipcCPUToCMDataBuffer.statusNode.ZGyro_sense = (ipcCMToCPUDataBuffer.ctrlNode.ZGyro_on)
            ? RawToReal(SensorRead(ZGYRO_OUT, SBITS14), g_GyroScale, SBITS14, 1):0.0f;

    ipcCPUToCMDataBuffer.statusNode.XAcc_sense = (ipcCMToCPUDataBuffer.ctrlNode.XAcc_on)
            ? RawToReal(SensorRead(XACCL_OUT, SBITS14), g_AcclScale, SBITS14, 1):0.0f;

    ipcCPUToCMDataBuffer.statusNode.YAcc_sense = (ipcCMToCPUDataBuffer.ctrlNode.YAcc_on)
            ? RawToReal(SensorRead(YACCL_OUT, SBITS14), g_AcclScale, SBITS14, 1):0.0f;

    ipcCPUToCMDataBuffer.statusNode.ZAcc_sense = (ipcCMToCPUDataBuffer.ctrlNode.ZAcc_on)
            ? RawToReal(SensorRead(ZACCL_OUT, SBITS14), g_AcclScale, SBITS14, 1):0.0f;

    ipcCPUToCMDataBuffer.statusNode.Temp_sense = (ipcCMToCPUDataBuffer.ctrlNode.Temp_on)
            ? RawToReal(SensorRead(ZACCL_OUT, SBITS14), g_AcclScale, SBITS14, 1):0.0f;

    ipcCPUToCMDataBuffer.statusNode.XAngle_calc = (ipcCMToCPUDataBuffer.ctrlNode.XAngle_on)
            ? TEST_VALUE:0.0f;

    ipcCPUToCMDataBuffer.statusNode.YAngle_calc = (ipcCMToCPUDataBuffer.ctrlNode.YAngle_on)
            ? TEST_VALUE:0.0f;


    ipcCPUToCMDataBuffer.statusNode.ZAngle_calc = (ipcCMToCPUDataBuffer.ctrlNode.ZAngle_on)
            ? TEST_VALUE:0.0f;

    ipcCPUToCMDataBuffer.statusNode.XLinVel_calc = (ipcCMToCPUDataBuffer.ctrlNode.XLinVel_on)
            ? TEST_VALUE:0.0f;


    ipcCPUToCMDataBuffer.statusNode.YLinVel_calc = (ipcCMToCPUDataBuffer.ctrlNode.YLinVel_on)
            ? TEST_VALUE:0.0f;

    ipcCPUToCMDataBuffer.statusNode.ZLinVel_calc = (ipcCMToCPUDataBuffer.ctrlNode.ZLinVel_on)
            ? TEST_VALUE:0.0f;
}

//
// End of file
//
