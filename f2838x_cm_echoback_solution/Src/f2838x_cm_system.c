//###########################################################################
//
// FILE:   f2838x_cm_system.c
//
// TITLE:  F2838x CM EtherCAT System APIs
//
// This file contains the source for any device system APIs that require
// modification for compatibility with EtherCAT stack usage.
//
//###########################################################################
// $TI Release: F2838x EtherCAT Software v2.01.00.00 $
// $Release Date: August 31 2020 $
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "f2838x_cm_system.h"

//
// F2838XCM_strcpy - String copy wrapper for compatibility with EtherCAT stack
//                   calls to "strncpy"
//
void F2838XCM_strcpy(void * __restrict dest, const void * __restrict src,
                     size_t n)
{
    //
    // Call standard strncpy from string.h
    //
    strncpy((char *)dest, (const char *)src, (size_t)n);
}

//
// End of File
//
