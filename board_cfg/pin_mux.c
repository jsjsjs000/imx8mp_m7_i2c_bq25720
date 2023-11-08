/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MIMX8ML8xxxLZ
package_id: MIMX8ML8DVNLZ
mcu_data: ksdk2_0
processor_version: 0.9.1
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
	BOARD_InitPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm7}
- pin_list:
  - {pin_num: AJ5, peripheral: UART4, signal: uart_rx, pin_signal: UART4_RXD, PE: Enabled, HYS: CMOS, PUE: Weak_Pull_Up, FSEL: Slow, DSE: X1}
  - {pin_num: AH5, peripheral: UART4, signal: uart_tx, pin_signal: UART4_TXD, PE: Enabled, HYS: CMOS, PUE: Weak_Pull_Up, FSEL: Slow, DSE: X1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)                                /*!< Function assigned for the core: Cortex-M7F[m7] */
{
		/* UART4 - M7 debug */
	IOMUXC_SetPinMux(IOMUXC_UART4_RXD_UART4_RX, 0U);
	IOMUXC_SetPinConfig(IOMUXC_UART4_RXD_UART4_RX, 
			IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);
	IOMUXC_SetPinMux(IOMUXC_UART4_TXD_UART4_TX, 0U);
	IOMUXC_SetPinConfig(IOMUXC_UART4_TXD_UART4_TX, 
			IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);

		/* I2C4 - BQ40Z50 */
	IOMUXC_SetPinMux(IOMUXC_I2C4_SCL_I2C4_SCL, 1U); /// Software Input On Field
	IOMUXC_SetPinConfig(IOMUXC_I2C4_SCL_I2C4_SCL, 
			IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
			IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
			IOMUXC_SW_PAD_CTL_PAD_ODE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |            /// Schmitt
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);             /// Pull Enabled
	IOMUXC_SetPinMux(IOMUXC_I2C4_SDA_I2C4_SDA, 1U);
	IOMUXC_SetPinConfig(IOMUXC_I2C4_SDA_I2C4_SDA, 
			IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
			IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
			IOMUXC_SW_PAD_CTL_PAD_ODE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);

		/* GPIO1_00, GPIO1_01, GPIO1_03, GPIO1_05 as output - 4 devboard buttons - SOD5 switch devboard */
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO00_GPIO1_IO00, 1U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO00_GPIO1_IO00, 
			IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
			IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO01_GPIO1_IO01, 1U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO01_GPIO1_IO01, 
			IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
			IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 1U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 
			IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
			IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);
	// IOMUXC_SetPinMux(IOMUXC_GPIO1_IO05_GPIO1_IO05, 1U);
	// IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO05_GPIO1_IO05, 
	// 		IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
	// 		IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
	// 		IOMUXC_SW_PAD_CTL_PAD_PE_MASK);

		/* GPIO1_05 as input 4-th button - SOD5 switch devboard */
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO05_GPIO1_IO05, 1U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO05_GPIO1_IO05, 
			IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
			IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |
			IOMUXC_SW_PAD_CTL_PAD_PE_MASK);

	// IOMUXC_SetPinMux(IOMUXC_SD1_CLK_GPIO2_IO00, 0U);
	// IOMUXC_SetPinConfig(IOMUXC_SD1_CLK_GPIO2_IO00, 
	// 		IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
	// 		IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK);
	// IOMUXC_SetPinMux(IOMUXC_SPDIF_EXT_CLK_GPIO5_IO05, 0U);
	// IOMUXC_SetPinConfig(IOMUXC_SPDIF_EXT_CLK_GPIO5_IO05, 
	// 		IOMUXC_SW_PAD_CTL_PAD_DSE(3U) |
	// 		IOMUXC_SW_PAD_CTL_PAD_FSEL_MASK);
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
