//###########################################################################
//
// FILE:   ethercat_slave_cpu1_hal.c
//
// TITLE:  C28.CPU1 EtherCAT HAL Driver.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
// $Copyright:
// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "ethercat_slave_cpu1_hal.h"
#define PROFILE_MODE 0

#if PROFILE_MODE

#define INTERRUPT_PROFILE_BUFFER_SIZE 50
typedef struct
{
    uint32_t    Sync0_counter;
    uint32_t    Sync1_counter;
    uint32_t    PDI_counter;

    uint32_t    Sync0_stimes0[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    Sync0_stimes1[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    Sync0_etimes0[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    Sync0_etimes1[INTERRUPT_PROFILE_BUFFER_SIZE];

    uint32_t    Sync1_stimes0[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    Sync1_stimes1[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    Sync1_etimes0[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    Sync1_etimes1[INTERRUPT_PROFILE_BUFFER_SIZE];

    uint32_t    PDI_stimes0[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    PDI_stimes1[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    PDI_etimes0[INTERRUPT_PROFILE_BUFFER_SIZE];
    uint32_t    PDI_etimes1[INTERRUPT_PROFILE_BUFFER_SIZE];

}ISR_Profiler;


ISR_Profiler Profiler = {.Sync0_counter=0, .Sync1_counter=0, .PDI_counter=0};
#endif

#pragma DATA_SECTION(SPI_config,"Cla1DataRam")
SPI_Config SPI_config;

#pragma DATA_SECTION(ulCycleCount1,"Cla1ToCpuMsgRAM");
uint32_t ulCycleCount1;

uint32_t ESC_getTimer0(void);
void ESC_clearTimer0(void);

//*****************************************************************************
//
// ESC_getTimer
//
//*****************************************************************************
uint32_t
ESC_getTimer(void)
{
    //
    // Return 1's compliment of the CPU timer
    //
    return(~((uint32_t)CPUTimer_getTimerCount(CPUTIMER1_BASE)));
}

//*****************************************************************************
//
// ESC_getTimer0
//
//*****************************************************************************
uint32_t
ESC_getTimer0(void)
{
    //
    // Return 1's compliment of the CPU timer
    //
    return(~((uint32_t)CPUTimer_getTimerCount(CPUTIMER0_BASE)));
}

//*****************************************************************************
//
// ESC_clearTimer
//
//*****************************************************************************
void
ESC_clearTimer(void)
{
    //
    // Set the timer period count
    //
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFFUL);

    //
    // Reload timer with the period count value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
}

//*****************************************************************************
//
// ESC_clearTimer0
//
//*****************************************************************************
void
ESC_clearTimer0(void)
{
    //
    // Set the timer period count
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFFUL);

    //
    // Reload timer with the period count value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
}

//*****************************************************************************
//
// ESC_timerIncPerMilliSec
//
//*****************************************************************************
uint32_t
ESC_timerIncPerMilliSec(void)
{
    //
    // Returns value based on core frequency of 200MHz.
    //
    return((uint32_t)200000UL);
}

//*****************************************************************************
//
// ESC_readBlockISR
//
//*****************************************************************************
void
ESC_readBlockISR(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    //
    // Create pointer to ESC Address
    //
    const void * escSource = (void *)(ESC_BASE + (uint32_t)(address / 2U));

    //
    // Copy ESC data to buffer. Convert lengths to words.
    //
    memcpy(pData, escSource, (size_t)((len + 1U) >> 1U));

    //
    // Determine if length (in bytes) is even or odd
    // (No action on even)
    //
    if((len & 0x1U) == 0x1U)
    {
        //
        // Odd Length
        //

        //
        // Clear extra byte in buffer
        //
        pData[((len - 1U) / 2U)] = (pData[((len - 1U) / 2U)] & ESC_M_LSB);
    }
}

//*****************************************************************************
//
// ESC_readBlock
//
//*****************************************************************************
void
ESC_readBlock(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    //
    // Disables interrupts
    //
    DINT;

    //
    // Perform copy of ESC data to buffer
    //
    ESC_readBlockISR(pData, address, len);

    //
    // Enable interrupts
    //
    EINT;
}

//*****************************************************************************
//
// ESC_readDWordISR
//
//*****************************************************************************
uint32_t
ESC_readDWordISR(uint16_t address)
{
    //
    // Read 32-bit address from ESC memory
    //
    return(HWREG(ESC_BASE + (address / 2U)));
}

//*****************************************************************************
//
// ESC_readDWord
//
//*****************************************************************************
uint32_t
ESC_readDWord(uint16_t address)
{
    uint32_t dWordValue;

    //
    // Disables interrupts
    //
    DINT;

    //
    // Read 32-bit address from ESC memory
    //
    dWordValue = ESC_readDWordISR(address);

    //
    // Enable interrupts
    //
    EINT;

    //
    // Return value
    //
    return(dWordValue);
}

//*****************************************************************************
//
// ESC_readWordISR
//
//*****************************************************************************
uint16_t
ESC_readWordISR(uint16_t address)
{
    //
    // Read 16-bit address from ESC memory
    //
    return(HWREGH(ESC_BASE + (address / 2U)));
}

//*****************************************************************************
//
// ESC_readWord
//
//*****************************************************************************
uint16_t
ESC_readWord(uint16_t address)
{
    uint16_t wordValue;

    //
    // Disables interrupts
    //
    DINT;

    //
    // Read 16-bit address from ESC memory
    //
    wordValue = ESC_readWordISR(address);

    //
    // Enable interrupts
    //
    EINT;

    //
    // Return value
    //
    return(wordValue);
}

//*****************************************************************************
//
// ESC_writeBlockISR
//
//*****************************************************************************
void
ESC_writeBlockISR(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    uint16_t wordValue;

    //
    // Create pointer to ESC Address
    //
    void * escDest = (void *)(ESC_BASE + (uint32_t)(address / 2U));

    //
    // Determine if length (in bytes) is even or odd
    //
    if((len & 0x1U) == 0x1U)
    {
        //
        // Odd Length
        //

        //
        // Copy even bytes of buffer data to ESC memory.
        // Convert length to words.
        //
        memcpy(escDest, pData, (size_t)((len - 1U) >> 1U));

        //
        // Read last 16-bit word
        //
        wordValue = ESC_readWordISR(address + (len - 1U));

        //
        // Modify word data and set new data
        //
        wordValue &= ESC_M_MSB;
        wordValue |= (pData[((len - 1U) / 2U)] & ESC_M_LSB);

        //
        // Write modified value to ESC destination
        //
        ESC_writeWordISR(wordValue, (address + (len - 1U)));
    }
    else
    {
        //
        // Even Length
        //

        //
        // Copy buffer data to ESC memory. Convert length to words.
        //
        memcpy(escDest, pData, (size_t)(len >> 1U));
    }
}

//*****************************************************************************
//
// ESC_writeBlock
//
//*****************************************************************************
void
ESC_writeBlock(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    //
    // Disables interrupts
    //
    DINT;

    //
    // Write data buffer into ESC memory
    //
    ESC_writeBlockISR(pData, address, len);

    //
    // Enable interrupts
    //
    EINT;
}

//*****************************************************************************
//
// ESC_writeDWordISR
//
//*****************************************************************************
void
ESC_writeDWordISR(uint32_t dWordValue, uint16_t address)
{
    //
    // Write two 16-bit words to ESC memory
    //
    HWREG(ESC_BASE + (address / 2U)) = dWordValue;
}

//*****************************************************************************
//
// ESC_writeDWord
//
//*****************************************************************************
void
ESC_writeDWord(uint32_t dWordValue, uint16_t address)
{
    //
    // Disables interrupts
    //
    DINT;

    //
    // Write two 16-words into ESC memory
    //
    ESC_writeDWordISR(dWordValue, address);

    //
    // Enable interrupts
    //
    EINT;
}

//*****************************************************************************
//
// ESC_writeWordISR
//
//*****************************************************************************
void
ESC_writeWordISR(uint16_t wordValue, uint16_t address)
{
    //
    // Write 16-bit word into ESC memory
    //
    HWREGH(ESC_BASE + (address / 2U)) = wordValue;
}

//*****************************************************************************
//
// ESC_writeWord
//
//*****************************************************************************
void
ESC_writeWord(uint16_t wordValue, uint16_t address)
{
    //
    // Disables interrupts
    //
    DINT;

    //
    // Write one 16-word into ESC memory
    //
    ESC_writeWordISR(wordValue, address);

    //
    // Enable interrupts
    //
    EINT;
}

//*****************************************************************************
//
// ESC_setLed
//
//*****************************************************************************
void
ESC_setLed(uint16_t runLed, uint16_t errLed)
{
    //
    // Set/Clear Run LED
    //
    GPIO_writePin(ESC_RUN_LED_GPIO, (uint32_t)(runLed));

    //
    // Set/Clear Error LED
    //
    GPIO_writePin(ESC_ERR_LED_GPIO, (uint32_t)(errLed));
}

//*****************************************************************************
//
// ESC_loadedCheckEEPROM
//
//*****************************************************************************
uint16_t
ESC_loadedCheckEEPROM(void)
{
    uint16_t status;

    //
    // Get ESC DL Status register
    //
    status = ESC_readWord(ESC_O_DL_STATUS);

    //
    // Check if EEPROM is loaded
    //
    if((status & ESC_DL_STATUS_EEPROMLOAD_M) == ESC_DL_STATUS_EEPROMLOAD_M)
    {
        //
        // Get ESC EEPROM Status register
        //
        status = ESC_readWord(ESC_O_EEPROM_STATUS);

        //
        // Check if EEPROM is loaded and device information is okay
        //
        if((status & ESC_EEPROM_STATUS_EEPROMLOAD_M) == ESC_EEPROM_SUCCESS)
        {
            return(ESC_EEPROM_SUCCESS);
        }
        else
        {
            return(ESC_EEPROM_LOAD_ERROR);
        }
    }
    else
    {
        //
        // DL Status indicated EEPROM is not loaded
        //
        return(ESC_EEPROM_NOT_LOADED);
    }
}

//*****************************************************************************
//
// ESC_resetESC
//
//*****************************************************************************
void
ESC_resetESC(void)
{
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAT);
}

//*****************************************************************************
//
// ESC_holdESCInReset
//
//*****************************************************************************
void
ESC_holdESCInReset(void)
{
    //
    // Put ESC in reset
    //
    EALLOW;
    HWREGH(DEVCFG_BASE + SYSCTL_O_SOFTPRES23) |= SYSCTL_SOFTPRES23_ETHERCAT;
    EDIS;
}

//*****************************************************************************
//
// ESC_releaseESCReset
//
//*****************************************************************************
void
ESC_releaseESCReset(void)
{
    //
    // Release from reset
    //
    EALLOW;
    HWREGH(DEVCFG_BASE + SYSCTL_O_SOFTPRES23) &= (~SYSCTL_SOFTPRES23_ETHERCAT);
    EDIS;
}

//*****************************************************************************
//
// ESC_initHW
//
//*****************************************************************************
uint16_t
ESC_initHW(void)
{
    //
    // Set application-specific timeout for waiting for EEPROM to load
    // and one for waiting for memory initialization
    // (End user can adjust as needed)
    //
    uint16_t eepromTimeOut = 0x1000U;
    uint16_t memoryTimeOut = 0x300U;

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
    // Turn on all needed peripherals and initialize GPIOs (Do not open all peripherals for reduced power consumption)
    //
    Device_enableNeededPeripherals();
    Device_initGPIO();

    //
    // Setup AUX Clock for ECAT and CM
    // Configured to 500MHz raw ((25 * 20 IMULT) /1)
    //
    SysCtl_setAuxClock(SYSCTL_AUXPLL_ENABLE | SYSCTL_AUXPLL_OSCSRC_XTAL |
                       SYSCTL_AUXPLL_IMULT(20) | SYSCTL_AUXPLL_FMULT_0 |
                       SYSCTL_AUXPLL_DIV_1);

    //
    // Configure GPIOs for EtherCAT
    //
    ESC_initGPIO();

    //
    // Initialize SPI Peripheral
    //
    SPI_configure(&SPI_config);
    SPI_init(&SPI_config);
    SPI_PinMuxOptions(&SPI_config);

    //
    // Initialize CLA for CPU1
    //
    CLA_configClaMemory();
    CLA_initCpu1Cla1();
    initEPWM1();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Register EtherCAT Interrupt Handlers
    //
    Interrupt_register(INT_ECAT, &ESC_applicationLayerHandler);
    Interrupt_register(INT_ECATSYNC0, &ESC_applicationSync0Handler);
    Interrupt_register(INT_ECATSYNC1, &ESC_applicationSync1Handler);

    //
    // Enable ECAT/PDI, Sync0, and Sync1 interrupts in CPU
    //
    Interrupt_enable(INT_ECAT);
    Interrupt_enable(INT_ECATSYNC0);
    Interrupt_enable(INT_ECATSYNC1);

    //
    // Configure and Start timer
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFFUL);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0U);
    CPUTimer_startTimer(CPUTIMER0_BASE);

    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFFUL);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0U);
    CPUTimer_startTimer(CPUTIMER1_BASE);

    //
    // Aux = 500MHz and use /5 to get 100MHz for ECAT IP
    // (There is a built in /4 to get 25MHz for PHY when using
    //  internal clocking for PHY)
    //
    SysCtl_setECatClk(SYSCTL_ECATCLKOUT_DIV_5, SYSCTL_SOURCE_AUXPLL,
                      ESC_USE_INT_PHY_CLK);

    //
    // Configure EEPROM Size for 16K bits or less
    //
    ESCSS_configureEEPROMSize(ESC_SS_CONFIG_BASE, ESCSS_LESS_THAN_16K);

    //
    // Reset ESC
    //
    ESC_resetESC();

    //
    // Initialize ESCSS Memory
    //
    ESCSS_initMemory(ESC_SS_BASE);

    //
    // Wait for ESCSS memory initialization to complete
    //
    if(ESCSS_getMemoryInitDoneStatusBlocking(ESC_SS_BASE, memoryTimeOut) !=
       ESCSS_API_SUCCESS)
    {
        return(ESC_HW_INIT_FAIL);
    }

    //
    // Wait (with time out) for EEPROM to be loaded
    //
    while(ESC_loadedCheckEEPROM() != ESC_EEPROM_SUCCESS)
    {
        eepromTimeOut--;

        //
        // On time out, return fail
        //
        if(eepromTimeOut == 0U)
        {
            return(ESC_HW_INIT_FAIL);
        }
    }

    //
    // Initialize AL Event Mask to zero to prevent ESC interrupts until
    // set during stack state transition to SAFEOP
    //
    ESC_writeDWord(0UL, ESC_O_AL_EVENTMASK);

    //
    // Enable ECAT/PDI, Sync0, and Sync1 interrupts in ESCSS
    //
    ESCSS_setMaskedInterruptStatus(ESC_SS_BASE,
                                   (ESCSS_INTR_MASK_IRQ_MASK |
                                    ESCSS_INTR_MASK_SYNC0_MASK |
                                    ESCSS_INTR_MASK_SYNC1_MASK));

    //
    // Connect ESCSS Sync0/1 signals to respective interrupts in PIE
    //
    ESCSS_configureSync0Connections(ESC_SS_BASE, ESCSS_SYNC0_CONFIG_C28X_PIE_EN,
                                    ESCSS_VALID_KEY_VALUE);
    ESCSS_configureSync1Connections(ESC_SS_BASE, ESCSS_SYNC1_CONFIG_C28X_PIE_EN,
                                    ESCSS_VALID_KEY_VALUE);

    //
    // Enable interrupts to CPU
    //
    EINT;
#if PROFILE_MODE
    int ii;
    for (ii=0;ii< INTERRUPT_PROFILE_BUFFER_SIZE;ii++)
    {
        Profiler.Sync0_stimes0[ii] = 0;
        Profiler.Sync0_stimes1[ii] = 0;
        Profiler.Sync0_etimes0[ii] = 0;
        Profiler.Sync0_etimes1[ii] = 0;

        Profiler.Sync1_stimes0[ii] = 0;
        Profiler.Sync1_stimes1[ii] = 0;
        Profiler.Sync1_etimes0[ii] = 0;
        Profiler.Sync1_etimes1[ii] = 0;

        Profiler.PDI_stimes0[ii] = 0;
        Profiler.PDI_stimes1[ii] = 0;
        Profiler.PDI_etimes0[ii] = 0;
        Profiler.PDI_etimes1[ii] = 0;
    }
#endif
    return(ESC_HW_INIT_SUCCESS);
}

//*****************************************************************************
//
// ESC_releaseHW
//
//*****************************************************************************
uint16_t
ESC_releaseHW(void)
{
    //
    // Intentionally empty - Implementation is left to the end user
    //
    return(ESC_HW_TERMINATE);
}

//*****************************************************************************
//
// ESC_applicationLayerHandler
//
//*****************************************************************************
__interrupt void
ESC_applicationLayerHandler(void)
{
#if PROFILE_MODE

    if (Profiler.PDI_counter<INTERRUPT_PROFILE_BUFFER_SIZE)
    {
        Profiler.PDI_stimes0[Profiler.PDI_counter] = ESC_getTimer0();
        Profiler.PDI_stimes1[Profiler.PDI_counter] = ESC_getTimer();
    }
#endif

#ifdef ETHERCAT_STACK
#if AL_EVENT_ENABLED
    //
    // When stack is included and application event enabled, call stack PDI ISR
    //
    PDI_Isr();
#endif  // AL_EVENT_ENABLED
#endif  // ETHERCAT_STACK

    //
    // Acknowledge and clear interrupt in ESCSS
    //
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_IRQ_CLR);

    //
    // Acknowledge this interrupt located in PIE group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

#if PROFILE_MODE
    if (Profiler.PDI_counter<INTERRUPT_PROFILE_BUFFER_SIZE)
    {
        Profiler.PDI_etimes0[Profiler.PDI_counter] = ESC_getTimer0();
        Profiler.PDI_etimes1[Profiler.PDI_counter] = ESC_getTimer();
    }

    Profiler.PDI_counter++;
#endif
}

//*****************************************************************************
//
// ESC_applicationSync0Handler
//
//*****************************************************************************
__interrupt void
ESC_applicationSync0Handler(void)
{
#if PROFILE_MODE
    if (Profiler.Sync0_counter<INTERRUPT_PROFILE_BUFFER_SIZE)
    {
        Profiler.Sync0_stimes0[Profiler.Sync0_counter] = ESC_getTimer0();
        Profiler.Sync0_stimes1[Profiler.Sync0_counter] = ESC_getTimer();
    }

#endif

#ifdef ETHERCAT_STACK
#if DC_SUPPORTED
    //
    // When stack is included and DC is enabled, call stack Sync0 ISR
    //
    Sync0_Isr();
#endif  // DC_SUPPORTED
#endif  // ETHERCAT_STACK

    //
    // Acknowledge and clear interrupt in ESCSS
    //
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_SYNC0_CLR);

    //
    // Acknowledge this interrupt located in PIE group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

#if PROFILE_MODE
    if (Profiler.Sync0_counter<INTERRUPT_PROFILE_BUFFER_SIZE)
    {
        Profiler.Sync0_etimes0[Profiler.Sync0_counter] = ESC_getTimer0();
        Profiler.Sync0_etimes1[Profiler.Sync0_counter] = ESC_getTimer();
    }

    Profiler.Sync0_counter++;
#endif
}

//*****************************************************************************
//
// ESC_applicationSync1Handler
//
//*****************************************************************************
__interrupt void
ESC_applicationSync1Handler(void)
{
#if PROFILE_MODE
    if (Profiler.Sync1_counter<INTERRUPT_PROFILE_BUFFER_SIZE)
    {
        Profiler.Sync1_stimes0[Profiler.Sync1_counter] = ESC_getTimer0();
        Profiler.Sync1_stimes1[Profiler.Sync1_counter] = ESC_getTimer();
    }
#endif


#ifdef ETHERCAT_STACK
#if DC_SUPPORTED
    //
    // When stack is included and DC is enabled, call stack Sync1 ISR
    //
    Sync1_Isr();
#endif  // DC_SUPPORTED
#endif  // ETHERCAT_STACK

    //
    // Acknowledge and clear interrupt in ESCSS
    //
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_SYNC1_CLR);

    //
    // Acknowledge this interrupt located in PIE group 5
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);

#if PROFILE_MODE
    if (Profiler.Sync1_counter<INTERRUPT_PROFILE_BUFFER_SIZE)
    {
        Profiler.Sync1_etimes0[Profiler.Sync1_counter] = ESC_getTimer0();
        Profiler.Sync1_etimes1[Profiler.Sync1_counter] = ESC_getTimer();
    }
    Profiler.Sync1_counter++;
#endif
}

//
// End of File
//
