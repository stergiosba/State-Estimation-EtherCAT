//###########################################################################
//
// FILE:   f2838x_cpu1_system.h
//
// TITLE:  F2838x CPU1 EtherCAT System APIs
//
// This file contains the function prototypes for any device system APIs that
// require modification for compatibility with EtherCAT stack usage.
//
//###########################################################################
// $TI Release: F2838x EtherCAT Software v2.01.00.00 $
// $Release Date: August 31 2020 $
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2838X_CPU1_SYSTEM_H
#define F2838X_CPU1_SYSTEM_H

//
// Included Files
//
#include <string.h>

//
// Function Prototypes
//
void F2838XCPU1_strcpy(void * __restrict dest, const void * __restrict src,
                       size_t n);
void F2838XCPU1_memcpy(void * __restrict destination,
                       const void * __restrict source,
                       size_t length);
void F2838XCPU1_memset(void *mem, int ch, size_t length);                       
int F2838XCPU1_memcmp(const void *cs, const void *ct, size_t n);


#endif // F2838X_CPU1_SYSTEM_H

//
// End of File
//
