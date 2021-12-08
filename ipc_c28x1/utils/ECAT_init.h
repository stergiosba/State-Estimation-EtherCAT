/*
 * ECAT_init.h
 *
 *  Created on: 8 December 2021
 *      Author: Stergios Bachoumas
 */

#ifndef ECAT_INIT_H_
#define ECAT_INIT_H_

#include "device.h"


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


void configureECAT(void);
void setupESCGPIOs(void);

#endif /* ECAT_INIT_H_ */
