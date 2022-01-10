/*
 * init_Sci.h
 *
 *  Created on: 2 ??? 2021
 *      Author: Lupus
 */

#ifndef HAL_SCI_INIT_H_
#define HAL_SCI_INIT_H_

#include "driverlib.h"
#include "device.h"
#include "math.h"
#include "stdlib.h"

typedef struct{
    char* narray;
    int size;
}int_st;
/*
 * type_flag:"
 * 0: int,
 * 1: uint16_t
 */
int_st litoa(int value, int base);
void SCI_init(void);


#endif /* HAL_SCI_INIT_H_ */
