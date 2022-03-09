//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "cla_ex1_asin_shared.h"
#include "setvalue.h"


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

m_elem TaskPerformance (m_elem correct[][N],m_elem z[][N],m_elem E[][N]);

#pragma DATA_SECTION(S,"Cla1DataRam")
m_elem S[M];
#pragma DATA_SECTION(Df,"Cla1DataRam")
m_elem Df[N][N];
#pragma DATA_SECTION(z,"Cla1DataRam")
m_elem z[N][N];
#pragma DATA_SECTION(Pxx,"CLADataLS3")
m_elem Pxx[M];


m_elem correct[N][N];
m_elem E[N][N];
m_elem f_mse;
m_elem sum_sq_error;

#pragma DATA_SECTION(kk,"Cla1ToCpuMsgRAM");
uint32_t kk=0;

//
//Task 2 (C) Variables
//

//
//Task 3 (C) Variables
//

//
//Task 4 (C) Variables
//

//
//Task 5 (C) Variables
//

//
//Task 6 (C) Variables
//

//
//Task 7 (C) Variables
//

//
//Task 8 (C) Variables
//

//
//Common (C) Variables
//The Exponential table
//

//
// Function Prototypes
//
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
    setvalues(S,Df,correct);

    for(;;)
    {
        CLA_runTest();
        //f_mse = TaskPerformance(correct,z,E);
    }
}

m_elem TaskPerformance (m_elem correct[][N], m_elem z[][N], m_elem E[][N])
{
    m_elem sum_sq_error;
    m_elem error;
    int i,j;
    sum_sq_error = 0;
    for(i=0; i < N; i++)
    {
        for(j=0; j < N; j++)
        {
            error = correct[i][j]-z[i][j];
            E[i][j] = fabs(error);
            sum_sq_error+=error*error;
        }
    }
    return (sum_sq_error/(N*N));
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
