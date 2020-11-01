/** @file spi_iha.c
@brief Library to control the SPI communication.
@author Ib Havn
@defgroup spi SPI Driver
@{
	The implementation works with interrupt, meaning that there are no buzy-waiting involved.
	
	@note Only implemented for Master mode.
	
	@defgroup spi_init SPI Initialization
	@brief SPI Initialization.
	
	@defgroup spi_function SPI Functions
	@brief Commonly used SPI functions.
	
	Here you you will find the functions you will need.
	
@}
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi_iha.h"

#define CS_INACTIVE 0
#define CS_ACTIVE 1

static uint8_t _spi_active; /**< An explanation */

static buffer_struct_t *_tx_buf = 0;
static buffer_struct_t *_rx_buf = 0;
static volatile uint8_t *_cs_port = 0;
static uint8_t _cs_pin;
static uint8_t _cs_active_level;
static void(*_handler_call_back )() = 0;

static inline void _spi_send_byte(uint8_t byte) {
	SPDR = byte;
}

static inline void _set_cs(uint8_t state) {
	if (_cs_active_level == 1) {
		if (state == CS_ACTIVE) {
			*_cs_port |= _BV(_cs_pin);
		} else {
			*_cs_port &= ~_BV(_cs_pin);
		}
	} else {
		if (state == CS_ACTIVE) {
			*_cs_port &= ~_BV(_cs_pin);

		} else {
			*_cs_port |= _BV(_cs_pin);
		}
	}
}

/**********************************************************************//**
@ingroup spi_init
@brief Initialize the SPI driver.

Setup SPI according to parameters. Can be called every time the setup has to be changed.

@note This must be called at least once before the driver can be used.
@note Slave mode is not implemented!!!

@todo Document cs pin handling
@todo clk defines dosen't work for 2x handling!!!!

@param uint8_t mode SPI_MODE_MASTER: Master mode\n
SPI_MODE_SLAVE: Slave Mode.
@param int8_t clock_divider defines the SPI clock divider. Use SPI_CLOCK_DIVIDER_xx as parameter.
@param uint8_t clock_polarity defines the SPI clock polarity (CPOL). Use SPI_CLOCK_POLARITY_LEADING_xx as parameter.
@param uint8_t clock_phase defines the SPI clock phase (CPHA). Use SPI_CLOCK_PHASE_SAMPLE_??_EDGE as parameter.
@param uint8_t data_order SPI_DATA_ORDER_LSB: LSB transmitted first.\n
SPI_DATA_ORDER_MSB: MSB transmitted first.
@param buffer_struct_t * rx_buf 0: No receive buffer used, means no data vil be received from slave.\n
pointer to the receive buffer structure to store received data in @see buffer.
@param buffer_struct_t * tx_buf 0: No trasmit buffer used, means that only one byte can be transmitted at the time.\n
pointer to the transmit buffer structure to store transmit data in @see buffer.
**********************************************************************/
void spi_init(uint8_t mode, int8_t clock_divider, uint8_t clock_polarity, uint8_t clock_phase, uint8_t data_order, volatile uint8_t *cs_port, uint8_t cs_pin, uint8_t cs_active_level,
buffer_struct_t *rx_buf, buffer_struct_t *tx_buf, void(*handler_call_back )()) {
	
	asm volatile ("cli");
	
	_spi_active = 0;
	_tx_buf = tx_buf;
	_rx_buf = rx_buf;
	_cs_port = cs_port;
	_cs_pin = cs_pin;
	_cs_active_level = cs_active_level;
	_handler_call_back = handler_call_back;
	
	// SS, SCK, MOSI as output
	DDRB |= _BV(DDB0) | _BV(DDB1) |_BV(DDB2);

	_set_cs(CS_INACTIVE);
	
	// Disable SPI and SPI interrupt before changing setup
	SPCR &= ~(_BV(SPIE) | _BV(SPE));
	
	// setup SPI and enable it
	SPCR = mode | clock_divider | clock_polarity | clock_phase | data_order | _BV(SPE);
	if ((clock_divider == SPI_CLOCK_DIVIDER_2) || (clock_divider == SPI_CLOCK_DIVIDER_8) | (clock_divider == SPI_CLOCK_DIVIDER_32) || (clock_divider == SPI_CLOCK_DIVIDER_64)) {
		SPSR = _BV(SPI2X);
	}
	asm volatile ("sei");
}

/**********************************************************************//**
@ingroup spi_function
@brief Send a single byte to the SPI bus.

@return uint8_t SPI_OK: OK data is in buffer\n
SPI_NO_ROOM_IN_TX_BUFFER: Buffer full no data send.
@param uint8_t byte to be send.
**********************************************************************/
uint8_t spi_send_byte(uint8_t byte) {
	return spi_send_string(&byte, 1);
}

/********************************************//**
@ingroup spi_function
@brief Send an array of bytes to to the SPI bus.

@return uint8_t SPI_OK: OK data is in buffer\n
SPI_NO_ROOM_IN_TX_BUFFER: Buffer full no data send.
@param uint8_t *buf pointer to buffer to be send.
@param uint8_t len no of bytes to send.
***********************************************/
uint8_t spi_send_string(uint8_t *buf, uint8_t len) {
	uint8_t c_sreg = SREG;
	uint8_t tmp = 0;
	uint8_t result = SPI_OK;
	
	// disable interrupt
	c_sreg = SREG;
	asm volatile ("cli");
	
	// Check if buffer is free
	if ( ((_tx_buf != 0) && (len > (BUFFER_SIZE - _tx_buf->no_in_buffer))) || ((_tx_buf == 0) && (len > 1)) ) {
		result = SPI_NO_ROOM_IN_TX_BUFFER;
	} else 	{
		// If SPI in idle send the first byte
		if (!_spi_active) {
			_set_cs(CS_ACTIVE);
			// Enable SPI interrupt
			SPCR |= _BV(SPIE);
			_spi_send_byte(buf[0]);
			_spi_active = 1;
			tmp = 1;
		}
		
		// Put in the tx buffer
		for (uint8_t i = tmp; i < len; i++) {
			buffer_put_item(_tx_buf, buf[i]);
		}
	}
	
	// restore interrupt state
	SREG = c_sreg;
	asm volatile ("sei");

	return result;
}

/********************************************//**
@todo Documentation
***********************************************/
ISR(SPI_STC_vect) {
	uint8_t item;
	// store received byte if receive buffer available
	if (_rx_buf != 0){
		buffer_put_item(_rx_buf, SPDR);
	}
	// more bytes to send?
	if ( buffer_get_item(_tx_buf, &item) == BUFFER_OK) {
		_spi_send_byte(item);
	} else {
		// No
		// Disable SPI interrupt
		SPCR &= ~_BV(SPIE);
		_spi_active = 0;
		_set_cs(CS_INACTIVE);
	}
	
	// If handler defined call it
	if (_handler_call_back)
	{
		_handler_call_back();
	}
}