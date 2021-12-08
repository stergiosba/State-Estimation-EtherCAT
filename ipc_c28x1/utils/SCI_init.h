/*
 * init_Sci.h
 *
 *  Created on: 2 December 2021
 *      Author: Stergios Bachoumas
 */

#ifndef HAL_SCI_INIT_H_
#define HAL_SCI_INIT_H_

#include "device.h"
#include "math.h"
#include "stdlib.h"

struct litoa_return{
    char* narray;
    int size;
};

typedef struct litoa_return Struct;

Struct litoa(int value, char* buffer, int base);
void SCI_init(void);


#endif /* HAL_SCI_INIT_H_ */
