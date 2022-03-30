/*
 * ECAT_init.c
 *
 *  Created on: 8 December 2021
 *      Author: Stergios Bachoumas
 */

#include "ECAT_init.h"

void ECAT_init(void)
{
    //
    // Setup GPIOs for EtherCAT
    //
    setupESCGPIOs();

    //
    // Allocate Ethercat to CM

    SysCtl_allocateSharedPeripheral(SYSCTL_PALLOCATE_ETHERCAT,
                                        ALLOCATE_TO_CM);
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

    SysCtl_setECatClk(SYSCTL_ECATCLKOUT_DIV_5, SYSCTL_SOURCE_AUXPLL,
                          ESC_USE_INT_PHY_CLK);

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
// setupESCGPIOs - Setup EtherCAT GPIOs
//
//                 Note: These are configured for the F2838x controlCARD. For
//                 more pin mapping details refer to the GPIO chapter of the
//                 F2838x Technical Reference Manual.
//
void setupESCGPIOs(void)
{
    // Setup EtherCAT GPIOs
    // Note: These are configured for the F2838x controlCARD. For
    //       more pin mapping details refer to the GPIO chapter of the
    //       F2838x Technical Reference Manual.

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


