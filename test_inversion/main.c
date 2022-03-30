#include <myCHOL1.h>
#include <myCHOL2.h>
#include <myCHOLMATLAB.h>
#include "SPI_init.h"
#include "SCI_init.h"
#include <stdio.h>

uint16_t check;
uint16_t sleep;

int main(void)
{
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    SPI_init();
    SCI_init();
    EINT;
    ERTM;

    //float A[N*N] = {4.0, -1.0, -1.0, -1.0, 4.0, -1.0, -1.0 ,-1.0 , 4.0};

    float A[N*N] =
    {
        1.7392, 0.7142, 1.8934, 1.4695, 1.5499, 0.7142, 0.5878, 0.7385, 0.5888, 0.6450, 1.8934, 0.7385, 2.1655, 1.6312, 1.6179, 1.4695, 0.5888, 1.6312, 1.5914, 1.5848, 1.5499, 0.6450, 1.6179, 1.5848, 1.9289
    };
    float L[N*N], invL[N*N], L2[N*N], invL2[N*N], L3[N*N], invL3[N*N];

    while(1)
    {
        CHOL3(A,L,invL);    // 7014 for 5x5
        CHOL2(A,L2,invL2);  // 8953  for 5x5
        CHOLMATLAB(A,L3,invL3);
    }
}




