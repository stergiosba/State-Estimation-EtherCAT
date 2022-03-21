//###########################################################################
//
// FILE:   f2838x_cpu1_system.c
//
// TITLE:  F2838x CPU1 EtherCAT System APIs
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
#include "f2838x_cpu1_system.h"

//
// F2838XCPU1_strcpy - String copy wrapper for compatibility with EtherCAT stack
//                     to store as 8-bit values.
//
void F2838XCPU1_strcpy(void * __restrict dest, const void * __restrict src,
                       size_t n)
{
    unsigned int srcIndex = 0U;
    unsigned int destIndex = 0U;
    unsigned int *intDest, *intSrc;

    //
    // Re-cast pointers as unsigned int
    //
    intDest = (unsigned int *)dest;
    intSrc = (unsigned int *)src;

    //
    // Combine 8-bit ASCII values into single 16-bit destination for requested
    // length of string
    //
    for(srcIndex = 0U; srcIndex < n; srcIndex += 2U)
    {
        intDest[destIndex] =  (intSrc[srcIndex + 1U] << 8U) | intSrc[srcIndex];
        destIndex = destIndex + 1U;
    }
}

//
// F2838XCPU1_memcpy - Memory copy wrapper for compatibility with EtherCAT stack
//                     calls to "memcpy" to adjust for input size in bytes
//
void F2838XCPU1_memcpy(void * __restrict destination, const void * __restrict source,
                       size_t length)
{
    //
    // Convert length in bytes to words
    //
    length = length >> 1U;

    //
    // Call standard memcpy
    //
    memcpy(destination, source, length);
}

//
// F2838XCPU1_memset - Memory set wrapper for compatibility with EtherCAT stack
//                     calls to "memset" to adjust for input size in bytes
//
void F2838XCPU1_memset(void *mem, int ch, size_t length)
{
    //
    // Convert length in bytes to words
    //
    length = length >> 1U;

    //
    // Call standard memset
    //
    memset(mem, ch, length);
}

//
// F2838XCPU1_memcpy - String copy wrapper for compatibility with EtherCAT stack
//                     calls to "memcmp" to adjust for input size in bytes
//
int F2838XCPU1_memcmp(const void *cs, const void *ct, size_t n)
{
    //
    // Adjust size in bytes to words
    //
    n = n >> 1U;

    //
    // Call standard memcmp from string.h
    //    
    return(memcmp(cs, ct, n));
}

//
// End of File
//
