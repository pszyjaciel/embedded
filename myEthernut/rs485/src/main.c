// This program reads and displays values of different parameters from a Micromaster Inverter.
// It works with two serial ports of AVR microcontroller. One is connected to the RS485-RS232 converter, while the other
// displays values on COM1 on the PC.

// The AVR-project has been compiled with AVR Compiler.

#include <avr/interrupt.h>
#include <util/delay.h>
#include "usscalc.h"
#include "nokia_lcd.h"
#include "debounce.h"

uint8_t errorFlag = 0;
uint8_t counter = 0;

uint8_t myIndex, rxLength;

ISR(USART1_RX_vect) {
	char ReceivedByte;
	ReceivedByte = UDR1;				// Fetch the received byte value into the variable "ReceivedByte"

	if (ReceivedByte != 0x02 && myIndex == 0) {
		errorFlag = 1;
		return;
	}

	if (myIndex == 1) {
		rxLength = ReceivedByte;          // save the length of the telegram
		if (rxLength != 0x0c) {
			errorFlag = 1;
		}
	}

	errorFlag = 0;
	myRxArray[myIndex] = ReceivedByte;
	myIndex++;

	if (myIndex > rxLength + 1) {
		myIndex = 0;
		USART1_RX_complete = 1;
	}
}

// Called at about 28Hz (~36ms), uses 16-bit timer1
ISR(TIMER1_OVF_vect) {
	// Debounce buttons. debounce() is declared static inline
	// in debounce.h so we will not suffer from the added overhead
	// of a (external) function call (nie bedziemy cierpiec)

	PORTE = PORTE & ~(1 << PE5);
	debounce();						// takes 6 microsec.
	PORTE = PORTE | (1 << PE5);
}

/**
 * @brief This is the Interrupt handler, which is called every 4.55sec when the timer overflows.
 * The heartbeat value should be incremented each time new data has been read in the function getAllValues().
 * By the comparing the previous value with the heartbeat value will be ensured, that the connection
 * to the USS-device has not been dropped. In other case an error message will be displayed on the LCD.
 * @param no parameters
 * @return no return values
 */ISR(TIMER3_OVF_vect) {
	if (previous == heartbeat) {
		errorFlag = 1;							// set the error flag
		previous = heartbeat;
	} else {
		previous = heartbeat;
	}
	if (counter % 10) {
		errorFlag = 0;							// reset the error flag
		heartbeat++;
	}
	counter++;
}

/**
 * @brief This function initializes the 16bit-timer3 in a normal mode (0) with a period of about 4.55 seconds.
 * When the TOP has been reached (TCNT3 rolls over 65535), the Overflow Interrupt will be fired.
 * @param no parameters
 * @return no return values
 */
void Timer3_Init(void) {
	// 16bit
	TCCR3A = 0;
	TCCR3B = 0;
	TCCR3C = 0;

	TCCR3B = TCCR3B & ~(1 << WGM33) & ~(1 << WGM32);
	TCCR3A = TCCR3A & ~(1 << WGM31) & ~(1 << WGM30);
	TCCR3B = TCCR3B | (1 << CS32) & ~(1 << CS31) | (1 << CS30);          // Prescaler: s. 136 clk/1024 (every 9sec.)
	ETIMSK = ETIMSK | (1 << TOIE3);										// Overflow Interrupt Enable
}

// Mode CTC (8 bit)
void Timer2_Init(void) {
	// OCR2 * prescaler / Fosc - 255 : 17,7ms, 16 : 1,1ms
	TCCR2 = 0;

	TCCR2 = TCCR2 | (1 << WGM21) & ~(1 << WGM20);			// CTC
	TCCR2 = TCCR2 & ~(1 << COM21) & ~(1 << COM20);
	OCR2 = 0xff;											// 255 * 1024 / 14745600 = 17.71ms
	// TIMSK = TIMSK | (1 << OCIE2);						// Interrupt when Compare Match
	// TIMSK = TIMSK | (1 << TOIE2);						// Timer/Counter0 Overflow Interrupt Enable
	TCCR2 = TCCR2 | (1 << CS22) & ~(1 << CS21) | (1 << CS20);          // clk/1024
}

uint8_t getInputs() {

	uint8_t myInputs = 0;

	if (button_down(BUTTON1_MASK)) {
		myInputs = myInputs | (1 << 0);
		printBigString(0, 0, "1");
	} else if (button_down(BUTTON2_MASK)) {
		printBigString(0, 0, "2");
		myInputs = myInputs | (1 << 1);
	} else if (button_down(BUTTON3_MASK)) {
		printBigString(0, 0, "3");
		myInputs = myInputs | (1 << 2);
	} else if (button_down(BUTTON4_MASK)) {
		printBigString(0, 0, "4");
		myInputs = myInputs | (1 << 3);
	} else if (button_down(BUTTON5_MASK)) {
		printBigString(0, 0, "5");
		myInputs = myInputs | (1 << 4);
	} else {
		printBigString(0, 0, "0");
	}
	return myInputs;
}

int main(void) {

	uint8_t i, inputs;
	char * myShortStr;

	cli();
	// we have 2 serial ports. one for rs485 connection, another for debugging.
	RS232_init(38400);
	RS485_init(9600);          // when 4800 baud or less transfer is not readable

	DDRE = DDRE | (1 << PE5) | (1 << PE3);          // oscilloscope

	N5110_Init();				// initialize the LCD Nokia display
	debounce_init();	        // (Timer1)
	Timer2_Init();				// timeout timer
	Timer3_Init();				// initialize the 16-bit timer
	sei();

	_delay_ms(200);				// stabilize timer before RS232_putstring()

	uint16_t mmParameters[] =
		{ 131, 132, 133, 134, 135, 922, 923 };
	uint8_t mmParametersLength = sizeof(mmParameters) / 2;          // max 127 parameters (of short)
	uint16_t * mmValues;

	myIndex = 0;
	rxLength = 0;
	USART1_RX_complete = 0;

	while (1) {

		inputs = getInputs();
		RS232_putstring("0000: ");
		print_hexWord(inputs);
		RS232_putstring("\r\n");

		// read multiple parameters from MM
		mmValues = getAllValues(mmParameters, mmParametersLength);

		for (i = 0; i < (mmParametersLength); i++) {
			print_hexWord(mmParameters[i]);
			RS232_putstring(": ");
			print_hexWord(mmValues[i]);
			RS232_putstring("\r\n");
		}
		RS232_putstring("\r\n");

		myShortStr = short2String(mmParameters[4]);
		printBigString(1, 2, myShortStr);

		myShortStr = short2String(mmValues[4]);
		printBigString(1, 4, myShortStr);

		if (errorFlag != 0) {
			N5110_Clear();
			printSmString(0, 0, "Connection error. Check cables and then reset the Ethernut board.");
		}
		_delay_ms(2000);
	}

	return 0;
}
