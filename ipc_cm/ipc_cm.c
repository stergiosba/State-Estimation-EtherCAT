//
// Included Files
//
#include "cm.h"
#include "ipc.h"

//
// Defines
//
#define IPC_CMD_READ_MEM   0x1001
#define IPC_CMD_RESP       0x2001

#define TEST_PASS          0x5555
#define TEST_FAIL          0xAAAA


//
// IPC ISR for Flag 0.
// C28x core sends data without message queue using Flag 0
//
__interrupt void IPC_ISR0()
{
    int i;
    uint32_t command, addr, data;
    bool status = false;

    //
    // Read the command
    //
    IPC_readCommand(IPC_CM_L_CPU1_R, IPC_FLAG0, IPC_ADDR_CORRECTION_ENABLE,
                    &command, &addr, &data);

    if(command == IPC_CMD_READ_MEM)
    {
        status = true;

        //
        // Read and compare data
        //
        for(i=0; i<data; i++)
        {
            if(*((uint32_t *)addr + i) != i)
                status = false;
        }
    }
    uint32_t uui=0;
    //
    // Send response to C28x core
    //
    if(status)
    {
        IPC_sendResponse(IPC_CM_L_CPU1_R, uui);
    }
    else
    {
        IPC_sendResponse(IPC_CM_L_CPU1_R, TEST_FAIL);
    }

    //
    // Acknowledge the flag
    //
    IPC_ackFlagRtoL(IPC_CM_L_CPU1_R, IPC_FLAG0);
}

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CM_L_CPU1_R, IPC_FLAG_ALL);

    //
    // Enable IPC interrupts
    //
    IPC_registerInterrupt(IPC_CM_L_CPU1_R, IPC_INT0, IPC_ISR0);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CM_L_CPU1_R, IPC_FLAG31);

    //
    // Loop forever. Wait for IPC interrupt
    //
    while(1);
}


//
// End of File
//
