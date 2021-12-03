// Included Files
//
#include "device.h"
#include "SCI_init.h"

//
// Defines
//
#define ESCSS_LOOP_TIMEOUT       0x300U
#define ALLOCATE_TO_CM           0x1U
#define ESC_USE_INT_PHY_CLK      0x1U

#define BOOT_KEY                 0x5A000000UL
#define CM_BOOT_FREQ_125MHZ      0x7D00U
#define BOOTMODE_BOOT_TO_WAIT    0x0U
#define BOOTMODE_BOOT_TO_RAM     0x5U
#define BOOTMODE_BOOT_TO_FLASH   0x3U

#define CCARD_LED_1_GPIO         31U
#define CCARD_LED_2_GPIO         34U
#define CCARD_ECAT_RUN_LED_GPIO  146U
#define CCARD_ECAT_ERR_LED_GPIO  145U

//
// Function Prototypes
//
void setupESCGPIOs(void);
void configureAndReleaseCMToWait(void);
void releaseCMToApplication(void);


char* msg;
int i;
Struct lot;


//
// Main
//
void main(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

#ifdef _FLASH
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: Flash_initModule();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif

    //
    // Set up device clock
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Make sure the LSPCLK divider is set to the default (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

    //
    // Turn on all peripherals and initialize GPIOs
    //
    Device_enableAllPeripherals();
    Device_initGPIO();

    //
    // Setup AUX Clock for ECAT and CM
    // Configured to 500MHz raw ((25 * 20 IMULT) /1)
    //
    SysCtl_setAuxClock(SYSCTL_AUXPLL_ENABLE | SYSCTL_AUXPLL_OSCSRC_XTAL |
                       SYSCTL_AUXPLL_IMULT(20) | SYSCTL_AUXPLL_FMULT_0 |
                       SYSCTL_AUXPLL_DIV_1);

    //
    // Setup GPIOs for EtherCAT
    //
    setupESCGPIOs();
    SCI_init();

    //
    // Allocate Ethercat to CM
    //
    SysCtl_allocateSharedPeripheral(SYSCTL_PALLOCATE_ETHERCAT,
                                    ALLOCATE_TO_CM);

    //
    // Setup CM clocks and release from reset to Wait Boot Mode
    //
    configureAndReleaseCMToWait();

    //
    // Setup EtherCAT Clocks
    //
    // Aux = 500MHz and use /5 to get 100MHz for ECAT IP
    // (There is a built in /4 to get 25MHz for PHY when using
    //  internal clocking for PHY)
    //
    SysCtl_setECatClk(SYSCTL_ECATCLKOUT_DIV_5, SYSCTL_SOURCE_AUXPLL,
                      ESC_USE_INT_PHY_CLK);

    //
    // Set boot mode to RAM or Flash and release from Wait Boot Mode
    //
    releaseCMToApplication();



    //
    // Wait Forever
    //
    i=8000;
    char* buffer;
    while(1)
    {
        lot=litoa(i,buffer,10);
        //msg = "\r\nRunning Application!\0";
        //SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 22+lot.size);
        //msg = lot.narray;
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)buffer, lot.size);
        //SysCtl_delay(10000000);
        i++;
    }
}

//
// setupESCGPIOs - Setup EtherCAT GPIOs
//
//                 Note: These are configured for the F2838x controlCARD. For
//                 more pin mapping details refer to the GPIO chapter of the
//                 F2838x Technical Reference Manual.
//
void
setupESCGPIOs(void)
{
    //
    // PHY CLK
    //
    GPIO_setPinConfig(GPIO_154_ESC_PHY_CLK);

    //
    // PHY Reset
    //
    GPIO_setPinConfig(GPIO_155_ESC_PHY_RESETN);

    //
    // I2C for EEPROM
    //
    GPIO_setPinConfig(GPIO_150_ESC_I2C_SDA);
    GPIO_setQualificationMode(150, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(150, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_151_ESC_I2C_SCL);
    GPIO_setQualificationMode(151, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(151, GPIO_PIN_TYPE_PULLUP);

    //
    // P0 TX and RX DATA
    //
    GPIO_setPinConfig(GPIO_158_ESC_TX0_DATA0);
    GPIO_setQualificationMode(158, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_159_ESC_TX0_DATA1);
    GPIO_setQualificationMode(159, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_160_ESC_TX0_DATA2);
    GPIO_setQualificationMode(160, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_161_ESC_TX0_DATA3);
    GPIO_setQualificationMode(161, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_165_ESC_RX0_DATA0);
    GPIO_setQualificationMode(165, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_166_ESC_RX0_DATA1);
    GPIO_setQualificationMode(166, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_167_ESC_RX0_DATA2);
    GPIO_setQualificationMode(167, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_168_ESC_RX0_DATA3);
    GPIO_setQualificationMode(168, GPIO_QUAL_ASYNC);

    //
    // P0 TX Enable, RX DV, RX ERR
    //
    GPIO_setPinConfig(GPIO_156_ESC_TX0_ENA);
    GPIO_setQualificationMode(156, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_162_ESC_RX0_DV);
    GPIO_setQualificationMode(162, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_164_ESC_RX0_ERR);
    GPIO_setPadConfig(164, GPIO_PIN_TYPE_STD);

    //
    // P0 TX and RX Clk
    //
    GPIO_setPinConfig(GPIO_157_ESC_TX0_CLK);
    GPIO_setQualificationMode(157, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_163_ESC_RX0_CLK);
    GPIO_setQualificationMode(163, GPIO_QUAL_ASYNC);

    //
    // P0 Linkstatus and Link Active LED
    //
    GPIO_setPinConfig(GPIO_148_ESC_PHY0_LINKSTATUS);
    GPIO_setPadConfig(148, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_143_ESC_LED_LINK0_ACTIVE);
    GPIO_setQualificationMode(143, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(143, GPIO_PIN_TYPE_INVERT);

    //
    // P0+P1 MDIO CLK and Data
    //
    GPIO_setPinConfig(GPIO_152_ESC_MDIO_CLK);
    GPIO_setPinConfig(GPIO_153_ESC_MDIO_DATA);

    //
    // P1 TX and RX DATA
    //
    GPIO_setPinConfig(GPIO_131_ESC_TX1_DATA0);
    GPIO_setQualificationMode(131, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_132_ESC_TX1_DATA1);
    GPIO_setQualificationMode(132, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_134_ESC_TX1_DATA2);
    GPIO_setQualificationMode(134, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_135_ESC_TX1_DATA3);
    GPIO_setQualificationMode(135, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_139_ESC_RX1_DATA0);
    GPIO_setQualificationMode(139, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_140_ESC_RX1_DATA1);
    GPIO_setQualificationMode(140, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_141_ESC_RX1_DATA2);
    GPIO_setQualificationMode(141, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_142_ESC_RX1_DATA3);
    GPIO_setQualificationMode(142, GPIO_QUAL_ASYNC);

    //
    // P1 TX Enable, RX DV, RX ERR
    //
    GPIO_setPinConfig(GPIO_129_ESC_TX1_ENA);
    GPIO_setQualificationMode(129, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_136_ESC_RX1_DV);
    GPIO_setQualificationMode(136, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_138_ESC_RX1_ERR);
    GPIO_setPadConfig(138, GPIO_PIN_TYPE_STD);

    //
    // P1 TX and RX Clk
    //
    GPIO_setPinConfig(GPIO_130_ESC_TX1_CLK);
    GPIO_setQualificationMode(130, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_137_ESC_RX1_CLK);
    GPIO_setQualificationMode(137, GPIO_QUAL_ASYNC);

    //
    // P1 Linkstatus and Link Active LED
    //
    GPIO_setPinConfig(GPIO_149_ESC_PHY1_LINKSTATUS);
    GPIO_setPadConfig(149, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_144_ESC_LED_LINK1_ACTIVE);
    GPIO_setQualificationMode(144, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(144, GPIO_PIN_TYPE_INVERT);

    //
    // Sync and Latch
    //
    // Note these GPIOs aren't required for EtherCAT
    // operation and are configured here for demonstration,
    // analysis, and debug purposes
    //
    GPIO_setPinConfig(GPIO_125_ESC_LATCH0);
    GPIO_setPinConfig(GPIO_126_ESC_LATCH1);
    GPIO_setPinConfig(GPIO_127_ESC_SYNC0);
    GPIO_setPinConfig(GPIO_128_ESC_SYNC1);
    GPIO_setDirectionMode(127, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(128, GPIO_DIR_MODE_OUT);

    //
    // Allocate controlCARD LEDS to CM
    //
    GPIO_setDirectionMode(CCARD_ECAT_RUN_LED_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(CCARD_ECAT_ERR_LED_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(CCARD_ECAT_RUN_LED_GPIO, GPIO_CORE_CM);
    GPIO_setMasterCore(CCARD_ECAT_ERR_LED_GPIO, GPIO_CORE_CM);
    GPIO_setDirectionMode(CCARD_LED_1_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(CCARD_LED_2_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(CCARD_LED_1_GPIO, GPIO_CORE_CM);
    GPIO_setMasterCore(CCARD_LED_2_GPIO, GPIO_CORE_CM);
}

//
// configureAndReleaseCMToWait - Configure CM clocks, set boot mode to wait,
//                               and release from reset
//
void
configureAndReleaseCMToWait(void)
{
    //
    // Configuring CM to run at 125MHz (AUX Raw = 500MHz)
    //
    SysCtl_setCMClk(SYSCTL_CMCLKOUT_DIV_4, SYSCTL_SOURCE_AUXPLL);

    //
    // Configure CM boot up configurations and boot mode as wait boot
    //
    IPC_setBootMode(IPC_CPU1_L_CM_R,
                    (BOOT_KEY | CM_BOOT_FREQ_125MHZ | BOOTMODE_BOOT_TO_WAIT));

    //
    // Set IPC flag (required for boot)
    //
    IPC_setFlagLtoR(IPC_CPU1_L_CM_R, IPC_FLAG0);

    //
    // Release CM from reset
    //
    SysCtl_controlCMReset(SYSCTL_CORE_DEACTIVE);
}

//
// releaseCMToApplication - Set CM boot mode to Flash or RAM, then release from
//                          wait boot mode
//
void 
releaseCMToApplication(void)
{
    //
    // Configure CM boot up configurations and boot mode
    //
#ifdef _FLASH
    IPC_setBootMode(IPC_CPU1_L_CM_R,
                    (BOOT_KEY | CM_BOOT_FREQ_125MHZ | BOOTMODE_BOOT_TO_FLASH));
#else
    IPC_setBootMode(IPC_CPU1_L_CM_R,
                    (BOOT_KEY | CM_BOOT_FREQ_125MHZ | BOOTMODE_BOOT_TO_RAM));
#endif

    //
    // Set IPC flag (required for leaving wait boot mode)
    //
    IPC_setFlagLtoR(IPC_CPU1_L_CM_R, IPC_FLAG0);    
}

//
// End of file
//
