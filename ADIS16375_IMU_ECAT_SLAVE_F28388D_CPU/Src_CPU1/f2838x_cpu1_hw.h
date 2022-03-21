//###########################################################################
//
// FILE:   f2838x_cpu1_hw.h
//
// TITLE:  F2838x CPU1 EtherCAT Hardware API Mapping
//
// This file maps the F2838x CPU1 HAL APIs to the EtherCAT stack API naming.
//
//###########################################################################
// $TI Release: F2838x EtherCAT Software v2.01.00.00 $
// $Release Date: August 31 2020 $
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2838X_CPU1_HW_H
#define F2838X_CPU1_HW_H

//
// Included Files
//
#include <stdint.h>
#include <string.h>
#include "esc.h"


//
// Defines - Mapping HAL APIs to Stack APIS
//

//
// Interrupt APIs
//
#define DISABLE_ESC_INT()                          __asm(" setc INTM")
#define ENABLE_ESC_INT()                           __asm(" clrc INTM")

//
// Timer APIs
//
#define ECAT_TIMER_INC_P_MS                        ESC_timerIncPerMilliSec()
#define HW_GetTimer()                              ESC_getTimer()
#define HW_ClearTimer()                            ESC_clearTimer()

//
// System APIs
//
#define HW_Init()                                  ESC_initHW()
#define HW_Release()                               ESC_releaseHW()
#define HW_SetLed(RunLed, ErrLed)                  ESC_setLed(RunLed, ErrLed)

//
// Read and Write APIs
//
#define HW_EscRead(pData, Address, Len)            ESC_readBlock(pData, Address, Len)
#define HW_EscReadIsr(pData, Address, Len)         ESC_readBlockISR(pData, Address, Len)
#define HW_EscReadDWord(DWordValue, Address)       ((DWordValue) = ESC_readDWord(Address))
#define HW_EscReadDWordIsr(DWordValue, Address)    ((DWordValue) = ESC_readDWordISR(Address))
#define HW_EscReadWord(WordValue, Address)         ((WordValue) = ESC_readWord(Address))
#define HW_EscReadWordIsr(WordValue, Address)      ((WordValue) = ESC_readWordISR(Address))
#define HW_EscReadMbxMem(pData, Address, Len)      ESC_readBlock(pData, Address, Len)

#define HW_EscWrite(pData, Address, Len)           ESC_writeBlock(pData, Address, Len)
#define HW_EscWriteIsr(pData, Address, Len)        ESC_writeBlockISR(pData, Address, Len)
#define HW_EscWriteDWord(DWordValue, Address)      ESC_writeDWord(DWordValue, Address)
#define HW_EscWriteDWordIsr(DWordValue, Address)   ESC_writeDWordISR(DWordValue, Address)
#define HW_EscWriteWord(WordValue, Address)        ESC_writeWord(WordValue, Address)
#define HW_EscWriteWordIsr(WordValue, Address)     ESC_writeWordISR(WordValue, Address)
#define HW_EscWriteMbxMem(pData, Address, Len)     ESC_writeBlock(pData, Address, Len)

//
// Application Layer Event APIs
//
#define HW_GetALEventRegister()                    ESC_readWord(ESC_AL_EVENT_OFFSET)
#define HW_GetALEventRegister_Isr()                ESC_readWordISR(ESC_AL_EVENT_OFFSET)


//
// Function Prototypes
//
extern uint16_t ESC_initHW(void);
extern void ESC_releaseHW(void);
extern void ESC_setLed(uint16_t RunLed, uint16_t ErrLed);

extern uint32_t ESC_getTimer(void);
extern void ESC_clearTimer(void);
extern uint32_t ESC_timerIncPerMilliSec(void);

extern void ESC_readBlock(uint16_t *pData, uint16_t Address, uint16_t Len);
extern void ESC_readBlockISR(uint16_t *pData, uint16_t Address, uint16_t Len);
extern uint32_t ESC_readDWord(uint16_t Address);
extern uint32_t ESC_readDWordISR(uint16_t Address);
extern uint16_t ESC_readWord(uint16_t Address);
extern uint16_t ESC_readWordISR(uint16_t Address);

extern void ESC_writeBlock(uint16_t *pData, uint16_t Address, uint16_t Len);
extern void ESC_writeBlockISR(uint16_t *pData, uint16_t Address, uint16_t Len);
extern void ESC_writeDWord(uint32_t DWordValue, uint16_t Address);
extern void ESC_writeDWordISR(uint32_t DWordValue, uint16_t Address);
extern void ESC_writeWord(uint16_t WordValue, uint16_t Address);
extern void ESC_writeWordISR(uint16_t WordValue, uint16_t Address);

#endif // F2838X_CPU1_HW_H

//
// End of File
//
