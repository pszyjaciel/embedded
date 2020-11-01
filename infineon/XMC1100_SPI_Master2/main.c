/**
 * @file
 * @date 01 Aug, 2015
 * @version 1.0.0
 *
 * @brief SPI demo example
 *
 * Send two periodic messages via SPI with different lengths
 *
 * This example sends a SPI frame on each alternate (receive) interrupt.
 * Initialize P0.5 which connected to an on-board LED as output pin.
 * Initialize P1.1 (SEL pin), P1.2 (TX, RX pin) and P1.4 (CLK)for SPI communication with loopback Next,
 * Initialize clock and USIC channel 1.
 * Followed by create a receive start interrupt handler to toggle LED and send a SPI frame.
 * Generate the first alternate (receive) interrupt.

 USIC0_CH1 (USIC0_CH1_spi_pins.png):
 P1.1 (SEL pin): ALT7
 P1.2 (TX, RX pin): ALT7
 P1.4 (CLK): ALT2

 USIC0_CH0 (USIC0_CH0_spi_pins.png):
 P0.8 (SCLK pin): ALT6
 P0.9 (SEL0 pin): ALT6
 P0.14 (MOSI): ALT6
 P0.15 (MISO): ALT6

 USIC0_CH1 (USIC0_CH1_spi_pins2.png):
 P0.6 (MISO pin): ALT7
 P0.7 (MOSI pin): ALT7
 P0.8 (SCLK): ALT7
 P0.9 (SELO0): ALT7
 */

//#include <xmc_common.h>
#include "xmc_spi.h"
#include "xmc_gpio.h"

#define LED P1_0
#define LED1 P1_1

void timing_delay(void);

uint16_t datain;
uint32_t myTicks = 0;

XMC_GPIO_CONFIG_t rx_pin_config;
XMC_GPIO_CONFIG_t tx_pin_config;
XMC_GPIO_CONFIG_t selo_pin_config;
XMC_GPIO_CONFIG_t clk_pin_config;

XMC_SPI_CH_CONFIG_t spi_config = { .baudrate = 1000, .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER, .selo_inversion =
		XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS, .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE };

void timing_delay(void) {
	uint32_t d;
	for (d = 0; d < 100000; d++) {
		;
	}
}

void USIC0_0_IRQHandler(void) {

	if ((XMC_SPI_CH_GetStatusFlag(XMC_SPI0_CH1) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 1U) {
		XMC_SPI_CH_ClearStatusFlag(XMC_SPI0_CH1, XMC_SPI_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
		timing_delay();
		XMC_GPIO_ToggleOutput(LED);

		datain = XMC_USIC_CH_RXFIFO_GetData(XMC_SPI0_CH1);

		//Transmit data 0x4D2 (1234)
		XMC_USIC_CH_TXFIFO_PutData(XMC_SPI0_CH1, 0x4D2);
	} else {
		XMC_GPIO_ToggleOutput(LED1);
	}

	myTicks++;
	if (myTicks % 100 == 0) {
		XMC_GPIO_ToggleOutput(LED);
	}
}

int main(void) {
	/* Initialize SPI */
	XMC_SPI_CH_Init(XMC_SPI0_CH1, &spi_config);
	XMC_SPI_CH_SetWordLength(XMC_SPI0_CH1, 16);
	XMC_SPI_CH_SetFrameLength(XMC_SPI0_CH1, 16);
	XMC_SPI_CH_SetBitOrderMsbFirst(XMC_SPI0_CH1);

	XMC_USIC_CH_RXFIFO_Configure(XMC_SPI0_CH1, 32, XMC_USIC_CH_FIFO_SIZE_32WORDS, 0);
	XMC_USIC_CH_TXFIFO_Configure(XMC_SPI0_CH1, 0, XMC_USIC_CH_FIFO_SIZE_32WORDS, 0);
	//XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, XMC_SPI_CH_INPUT_DIN0, USIC0_C1_DX0_P1_2);

	// DXxCR: x=0..5
	XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, XMC_SPI_CH_INPUT_DIN0, USIC0_C1_DX0_P0_6); // 0, 2

	/* Event/interrupt configuration. */
	XMC_SPI_CH_EnableEvent(XMC_SPI0_CH1, XMC_SPI_CH_EVENT_ALTERNATIVE_RECEIVE);

	/* Start operation. */
	XMC_SPI_CH_Start(XMC_SPI0_CH1);

	/* GPIO Output pin configuration P1.2 (MOSI: TX pin) */
	tx_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
	//XMC_GPIO_Init(XMC_GPIO_PORT1, 2, &tx_pin_config);
	XMC_GPIO_Init(XMC_GPIO_PORT0, 7, &tx_pin_config);

	/* GPIO Input pin configuration P1.2 (MISO: RX pin) */
	rx_pin_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
	//XMC_GPIO_Init(XMC_GPIO_PORT1, 2, &rx_pin_config);
	XMC_GPIO_Init(XMC_GPIO_PORT0, 6, &rx_pin_config);

	/* GPIO Clock pin configuration P1.4 (SCLK) */
	clk_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2;
	//XMC_GPIO_Init(XMC_GPIO_PORT1, 4, &clk_pin_config);
	XMC_GPIO_Init(XMC_GPIO_PORT0, 8, &clk_pin_config);

	/* GPIO Slave Select line pin configuration P1.1 (SELO0 pin) */
	selo_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
	//XMC_GPIO_Init(XMC_GPIO_PORT1, 1, &selo_pin_config);
	XMC_GPIO_Init(XMC_GPIO_PORT0, 9, &selo_pin_config);

	XMC_GPIO_SetMode(LED, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

	NVIC_SetPriority(USIC0_0_IRQn, 0U);
	NVIC_EnableIRQ(USIC0_0_IRQn);

	// XMC1100 Address Space str. 7-2
	// USIC0_CH1: 0x48000200 (Table 14-21 Registers Address Space)
	// 14.11.4.2 Protocol Status Register str. 14-169
	// The flags in the protocol status register can be cleared by writing a 1 to the
	// corresponding bit position in register PSCR. Writing a 0 has no effect.
	USIC0_CH1->PSR_SSCMode |= 0x8000;	// reset AIF (Alternative Receive Indication Flag)
	XMC_USIC_CH_TriggerServiceRequest(XMC_SPI0_CH1, 0);

	while (1) {
		/* Infinite loop */
	}
}

