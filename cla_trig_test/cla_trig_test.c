//
// Included Files
//
#include "driverlib.h"
#include "device.h"
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

#pragma DATA_SECTION(calcs,"Cla1DataRam")
m_elem calcs[N];

m_elem E[N];
m_elem f_mse;
m_elem sum_sq_error;

#pragma DATA_SECTION(kk,"Cla1ToCpuMsgRAM");
uint32_t kk=0;

#pragma DATA_SECTION(testValues,"Cla1DataRam")
m_elem testValues[N] = {
-3.141593, -3.092119, -3.042645, -2.993171, -2.943697,
-2.894223, -2.844749, -2.795275, -2.745801, -2.696327,
-2.646854, -2.597380, -2.547906, -2.498432, -2.448958,
-2.399484, -2.350010, -2.300536, -2.251062, -2.201589,
-2.152115, -2.102641, -2.053167, -2.003693, -1.954219,
-1.904745, -1.855271, -1.805797, -1.756323, -1.706850,
-1.657376, -1.607902, -1.558428, -1.508954, -1.459480,
-1.410006, -1.360532, -1.311058, -1.261584, -1.212111,
-1.162637, -1.113163, -1.063689, -1.014215, -0.9647411,
-0.9152672, -0.8657932, -0.8163193, -0.7668455, -0.7173715,
-0.6678976, -0.6184238, -0.5689499, -0.5194759, -0.4700021,
-0.4205281, -0.3710543, -0.3215804, -0.2721064, -0.2226326,
-0.1731586, -0.1236847, -0.07421085, -0.02473695, 0.02473695,
0.07421085, 0.1236847, 0.1731586, 0.2226326, 0.2721064,
0.3215804, 0.3710543, 0.4205281, 0.4700021, 0.5194759,
0.5689499, 0.6184238, 0.6678976, 0.7173715, 0.7668455,
0.8163193, 0.8657932, 0.9152672, 0.9647411, 1.014215,
1.063689, 1.113163, 1.162637, 1.212111, 1.261584,
1.311058, 1.360532, 1.410006, 1.459480, 1.508954,
1.558428, 1.607902, 1.657376, 1.706850, 1.756323,
1.805797, 1.855271, 1.904745, 1.954219, 2.003693,
2.053167, 2.102641, 2.152115, 2.201589, 2.251062,
2.300536, 2.350010, 2.399484, 2.448958, 2.498432,
2.547906, 2.597380, 2.646854, 2.696327, 2.745801,
2.795275, 2.844749, 2.894223, 2.943697, 2.993171,
3.042645, 3.092119, 3.141593
};

m_elem resExpected[N] =
{-1.00000000000006  ,-1.00122507055861  ,-1.00491536902796  ,-1.01111650670700,
-1.01990603997554   ,-1.03139586839701  ,-1.04573578479514  ,-1.06311839170353,
-1.08378569419477   ,-1.10803780713586  ,-1.13624377865596  ,-1.16885897814597,
-1.20644153898509   ,-1.24968097713774  ,-1.29943322521702  ,-1.35676911673759,
-1.42304150661355   ,-1.49997984729407  ,-1.58982617559520  ,-1.69553290370739,
-1.82107407824073   ,-1.97190400698113  ,-2.15572690462520  ,-2.38377871069164,
-2.67310488494377   ,-3.05086303201861  ,-3.56311535827244  ,-4.29472756516350,
-5.42110627191340   ,-7.37276511703804  ,-11.5644977205712  ,-26.9562420594643,
80.8537414119434    ,16.1804664961914   ,9.00198775078587   ,6.24615904351116,
4.79114414871132    ,3.89366153778294   ,3.28613982777242   ,2.84864956189139,
2.51939598598983    ,2.26333339901000   ,2.05909332920707   ,1.89291187567534,
1.75552648522387    ,1.64047704949999   ,1.54312364513756   ,1.46005073041330,
1.38869012747577    ,1.32707604126808   ,1.27368173391114   ,1.22730517452535,
1.18698986208203    ,1.15196825680743   ,1.12162027291918   ,1.09544206038732,
1.07302403204949    ,1.05403278587729   ,1.03819852599475   ,1.02530498122735,
1.01518156111521    ,1.00769801310999   ,1.00275995802147   ,1.00030603637583,
1.00030603637583    ,1.00275995802147   ,1.00769801310999   ,1.01518156111521,
1.02530498122735    ,1.03819852599475   ,1.05403278587729   ,1.07302403204949,
1.09544206038732    ,1.12162027291918   ,1.15196825680743   ,1.18698986208203,
1.22730517452535    ,1.27368173391114   ,1.32707604126808   ,1.38869012747577,
1.46005073041330    ,1.54312364513756   ,1.64047704949999   ,1.75552648522387,
1.89291187567534    ,2.05909332920707   ,2.26333339901000   ,2.51939598598983,
2.84864956189139    ,3.28613982777242   ,3.89366153778294   ,4.79114414871132,
6.24615904351116    ,9.00198775078587   ,16.1804664961914   ,80.8537414119434,
-26.9562420594643   ,-11.5644977205712  ,-7.37276511703804  ,-5.42110627191340,
-4.29472756516350   ,-3.56311535827244  ,-3.05086303201861  ,-2.67310488494377,
-2.38377871069164   ,-2.15572690462520  ,-1.97190400698113  ,-1.82107407824073,
-1.69553290370739   ,-1.58982617559520  ,-1.49997984729407  ,-1.42304150661355,
-1.35676911673759   ,-1.29943322521702  ,-1.24968097713774  ,-1.20644153898509,
-1.16885897814597   ,-1.13624377865596  ,-1.10803780713586  ,-1.08378569419477,
-1.06311839170353   ,-1.04573578479514  ,-1.03139586839701  ,-1.01990603997554,
-1.01111650670700   ,-1.00491536902796  ,-1.00122507055861  ,-1.00000000000006
};

//
// Function Prototypes
//
void test_run(void);
void CLA_runTest(void);
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

    for(;;)
    {
        CLA_runTest();
        f_mse = TaskPerformance(resExpected,calcs,E);
    }
}

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
}


//
// CLA_runTest - Execute CLA task tests for specified vectors
//
void CLA_runTest(void)
{
    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_1);
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
    asm(" ESTOP0");
}

//
// cla1Isr3 - CLA1 ISR 3
//
__interrupt void cla1Isr3 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr4 - CLA1 ISR 4
//
__interrupt void cla1Isr4 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr5 - CLA1 ISR 5
//
__interrupt void cla1Isr5 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr6 - CLA1 ISR 6
//
__interrupt void cla1Isr6 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr7 - CLA1 ISR 7
//
__interrupt void cla1Isr7 ()
{
    asm(" ESTOP0");
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
