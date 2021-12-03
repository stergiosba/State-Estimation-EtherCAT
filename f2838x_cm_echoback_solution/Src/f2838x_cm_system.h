//###########################################################################
//
// FILE:   f2838x_cm_system.h
//
// TITLE:  F2838x CM EtherCAT System APIs
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

#ifndef F2838X_CM_SYSTEM_H
#define F2838X_CM_SYSTEM_H

//
// Included Files
//
#include <string.h>

//
// Function Prototypes
//
void F2838XCM_strcpy(void * __restrict dest, const void * __restrict src,
                     size_t n);

#endif // F2838X_CM_SYSTEM_H

//
// End of File
//
