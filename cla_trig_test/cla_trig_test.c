//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include <string.h>
#include "cla_ex1_asin_shared.h"


//
// Defines
//
#define WAITSTEP     asm(" RPT #255 || NOP")


//
// Globals
//

#pragma DATA_SECTION(ulCycleCount1,"Cla1ToCpuMsgRAM");
uint32_t ulCycleCount1;
#pragma DATA_SECTION(ulCycleCount2,"Cla1ToCpuMsgRAM");
uint32_t ulCycleCount2;
#pragma DATA_SECTION(ulCycleCount3,"Cla1ToCpuMsgRAM");
uint32_t ulCycleCount3;

//
//Task 1 (C) Variables
// NOTE: Do not initialize the Message RAM variables globally, they will be
// reset during the message ram initialization phase in the CLA memory
// configuration routine
//

m_elem TaskPerformance (m_elem correct[N],m_elem z[N],m_elem E[N]);

#pragma DATA_SECTION(test,"Cla1ToCpuMsgRAM");
CLA_FPTR test;

#pragma DATA_SECTION(state,"Cla1DataRam")
State state;

#pragma DATA_SECTION(Jfx,"Cla1DataRam")
m_elem Jfx[STATE_SIZE][STATE_SIZE];

#pragma DATA_SECTION(Pxx_,"Cla1DataRam")
m_elem Pxx_[STATE_SYM_SIZE] = {1000, 0, 0, 1000, 0, 1000};

#pragma DATA_SECTION(Pxx,"Cla1DataRam")
m_elem Pxx[STATE_SYM_SIZE];

#pragma DATA_SECTION(Q,"Cla1DataRam")
m_elem Q[STATE_SYM_SIZE] = {1, 0, 0, 1, 0, 1};

#pragma DATA_SECTION(A,"Cla1DataRam")
m_elem A[STATE_SIZE*STATE_SIZE]=
    {
    2.97013501161380    ,2.12379707429834   ,2.65849548626597   ,2.63308171419847   ,2.55618699404475   ,2.14341489986319   ,2.94004380460203   ,2.89141412960990   ,3.02093116909430   ,1.97206385121652,
    2.12379707429834    ,2.42660041768136   ,2.32707485597331   ,2.15674205908146   ,2.68050872561834   ,1.50473448114253   ,2.09400758035127   ,2.81223981183653   ,2.22367324914715   ,1.74850493422440,
    2.65849548626597    ,2.32707485597331   ,4.79263737703086   ,3.51422036457563   ,3.81069913151511   ,2.70755981370156   ,2.86605704889075   ,3.90560179115932   ,4.21673505079240   ,3.10148534529344,
    2.63308171419847    ,2.15674205908146   ,3.51422036457563   ,4.03653818651459   ,2.48608030949455   ,2.33492303215859   ,3.04014806677545   ,2.98986159444988   ,3.26082376721887   ,2.13127932963281,
    2.55618699404475    ,2.68050872561834   ,3.81069913151511   ,2.48608030949455   ,4.02692063738971   ,2.04018476091397   ,2.45444193991512   ,3.90960727881222   ,3.41523564336229   ,2.71028832238732,
    2.14341489986319    ,1.50473448114253   ,2.70755981370156   ,2.33492303215859   ,2.04018476091397   ,2.53843666393708   ,2.19827569167528   ,2.21194613628438   ,2.82092735614422   ,1.88783442415468,
    2.94004380460203    ,2.09400758035127   ,2.86605704889075   ,3.04014806677545   ,2.45444193991512   ,2.19827569167528   ,3.32209373249153   ,2.82563243861420   ,3.20932240916266   ,2.05681167031968,
    2.89141412960990    ,2.81223981183653   ,3.90560179115932   ,2.98986159444988   ,3.90960727881222   ,2.21194613628438   ,2.82563243861420   ,4.55799178727805   ,3.61696479400183   ,2.96378441141885,
    3.02093116909430    ,2.22367324914715   ,4.21673505079240   ,3.26082376721887   ,3.41523564336229   ,2.82092735614422   ,3.20932240916266   ,3.61696479400183   ,4.19242771204075   ,3.08155920340698,
    1.97206385121652    ,1.74850493422440   ,3.10148534529344   ,2.13127932963281   ,2.71028832238732   ,1.88783442415468   ,2.05681167031968   ,2.96378441141885   ,3.08155920340698   ,2.99156834290365
};

#pragma DATA_SECTION(invA,"Cla1DataRam")
m_elem invA[STATE_SIZE*STATE_SIZE];

#pragma DATA_SECTION(L,"Cla1DataRam")
m_elem L[STATE_SIZE*STATE_SIZE];

#pragma DATA_SECTION(invL,"Cla1DataRam")
m_elem invL[STATE_SIZE*STATE_SIZE];

m_elem E[N];
m_elem f_mse;
m_elem sum_sq_error;

#pragma DATA_SECTION(kk,"Cla1ToCpuMsgRAM");
uint32_t kk=0;


//
// Function Prototypes
//
void test_run(void);
void CLA_runTest(void);
void CLA_runTest2(void);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);
void initEPWM1(void);
__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    //Device_initGPIO(); //skipped for this example

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    initEPWM1();
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;


    //
    // Configure the CLA memory spaces first followed by
    // the CLA task vectors
    //
    CLA_configClaMemory();
    CLA_initCpu1Cla1();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Run the test
    //
    state = (State) {.p = 0.0f, .q = 1.0f, .r = 1.0f, .phi = -0.7173715, .th = -2.547906};
    for(;;)
    {
        //memcpy(&L[0], &A[0], (N*N) * sizeof(m_elem));
        CLA_runTest();
        volatile int stopper = 1;
        //memcpy(&invL[0], &L[0], (N*N) * sizeof(m_elem));
        //CLA_runTest2();
        //f_mse = TaskPerformance(resExpected,calcs,E);
    }
}
/*
m_elem TaskPerformance (m_elem correct[N],m_elem calcs[N],m_elem E[N])
{
    m_elem sum_sq_error;
    m_elem error;
    int i;
    sum_sq_error = 0;
    for(i=0; i < N; i++)
    {
        error = correct[i]-calcs[i];
        E[i] = fabs(error);
        sum_sq_error+=error*error;
    }
    return (sum_sq_error/N);
}*/


//
// CLA_runTest - Execute CLA task tests for specified vectors
//
void CLA_runTest(void)
{
    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);
}

void CLA_runTest2(void)
{
    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_2);
}

//
// CLA_configClaMemory - Configure CLA memory sections
//
void CLA_configClaMemory(void)
{
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    EALLOW;

#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCLA1TOCPU);
    while (!MemCfg_getInitStatus(MEMCFG_SECT_MSGCLA1TOCPU)){};

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCPUTOCLA1);
    while (!MemCfg_getInitStatus(MEMCFG_SECT_MSGCPUTOCLA1)){};

    //
    // Select LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS5 and then
    // set the space to be a program block
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5,MEMCFG_CLA_MEM_PROGRAM);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS6,MEMCFG_CLA_MEM_PROGRAM);

    //
    // Next configure LS0RAM and LS1RAM as data spaces for the CLA
    // First configure the CLA to be the master for LS0(1) and then
    // set the spaces to be code blocks
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);



    EDIS;
}

//
// CLA_initCpu1Cla1 - Initialize CLA1 task vectors and end-of-task interrupts
//
void CLA_initCpu1Cla1(void)
{
    //
    // Compute all CLA task vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
    EALLOW;

#pragma diag_suppress=770
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_1,(uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_2,(uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_3,(uint16_t)&Cla1Task3);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_4,(uint16_t)&Cla1Task4);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_5,(uint16_t)&Cla1Task5);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_6,(uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_7,(uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_8,(uint16_t)&Cla1Task8);
#pragma diag_warning=770

    //
    // Enable the IACK instruction to start a task on CLA in software
    // for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
    // subset of tasks) by writing to their respective bits in the
    // MIER register
    //
    CLA_enableIACK(CLA1_BASE);
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_ALL);

    //
    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks
    //
    Interrupt_register(INT_CLA1_1, &cla1Isr1);
    Interrupt_register(INT_CLA1_2, &cla1Isr2);
    Interrupt_register(INT_CLA1_3, &cla1Isr3);
    Interrupt_register(INT_CLA1_4, &cla1Isr4);
    Interrupt_register(INT_CLA1_5, &cla1Isr5);
    Interrupt_register(INT_CLA1_6, &cla1Isr6);
    Interrupt_register(INT_CLA1_7, &cla1Isr7);
    Interrupt_register(INT_CLA1_8, &cla1Isr8);

    //
    // Enable CLA interrupts at the group and subgroup levels
    //
    Interrupt_enable(INT_CLA1_1);
    Interrupt_enable(INT_CLA1_2);
    Interrupt_enable(INT_CLA1_3);
    Interrupt_enable(INT_CLA1_4);
    Interrupt_enable(INT_CLA1_5);
    Interrupt_enable(INT_CLA1_6);
    Interrupt_enable(INT_CLA1_7);
    Interrupt_enable(INT_CLA1_8);
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

//
// cla1Isr1 - CLA1 ISR 1
//

__interrupt void cla1Isr1 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

    //
    // Uncomment to halt debugger and stop here
    //
    // asm(" ESTOP0");
}

//
// cla1Isr2 - CLA1 ISR 2
//
__interrupt void cla1Isr2 ()
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //asm(" ESTOP0");
}

//
// cla1Isr3 - CLA1 ISR 3
//
__interrupt void cla1Isr3 ()
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //asm(" ESTOP0");
}

//
// cla1Isr4 - CLA1 ISR 4
//
__interrupt void cla1Isr4 ()
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //asm(" ESTOP0");
}

//
// cla1Isr5 - CLA1 ISR 5
//
__interrupt void cla1Isr5 ()
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //asm(" ESTOP0");
}

//
// cla1Isr6 - CLA1 ISR 6
//
__interrupt void cla1Isr6 ()
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //asm(" ESTOP0");
}

//
// cla1Isr7 - CLA1 ISR 7
//
__interrupt void cla1Isr7 ()
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //asm(" ESTOP0");
}

//
// cla1Isr8 - CLA1 ISR 8
//
__interrupt void cla1Isr8 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 8
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
    //
    // Uncomment to halt debugger and stop here
    //
//    asm(" ESTOP0");
}

//
// End of file
//
