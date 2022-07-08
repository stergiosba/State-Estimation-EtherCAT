#ifndef ETHERCAT_F28388X_HAL_ETHERCAT_SLAVE_CPU1_HAL_H_
#define ETHERCAT_F28388X_HAL_ETHERCAT_SLAVE_CPU1_HAL_H_

//###########################################################################
//
// FILE:   ethercat_slave_cpu1_hal.h
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

#ifndef ETHERCAT_SLAVE_CPU1_HAL_H
#define ETHERCAT_SLAVE_CPU1_HAL_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup esc_cpu1_hal_api ESC CPU1 HAL
//! @{
//
//*****************************************************************************

//
// Included Files
//
#include "device.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//
// User Defined Files
//
#include "SPI_init.h"
#include "CLA_init.h"
#include "CLA_shared.h"



#ifdef ETHERCAT_STACK
#include "ecat_def.h"
#endif // ETHERCAT_STACK

//
// ESC Registers Base Address
//
#define ESC_BASE             0x50000UL

//
// ESC Register Offsets
//
#define ESC_O_DL_STATUS      0x0110U
#define ESC_O_PDI_CONTROL    0x0140U
#define ESC_O_AL_EVENTMASK   0x0204U
#define ESC_O_EEPROM_STATUS  0x0502U

//
// ESC Register Masks
//
#define ESC_DL_STATUS_EEPROMLOAD_M     0x1U
#define ESC_EEPROM_STATUS_EEPROMLOAD_M 0x1000U

//
// Defines for Success and Failure returns during hardware initialization
//
#define ESC_HW_INIT_SUCCESS  0x0U
#define ESC_HW_INIT_FAIL     0xFFFFU

//
// Defines for Success and Failure returns during hardware initialization
//
#define ESC_HW_TERMINATE    0x1U

//
// Masking Defines
//
#define ESC_M_MSB            0xFF00U
#define ESC_M_LSB            0xFFU

//
// ESC Clock Config
//
#define ESC_USE_INT_PHY_CLK   0x1U

//
// Typedef for ESC Memory Address Access Size
//
typedef uint16_t ESCMEM_ADDR;

//
// Defines to EEPROM Loaded Status
//
#define ESC_EEPROM_SUCCESS    0x0U
#define ESC_EEPROM_NOT_LOADED 0xFFFFU
#define ESC_EEPROM_LOAD_ERROR 0xFFFEU

//
// Defines for EtherCAT LED GPIOs (controlCARD)
//
#define ESC_RUN_LED_GPIO      146U
#define ESC_ERR_LED_GPIO      145U

//
// Stack Functions
//
#ifdef ETHERCAT_STACK
extern void Sync0_Isr(void);
extern void PDI_Isr(void);
extern void Sync1_Isr(void);
#endif // ETHERCAT_STACK

//
// HAL function prototypes
//
extern uint32_t ESC_getTimer0(void);
extern void ESC_clearTimer0(void);
extern void initEPWM1(void);

//*****************************************************************************
//
//! Gets the Current Timer Value
//!
//! This function returns the current timer counter value from the CPU timer.
//!
//! \return Returns the 1's compliment of the timer counter register value
//
//*****************************************************************************
extern uint32_t ESC_getTimer(void);

//*****************************************************************************
//
//! Clears the Timer Value
//!
//! This function resets the timer counter.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_clearTimer(void);

//*****************************************************************************
//
//! Get the Timer Increment Value
//!
//! This function returns a constant value of 200000UL for the timer increment
//! value as the CPU timer is configured to run at 200MHz.
//!
//! \return Returns a constant value depending on the max frequency of the
//! CPU timer
//
//*****************************************************************************
extern uint32_t ESC_timerIncPerMilliSec(void);

//*****************************************************************************
//
//! Reads the ESC Data into Local Buffer
//!
//! \param pData is the pointer to the local destination buffer.
//!        (Type of pointer depends on the host controller architecture,
//!         detailed in ecat_def.h or the Slave Stack Code Tool)
//! \param address is the EtherCAT slave controller offset address which
//!        specifies the offset within the ESC memory area in bytes.
//!        (Only valid addresses are used depending on ESC 8 bit, 16 bit, or
//!         32 bit access specified in ecat_def.h or the Slave Stack Code Tool)
//! \param len is the access size in bytes
//!
//! This function is used to access the ESC registers and the DPRAM area. The
//! function reads the requested number of bytes from the ESC address and copies
//! the data into the data buffer specified.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_readBlockISR(ESCMEM_ADDR *pData, uint16_t address,
                             uint16_t len);

//*****************************************************************************
//
//! Reads the ESC Data into Local Buffer with Interrupts Disabled
//!
//! \param pData is the pointer to the local destination buffer.
//!        (Type of pointer depends on the host controller architecture,
//!         detailed in ecat_def.h or the Slave Stack Code Tool)
//! \param address is the EtherCAT slave controller offset address which
//!        specifies the offset within the ESC memory area in bytes.
//!        (Only valid addresses are used depending on ESC 8 bit, 16 bit, or
//!         32 bit access specified in ecat_def.h or the Slave Stack Code Tool)
//! \param len is the access size in bytes
//!
//! This function is used to access the ESC registers and the DPRAM area with
//! interrupts disabled. The function disables interrupts, reads the requested
//! number of bytes from the ESC address, copies the data into the data buffer
//! specified, and re-enables interrupts.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_readBlock(ESCMEM_ADDR *pData, uint16_t address,
                          uint16_t len);

//*****************************************************************************
//
//! Reads two 16-bit words from ESC Memory
//!
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 32-bit aligned address boundary.
//!
//! This function reads two 16-bit words from the specified ESC address.
//!
//! \return Returns two 16-bit words
//
//*****************************************************************************
extern uint32_t ESC_readDWordISR(uint16_t address);

//*****************************************************************************
//
//! Reads two 16-bit words from ESC Memory with interrupts disabled
//!
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 32-bit aligned address boundary.
//!
//! This function disables interrupts, then reads two 16-bit words from the
//! specified ESC address, and re-enables interrupts.
//!
//! \return Returns two 16-bit words
//
//*****************************************************************************
extern uint32_t ESC_readDWord(uint16_t address);

//*****************************************************************************
//
//! Reads one 16-bit word from ESC Memory
//!
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 16-bit aligned address boundary.
//!
//! This function reads one 16-bit word from the specified ESC address..
//!
//! \return Returns 16-bit word value
//
//*****************************************************************************
extern uint16_t ESC_readWordISR(uint16_t address);

//*****************************************************************************
//
//! Reads one 16-bit word from ESC Memory with interrupts disabled
//!
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 16-bit aligned address boundary.
//!
//! This function disables interrupts, reads one 16-bit word from the specified
//! ESC address, and re-enables interrupts.
//!
//! \return Returns 16-bit word value
//
//*****************************************************************************
extern uint16_t ESC_readWord(uint16_t address);

//*****************************************************************************
//
//! Writes the Local Buffer Data into the ESC Memory
//!
//! \param pData is the pointer to the local source buffer.
//!        (Type of pointer depends on the host controller architecture,
//!         detailed in ecat_def.h or the Slave Stack Code Tool)
//! \param address is the EtherCAT slave controller offset address which
//!        specifies the offset within the ESC memory area in bytes.
//!        (Only valid addresses are used depending on ESC 8 bit, 16 bit, or
//!         32 bit access specified in ecat_def.h or the Slave Stack Code Tool)
//! \param len is the access size in bytes
//!
//! This function writes the requested number of bytes from the data buffer and
//! into the specified ESC addresses.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_writeBlockISR(ESCMEM_ADDR *pData, uint16_t address,
                              uint16_t len);

//*****************************************************************************
//
//! Writes the Local Buffer Data into the ESC Memory with interrupts disabled
//!
//! \param pData is the pointer to the local source buffer.
//!        (Type of pointer depends on the host controller architecture,
//!         detailed in ecat_def.h or the Slave Stack Code Tool)
//! \param address is the EtherCAT slave controller offset address which
//!        specifies the offset within the ESC memory area in bytes.
//!        (Only valid addresses are used depending on ESC 8 bit, 16 bit, or
//!         32 bit access specified in ecat_def.h or the Slave Stack Code Tool)
//! \param len is the access size in bytes
//!
//! This function disables interrupts, writes the requested number of bytes
//! from the data buffer into the specified ESC addresses, and re-enables
//! interrupts.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_writeBlock(ESCMEM_ADDR *pData, uint16_t address,
                           uint16_t len);

//*****************************************************************************
//
//! Writes two 16-bit words into ESC Memory
//!
//! \param dWordValue is the local 32-bit variable which contains the value
//!        that needs to be written.
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 32-bit aligned address boundary.
//!
//! This function writes two 16-bit words from \e DWordValue to the ESC
//! address.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_writeDWordISR(uint32_t dWordValue, uint16_t address);

//*****************************************************************************
//
//! Writes two 16-bit words into ESC Memory with interrupts disabled
//!
//! \param dWordValue is the local 32-bit variable which contains the value
//!        that needs to be written.
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 32-bit aligned address boundary.
//!
//! This function disables interrupts, writes two 16-bit words from
//! \e DWordValue to the ESC address, and re-enables interrupts.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_writeDWord(uint32_t dWordValue, uint16_t address);

//*****************************************************************************
//
//! Writes one 16-bit word into ESC Memory
//!
//! \param wordValue is the local 16-bit variable which contains the value to
//!        be written.
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 16-bit aligned address boundary.
//!
//! This function writes one 16-bit word from \e WordValue into the specified
//! ESC address.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_writeWordISR(uint16_t wordValue, uint16_t address);

//*****************************************************************************
//
//! Writes one 16-bit word into ESC Memory with interrupts disabled
//!
//! \param wordValue is the local 16-bit variable which contains the value to
//!        be written.
//! \param address is the EtherCAT slave controller offset address in bytes.
//!        This must be a valid 16-bit aligned address boundary.
//!
//! This function disables interrupts, writes one 16-bit word from \e WordValue
//! into the specified ESC address, and re-enables interrupts.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_writeWord(uint16_t wordValue, uint16_t address);

//*****************************************************************************
//
//! Updates the EtherCAT Run and Error LEDs
//!
//! \param runLed is the EtherCAT run LED state
//! \param errLed is the EtherCAT error LED state
//!
//! This function updates the EtherCAT run and error LEDS (or EtherCAT status
//! LED).
//!
//! \note This is configured to use the LED GPIOs for the controlCARD.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_setLed(uint16_t runLed, uint16_t errLed);

//*****************************************************************************
//
//! Checks if EEPROM was Loaded
//!
//! This function checks if the EEPROM load happened properly or not. The
//! function reads the EEPROM LOADED register bit in the DL register as no
//! proper EEPROM loaded IO signal is available. Recommended to be called by
//! applications during start up and after an EEPROM reload happens.
//!
//! \note ESC RAM access via PDI is blocked until EEPROM happens correctly.
//!
//! \return Returns \b ESC_EEPROM_SUCCESS if EEPROM loaded successfully,
//! \b ESC_EEPROM_NOT_LOADED if EEPROM not loaded as per the ESC DL register
//! status, and \b ESC_EEPROM_LOAD_ERROR if EEPROM ESC control status register
//! indicates that EEPROM is not loaded and device information not available.
//
//*****************************************************************************
extern uint16_t ESC_loadedCheckEEPROM(void);

//*****************************************************************************
//
//! Reset the ESC
//!
//! This function resets the ESC peripheral.
//!
//! \return None.
//
//*****************************************************************************
extern void ESC_resetESC(void);

//*****************************************************************************
//
//! Hold ESC in Reset
//!
//! This function holds the ESC peripheral in reset.
//!
//! \return None.
//
//*****************************************************************************
extern void ESC_holdESCInReset(void);

//*****************************************************************************
//
//! Release ESC from Reset
//!
//! This function de-activates the ESC peripheral reset signal and brings ESC
//! out of reset.
//!
//! \return None.
//
//*****************************************************************************
extern void ESC_releaseESCReset(void);

//*****************************************************************************
//
//! Initializes the Device for EtherCAT
//!
//! This function initializes the host controller, interrupts, SYNC signals,
//! PDI, and other necessary peripherals.
//!
//! \return Returns \b ESC_HW_INIT_SUCCESS if initialization was successful and
//! \b ESC_HW_INIT_FAIL if an error occurred during initialization
//
//*****************************************************************************
extern uint16_t ESC_initHW(void);

//*****************************************************************************
//
//! Releases the Device Resources
//!
//! This function releases the allocated device resources.
//!
//! \note Implementation of this function is left to the end user and
//! currently performs no action.
//!
//! \return None
//
//*****************************************************************************
extern uint16_t ESC_releaseHW(void);

//*****************************************************************************
//
//! Initializes GPIOs for EtherCAT
//!
//! This function initializes gpios for EtherCAT slave based on CPU1.
//!
//! \return None
//
//*****************************************************************************
extern void ESC_initGPIO(void);

//*****************************************************************************
//
//! Application Layer Handler
//!
//! This function is the interrupt handler for EtherCAT application/PDI
//! interrupts.
//!
//! \return None
//
//*****************************************************************************
__interrupt void ESC_applicationLayerHandler(void);

//*****************************************************************************
//
//! Application Sync 0 Handler
//!
//! This function is the interrupt handler for EtherCAT SYNC0 interrupts.
//!
//! \return None
//
//*****************************************************************************
__interrupt void ESC_applicationSync0Handler(void);

//*****************************************************************************
//
//! Application Sync 1 Handler
//!
//! This function is the interrupt handler for EtherCAT SYNC1 interrupts.
//!
//! \return None
//
//*****************************************************************************
__interrupt void ESC_applicationSync1Handler(void);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  ETHERCAT_SLAVE_CPU1_HAL_H

//
// End of File
//


#endif /* ETHERCAT_F28388X_HAL_ETHERCAT_SLAVE_CPU1_HAL_H_ */
