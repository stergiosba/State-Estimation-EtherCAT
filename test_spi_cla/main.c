#include "SPI_init.h"
#include "cla_shared.h"
#include "CLA_init.h"
#include "ADIS16364.h"
#include <stdio.h>

uint16_t imu_check;

#pragma DATA_SECTION(ulCycleCount1,"Cla1ToCpuMsgRAM");
uint32_t ulCycleCount1;

#pragma DATA_SECTION(test,"CLADataLS0")
float test[11];

#pragma DATA_SECTION(SENS,"CLADataLS0")
float SENS;


void initEPWM1(void);

int main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    SPI_init();
    CLA_configClaMemory();
    CLA_initCpu1Cla1();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    initEPWM1();
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    EINT;
    ERTM;

    //imu_check=IMUCommsCheck();
    while(1)
    {
        //BurstRead();
        CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);

        //DEVICE_DELAY_US(20);
    }

}


void initEPWM1(void)
{
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBPRD = 0xFFFF;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;
    EPwm1Regs.TBCTR = 0;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
}
