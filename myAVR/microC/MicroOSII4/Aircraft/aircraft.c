/** @file Aircraft.c
@brief Library to control the Aircraft driver.
@author Ib Havn
@defgroup aircraft Aircraft 2013
@{
	Here you you will find the functions you will need to control the Aircraft.
@}
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <includes.h>

#include "aircraft.h"
#include "Buffer/buffer.h"
#include "SPI/spi_iha.h"

#define ACC_CS_LOW (PORTB &= ~_BV(PB0))
#define ACC_CS_HIGH (PORTB |= _BV(PB0))

#define TC72_CE_LOW (PORTB &= ~_BV(PB4))
#define TC72_CE_HIGH (PORTB |= _BV(PB4))

#define LIS331HH_READ 7
#define LIS331HH_MULTI_READ 6

// Full-scale g/(2^16) = 12/(2^16)
#define ACC_SCALE_FACTOR 0.00018310546875

typedef enum {_init_temp1,_init_temp2, _read_temp, _init_acc1, _init_acc2, _read_acc} _states_t;

static buffer_struct_t tx_buf;
static buffer_struct_t rx_buf;

static int16_t _temp = 0;
static int16_t _x_acc = 0;
static int16_t _y_acc = 0;
static int16_t _z_acc = 0;

static void _handle_temp();
static void _handle_acc();

static void _acc_write_reg(uint8_t reg, uint8_t data)
{
	uint8_t send[2];
	send[0] = reg;
	send[1] = data;

	spi_send_string(send , 2);
}

static void _acc_read_reg(uint8_t reg, uint8_t no_of_bytes)
{
	uint8_t send[no_of_bytes+1];
	send[0] = (1<<LIS331HH_READ) | (((no_of_bytes > 1 ? 1 : 0)) << LIS331HH_MULTI_READ) | reg;
	for (uint8_t i = 1; i <= no_of_bytes; i++)
	{
		send[i] = 0;
	}
	
	buffer_clear(&rx_buf);
	spi_send_string(send , no_of_bytes+1);
}

static void _temp_write_control_reg(uint8_t byte)
{
	uint8_t send[2];
	// Write to control reg
	send[0] = 0x80;
	send[1] = byte;
	spi_send_string(send, 2);
}

static void _temp_read_reg(uint8_t reg, uint8_t no_of_bytes)
{
	uint8_t send[no_of_bytes+1];
	// Read from reg
	send[0] = reg;
	for (uint8_t i = 1; i <= no_of_bytes; i++)
	{
		send[i] = 0;
	}

	buffer_clear(&rx_buf);
	spi_send_string(send, no_of_bytes+1);
}

static void _select_acc()
{
	spi_init(SPI_MODE_MASTER, SPI_CLOCK_DIVIDER_128, SPI_CLOCK_IDLE_HEIGH, SPI_CLOCK_PHASE_SAMPLE_TRAILING_EDGE,SPI_DATA_ORDER_MSB, &PORTB, PB0, 0, &rx_buf, &tx_buf, _handle_acc);
}

static void _select_temp()
{
	spi_init(SPI_MODE_MASTER, SPI_CLOCK_DIVIDER_128, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_PHASE_SAMPLE_TRAILING_EDGE,SPI_DATA_ORDER_MSB, &PORTB, PB4, 1, &rx_buf, &tx_buf, _handle_temp);
}

/**********************************************************************//**
 @ingroup aircraft
 @brief Initialize the Aircraft driver.
 
 @note Must be called once before the Aircraft functions must be used!
 **********************************************************************/
void init_aircraft()
{
	USART_putstring("\nbefore: aircraft.c init_aircraft()\r\n");
	// Setup SPI
	{
		buffer_init(&tx_buf);
		buffer_init(&rx_buf);

		// set CE on TC72 low (disable it)
		DDRB |= _BV(DDB4);
		TC72_CE_LOW;

		// set CS on accelerometer high (disable it)
		DDRB |= _BV(DDB0);
		ACC_CS_HIGH;
	}
	
	// Setup LEDs
	{
		DDRB |= _BV(DDB5) | _BV(DDB6) | _BV(DDB7);
		set_led(LED_GREEN, LED_OFF);
		set_led(LED_RED, LED_OFF);
		set_led(LED_YELLOW, LED_OFF);
	}
	
	// Start up
	_handle_temp();
	USART_putstring("\nafter: aircraft.c init_aircraft()\r\n");
}

static void _poll_temp()
{
	_select_temp();
	_temp_read_reg(0x02, 2); // MSB and LSB
}

static void _poll_acc()
{
	_select_acc();
	_acc_read_reg(0x28, 6);
}

static void _handle_temp()
{
	uint8_t lsb, msb;
	static _states_t state = _init_temp1;
	
	switch (state)
	{
		case _init_temp1:
		{
			// Power on TC72
			_select_temp();
			_temp_write_control_reg(0x00);
			state = _init_temp2;			
			break;
		}
		
		case _init_temp2:
		{
			if (buffer_no_of_items(&rx_buf) == 2) {
				buffer_clear(&rx_buf);
				state = _read_temp;
				
				// Initialize ACC first
				_handle_acc();				
			}			
			break;
		}
		
		case _read_temp:
		{
			if (buffer_no_of_items(&rx_buf) == 3) {
				#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
				   OS_CPU_SR cpu_sr = 0;
				#endif
				 OS_ENTER_CRITICAL();				
				buffer_get_item(&rx_buf, &lsb); // Throw away the command response
				buffer_get_item(&rx_buf, &msb);
				buffer_get_item(&rx_buf, &lsb);
					
				_temp = (msb << 2) | (lsb >> 6);
				
				OS_EXIT_CRITICAL();
				
				// check if negative
				if (_temp & (1 << 9))
				{
					_temp |= 0xFE00;
				}
				
				_poll_acc();
			}
			break;
		}
		default:
		break;
	}
}

static void _handle_acc()
{
	uint8_t lsb, msb;
	static _states_t state = _init_acc1;
		
	switch (state)
	{
		case _init_acc1:
		{
			// Setup ACC to Normal mode, 400 Hz, +-6g
			_select_acc();
			_acc_write_reg(0x20, 0x37);
			state = _init_acc2;			
			break;
		}
		
		case _init_acc2:
		{
			if (buffer_no_of_items(&rx_buf) == 2) {
				state = _read_acc;
				_poll_acc();
			}			
			break;
		}
		
		case _read_acc:
		{
			if (buffer_no_of_items(&rx_buf) == 7) {
				#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
				   OS_CPU_SR cpu_sr = 0;
				#endif
				OS_ENTER_CRITICAL();	
								
				buffer_get_item(&rx_buf, &lsb); // Throw away the command response
				buffer_get_item(&rx_buf, &lsb);
				buffer_get_item(&rx_buf, &msb);
				_x_acc = (msb << 8) | lsb;
				buffer_get_item(&rx_buf, &lsb);
				buffer_get_item(&rx_buf, &msb);
				_y_acc = (msb << 8) | lsb;
				buffer_get_item(&rx_buf, &lsb);
				buffer_get_item(&rx_buf, &msb);
				_z_acc = (msb << 8) | lsb;
				
				OS_EXIT_CRITICAL();
				
				_poll_temp();
			}
			break;
		}		

		default:
		break;
	}	
}

/**********************************************************************//**
 @ingroup aircraft
 @brief Get the temperature on the Aircraft.

 @return int16_t Temperature in 0.25 C resolution.
 **********************************************************************/
int16_t get_temp() {
	return _temp;
}

/**********************************************************************//**
 @ingroup aircraft
 @brief Get the X-axis acceleration.

 @return float Acceleration in g [N/kg]
 **********************************************************************/
float get_x_acc() {
	return _x_acc * ACC_SCALE_FACTOR;
}

/**********************************************************************//**
 @ingroup aircraft
 @brief Get the Y-axis acceleration.

 @return float Acceleration in g [N/kg]
 **********************************************************************/
float get_y_acc() {
	return _y_acc * ACC_SCALE_FACTOR;
}

/**********************************************************************//**
 @ingroup aircraft
 @brief Get the Z-axis acceleration.

 @return float Acceleration in g [N/kg]
 **********************************************************************/
float get_z_acc() {
	return _z_acc * ACC_SCALE_FACTOR;
}

/**********************************************************************//**
 @ingroup aircraft
 @brief Controls the leds on the aircraft.

 @param uint8_t led the led to be controlled use:\n
	LED_YELLOW, LED_RED, LED_GREEN
 
 @param uint8_t led_state to put the led in use:\n
	LED_ON, LED_OFF
 **********************************************************************/
void set_led(uint8_t led, uint8_t led_state)
{
	if(led_state == LED_ON)
	{
		PORTB &= ~_BV(led);
	} else 
	{
		PORTB |= _BV(led);
	}
}