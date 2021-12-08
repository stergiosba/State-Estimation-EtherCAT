//
// Included Files
//
//#include "driverlib.h"
#include "ECAT_init.h"
#include "SCI_init.h"
//
// Defines
//
#define IPC_CMD_READ_MEM   0x1001
#define IPC_CMD_RESP       0x2001

#define TEST_PASS          0x5555
#define TEST_FAIL          0xAAAA


//#pragma DATA_SECTION(readData, "MSGRAM_CPU_TO_CM")
uint32_t readData[10];

uint32_t pass;

//
// Main
//
void main(void)
{
    int i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    //Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    //Interrupt_initVectorTable();

    configureECAT();

    SCI_init();

    //
    // Clear any IPC flags if set already
    //
    //IPC_clearFlagLtoR(IPC_CPU1_L_CM_R, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    //IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG31);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //

    EINT;
    ERTM;

    //
    // Fill in the data to be sent
    //
    for(i=0; i<10; i++)
    {
        readData[i] = i;
    }
    char* buffer;
    Struct lot;

    while(1){
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)"1", 1);
        /*
        //
        // Send a message without message queue
        // Since C28x and CM does not share the same address space for shared RAM,
        // ADDRESS_CORRECTION is enabled
        // Length of the data to be read is passed as data.
        //
        //IPC_sendCommand(IPC_CPU1_L_CM_R, IPC_FLAG0, IPC_ADDR_CORRECTION_ENABLE,
        //                IPC_CMD_READ_MEM, (uint32_t)readData, 10);

        //
        // Wait for acknowledgment
        //
        //IPC_waitForAck(IPC_CPU1_L_CM_R, IPC_FLAG0);

        //
        // Read response
        //

        //if(IPC_getResponse(IPC_CPU1_L_CM_R) == TEST_PASS)
        //{
        //    pass = 1;
        int ii= (int) IPC_getResponse(IPC_CPU1_L_CM_R);
        lot=litoa(ii,buffer,10);
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)buffer, lot.size);
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)"1", 1);

        GPIO_writePin(DEVICE_GPIO_PIN_LED1, IPC_getResponse(IPC_CPU1_L_CM_R));
        //}
        //else
        //{
        //    pass = 0;
        //}
        DEVICE_DELAY_US(50000);
        GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
        GPIO_writePin(DEVICE_GPIO_PIN_LED2, IPC_getResponse(IPC_CPU1_L_CM_R));
        DEVICE_DELAY_US(50000);
        GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);*/

    }
}


//
// End of File
//
