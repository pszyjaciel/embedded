
/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-08-06:
 *     - Initial version for DAVEv4.
 *
 * @endcond
 *
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "spi_slave.h"

/***********************************************************************************************************************
 * EXTERN DECLARATIONS
 ***********************************************************************************************************************/

extern void SPI_SLAVE_lTransmitHandler(const SPI_SLAVE_t * const handle);
extern void SPI_SLAVE_lReceiveHandler(const SPI_SLAVE_t * const handle);
extern void SPI_SLAVE_lProtocolHandler(const SPI_SLAVE_t * const handle);


/**********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
SPI_SLAVE_STATUS_t SPI_SLAVE_0_init(void);

/*USIC channel configuration*/
const XMC_SPI_CH_CONFIG_t SPI_SLAVE_0_channel_config =
{
  .bus_mode     = XMC_SPI_CH_BUS_MODE_SLAVE,
  .parity_mode   = XMC_USIC_CH_PARITY_MODE_NONE
};
/*MISO pin configuration*/
const XMC_GPIO_CONFIG_t SPI_SLAVE_0_mosi1_pin_config   = 
{ 
#ifdef P1_2_AF_U0C1_DOUT0
  .mode             = (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P1_2_AF_U0C1_DOUT0), 
#else
  .mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
#endif
  .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
};

/*MISO pin configuration used for initializing*/
const SPI_SLAVE_PIN_CONFIG_t SPI_SLAVE_0_miso_pin = 
{
  .port = (XMC_GPIO_PORT_t *)PORT1_BASE,
  .config = &SPI_SLAVE_0_mosi1_pin_config,
  .hw_control = XMC_GPIO_HWCTRL_DISABLED,
  .pin = 2U
};

/*MOSI pin configuration*/
const XMC_GPIO_CONFIG_t SPI_SLAVE_0_mosi_pin_config   = 
{ 
  .mode             = XMC_GPIO_MODE_INPUT_TRISTATE, 
  .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
};

/*MOSI pin configuration used for initializing*/
const SPI_SLAVE_PIN_CONFIG_t SPI_SLAVE_0_mosi_pin = 
{
  .port = (XMC_GPIO_PORT_t *)PORT1_BASE,
  .config = &SPI_SLAVE_0_mosi_pin_config,
  .hw_control = XMC_GPIO_HWCTRL_DISABLED,
  .pin = 3U
};

/*SCLK pin configuration*/
const XMC_GPIO_CONFIG_t SPI_SLAVE_0_sclk_pin_config   = 
{ 
  .mode             = XMC_GPIO_MODE_INPUT_TRISTATE, 
  .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
};

/*SELIN pin configuration*/
const XMC_GPIO_CONFIG_t SPI_SLAVE_0_slavesel_pin_config   = 
{ 
  .mode             = XMC_GPIO_MODE_INPUT_TRISTATE, 
  .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
};

const SPI_SLAVE_CONFIG_t SPI_SLAVE_0_conf =
{
  .channel_config = &SPI_SLAVE_0_channel_config,

  .mosi1_pin_config = &SPI_SLAVE_0_miso_pin,
  .mosi0_pin_config = &SPI_SLAVE_0_mosi_pin,
  .fptr_spi_slave_config = SPI_SLAVE_0_init,
  .tx_cbhandler = NULL,
  .rx_cbhandler = NULL,
  .parity_error_cbhandler = NULL,
  .slave_select_cbhandler = NULL,
  .transmit_mode = SPI_SLAVE_TRANSFER_MODE_INTERRUPT,
  .receive_mode = SPI_SLAVE_TRANSFER_MODE_INTERRUPT,
  .tx_fifo_size = XMC_USIC_CH_FIFO_SIZE_16WORDS,
  .rx_fifo_size = XMC_USIC_CH_FIFO_SIZE_16WORDS,
  .spi_configured_mode = XMC_SPI_CH_MODE_STANDARD,
  .tx_sr = 3U,
#ifdef USIC0_C1_DX0_P1_3
  .dx0_source = (SPI_SLAVE_INPUT_t)USIC0_C1_DX0_P1_3,
#else
  .dx0_source = SPI_SLAVE_INPUT_INVALID,
#endif
};

SPI_SLAVE_RUNTIME_t SPI_SLAVE_0_runtime =
{
  .spi_current_mode = XMC_SPI_CH_MODE_STANDARD,
  .data_size = SPI_SLAVE_DATA_SIZE_8BITS,
  .tx_busy = false,
  .rx_busy = false
};

SPI_SLAVE_t SPI_SLAVE_0 =
{
  .channel = XMC_SPI0_CH1,
  .config = &SPI_SLAVE_0_conf,
  .runtime = &SPI_SLAVE_0_runtime
};

/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/
/*Channel initialization function*/
SPI_SLAVE_STATUS_t SPI_SLAVE_0_init()
{
  SPI_SLAVE_STATUS_t status = SPI_SLAVE_STATUS_SUCCESS;
  /*Reset the runtime state variables*/
  SPI_SLAVE_0.runtime->tx_busy = false;
  SPI_SLAVE_0.runtime->rx_busy = false;

  /*Configure SCLK pin*/
  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT2_BASE, 7U, &SPI_SLAVE_0_sclk_pin_config);
  /*Configure slave select pin*/
  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT2_BASE, 6U, &SPI_SLAVE_0_slavesel_pin_config);
  /*Configure MOSI pin*/
  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT1_BASE, 3U, &SPI_SLAVE_0_mosi_pin_config);
  /* Initialize USIC channel in SPI slave mode*/
  XMC_SPI_CH_Init(XMC_SPI0_CH1, &SPI_SLAVE_0_channel_config);
  XMC_SPI_CH_SetBitOrderMsbFirst(XMC_SPI0_CH1);

  XMC_SPI_CH_SetWordLength(XMC_SPI0_CH1, (uint8_t)8U);
  XMC_SPI_CH_SetFrameLength(XMC_SPI0_CH1, (uint8_t)64U);

  /*Set input source path*/
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, (XMC_SPI_CH_INPUT_t)XMC_USIC_CH_INPUT_DX0, 0U);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, (XMC_SPI_CH_INPUT_t)XMC_USIC_CH_INPUT_DX3, 0U);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, (XMC_SPI_CH_INPUT_t)XMC_USIC_CH_INPUT_DX4, 3U);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, (XMC_SPI_CH_INPUT_t)XMC_USIC_CH_INPUT_DX5, 3U);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, (XMC_SPI_CH_INPUT_t)XMC_USIC_CH_INPUT_DX1, 6U);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH1, (XMC_SPI_CH_INPUT_t)XMC_USIC_CH_INPUT_DX2, 6U);
  XMC_SPI_CH_EnableInputInversion(XMC_SPI0_CH1, XMC_SPI_CH_INPUT_SLAVE_SELIN);
  /*Configure transmit FIFO*/
  XMC_USIC_CH_TXFIFO_Configure(XMC_SPI0_CH1,
        16U,
        XMC_USIC_CH_FIFO_SIZE_16WORDS,
        1U);
  /*Configure receive FIFO*/
  XMC_USIC_CH_RXFIFO_Configure(XMC_SPI0_CH1,
        0U,
        XMC_USIC_CH_FIFO_SIZE_16WORDS,
        0U);
  /*Set service request for SPI protocol events*/
  XMC_USIC_CH_SetInterruptNodePointer(XMC_SPI0_CH1, XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL,
     0U);
  /*Set service request for tx FIFO transmit interrupt*/
  XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(XMC_SPI0_CH1, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
      3U);
  /*Set service request for rx FIFO receive interrupt*/
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_SPI0_CH1, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
       0x1U);
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_SPI0_CH1, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE,
       0x1U);
  /*Set priority and enable NVIC node for transmit interrupt*/
  NVIC_SetPriority((IRQn_Type)12, 3U);
  NVIC_EnableIRQ((IRQn_Type)12);
  /*Set priority and enable NVIC node for receive interrupt*/
  NVIC_SetPriority((IRQn_Type)10, 2U);
  NVIC_EnableIRQ((IRQn_Type)10);
  /* Start SPI */
  XMC_SPI_CH_Start(XMC_SPI0_CH1);

  /* Initialize SPI Slave MISO pin */
  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT1_BASE, 2U, &SPI_SLAVE_0_mosi1_pin_config);
  XMC_GPIO_SetHardwareControl((XMC_GPIO_PORT_t *)PORT1_BASE, 2U, XMC_GPIO_HWCTRL_DISABLED);

  return status;
}
/*Interrupt handlers*/
/*Transmit ISR*/
void SPI_SLAVE_0_TX_HANDLER()
{
  SPI_SLAVE_lTransmitHandler(&SPI_SLAVE_0);
}

/*Receive ISR*/
void SPI_SLAVE_0_RX_HANDLER()
{
  SPI_SLAVE_lReceiveHandler(&SPI_SLAVE_0);
}

