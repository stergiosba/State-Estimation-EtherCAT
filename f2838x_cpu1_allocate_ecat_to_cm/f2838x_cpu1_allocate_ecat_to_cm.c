//TODO RENAME FILE AND PROJECT

// Included Files
//
#include "device.h"
#include "SCI_init.h"
#include "ECAT_init.h"
#include <math.h>
#include "SPI_init.h"
#include <stdio.h>

#define DEBUG_MODE 1

//
// Function Prototypes
//
//TODO Make a IPC header file
void ECAT_exchangeDataCPUandCM(void);
#pragma DATA_SECTION(ipcCMToCPUDataBuffer, "MSGRAM_CM_TO_CPU_ECAT")
ECAT_IPC_GetDataBuffer ipcCMToCPUDataBuffer;

#pragma DATA_SECTION(ipcCPUToCMDataBuffer, "MSGRAM_CPU_TO_CM_ECAT")
ECAT_IPC_PutDataBuffer ipcCPUToCMDataBuffer;

#if DEBUG_MODE
        char* msg;
#endif

#if DEBUG_MODE == 2
        char* buffer;
        //long Ecat_Sw1_Return;
#endif



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

    //
    // Setup GPIOs for SPI/EtherCAT
    //
    SPI_init();
    ECAT_init();
#if DEBUG_MODE
    SCI_init();
    GPIO_setPadConfig(CCARD_LED_1_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(CCARD_LED_1_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(CCARD_LED_2_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(CCARD_LED_2_GPIO, GPIO_DIR_MODE_OUT);
    msg = "\r\nInitialization Successful!\0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 29);
#endif
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
        GPIO_writePin(CCARD_LED_1_GPIO, !ipcCPUToCMDataBuffer.statusNode.led1);
        GPIO_writePin(CCARD_LED_2_GPIO, !ipcCMToCPUDataBuffer.ctrlNode.sw2);
        //DEVICE_DELAY_US(5000);
#endif
        i++;
    }
}

void ECAT_exchangeDataCPUandCM()
{
    //TODO check why TwinCat3 does not show floats properly
    // CPU to CM data
    ipcCPUToCMDataBuffer.statusNode.led1 = ipcCMToCPUDataBuffer.ctrlNode.sw1;
    ipcCPUToCMDataBuffer.statusNode.led2 = ipcCMToCPUDataBuffer.ctrlNode.sw2;
    ipcCPUToCMDataBuffer.statusNode.led3 = ipcCMToCPUDataBuffer.ctrlNode.sw3;
    ipcCPUToCMDataBuffer.statusNode.led4 = ipcCMToCPUDataBuffer.ctrlNode.sw4;
}

//
// End of file
//
