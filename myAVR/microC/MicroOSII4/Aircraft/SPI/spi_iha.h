/*
 * spi_iha.h
 *
 * Created: 16-03-2013 11:30:09
 *  Author: IHA
 */ 


#ifndef SPI_IHA_H_
#define SPI_IHA_H_

// ------------- Includes -------------------
#include <inttypes.h>

#include "../Buffer/buffer.h"

// ------------- Defines --------------------
#define SPI_MODE_MASTER _BV(MSTR)
#define SPI_MODE_SLAVE NOT_IMPLEMENTED

// These defines will not work correctly - 2x clk detection fails!!!
#define SPI_CLOCK_DIVIDER_2 0
#define SPI_CLOCK_DIVIDER_4 0
#define SPI_CLOCK_DIVIDER_8 _BV(SPR1)
#define SPI_CLOCK_DIVIDER_16 _BV(SPR0)
#define SPI_CLOCK_DIVIDER_32 _BV(SPR1)
#define SPI_CLOCK_DIVIDER_64 (_BV(SPR1) | _BV(SPR0))
#define SPI_CLOCK_DIVIDER_128 (_BV(SPR1) | _BV(SPR0))

#define SPI_CLOCK_IDLE_LOW 0
#define SPI_CLOCK_IDLE_HEIGH _BV(CPOL)

#define SPI_CLOCK_PHASE_SAMPLE_LEADING_EDGE 0
#define SPI_CLOCK_PHASE_SAMPLE_TRAILING_EDGE _BV(CPHA)

#define SPI_DATA_ORDER_LSB _BV(DORD)
#define SPI_DATA_ORDER_MSB 0

// return codes
#define SPI_OK 0
#define SPI_NO_ROOM_IN_TX_BUFFER 1

// ------------- Prototypes -----------------
void spi_init(uint8_t mode, int8_t clock_divider, uint8_t clock_polarity, uint8_t clock_phase, uint8_t data_order, volatile uint8_t *cs_port, uint8_t cs_pin, uint8_t cs_active_level,
			  buffer_struct_t *rx_buf, buffer_struct_t *tx_buf, void(*handler_call_back )());
uint8_t spi_send_byte(uint8_t byte);
uint8_t spi_send_string(uint8_t buf[], uint8_t len);
#endif /* SPI_IHA_H_ */