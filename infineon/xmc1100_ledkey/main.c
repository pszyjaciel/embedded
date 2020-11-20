// http://www.microcontroller.it/Tutorials/Elettronica/componenti/tm1638.htm
// https://github.com/rjbatista/tm1638-library/blob/master/TM16XX.cpp
// https://github.com/MartyMacGyver/TM1638-demos-and-examples/blob/master/README.md

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"

uint32_t event_count;
volatile bool czasMinou;

#define min(a,b)            (((a) < (b)) ? (a) : (b))

// czas obslugi tego przerwania dla MCLK 1MHz to ok 320microsec
// Aby uniknąć opóźnień, funkcja obsługi przerwania jest wykonywana z pamięci SRAM,
// która jest wystarczająco szybka i nie wprowadza żadnych cykli oczekiwania.
void __attribute__((section(".ISRAMCode"))) Time_Interval_Event(void) {
	TrackSignalByValue(1);	// zmierzyc czas obslugi tego przerwania
	czasMinou = true;
	/* Acknowledge Period Match interrupt generated on TIMER_CCU_1 */
	TIMER_ClearEvent(&TIMER_0);	// czy ma byc?
	TIMER_Stop(&TIMER_0);
	TrackSignalByValue(0);
}

void myDelayMS(uint32_t milliSec) {
	TrackSignalByValue(2);
	czasMinou = false;
	TIMER_SetTimeInterval(&TIMER_0, milliSec * 100000);
	TIMER_Start(&TIMER_0);
	while (!czasMinou) {
		;
	}
	TrackSignalByValue(0);
}


// The least significant bits are sent first
void mySend(uint8_t myDIO) {
	for (int i = 0; i < 8; i++) {
		if (myDIO & 1) {
			DIGITAL_IO_SetOutputHigh(&IODIO);
		} else {
			DIGITAL_IO_SetOutputLow(&IODIO);
		}
		//(myDIO & 1) ? DIGITAL_IO_SetOutputHigh(&IODIO) : DIGITAL_IO_SetOutputLow(&IODIO);
		DIGITAL_IO_SetOutputHigh(&IOCLK);	// po haj jest low.
		DIGITAL_IO_SetOutputLow(&IOCLK);	// min 400ns clock pulse width
		myDIO = myDIO >> 1;					// dawaj kolejny bit
	}
}

void sendCommand(uint8_t cmd) {
	DIGITAL_IO_SetOutputLow(&IOSTB);
	mySend(cmd);
	DIGITAL_IO_SetOutputHigh(&IOSTB);
}

void sendData(uint8_t address, uint8_t data) {
	sendCommand(0x44);
	DIGITAL_IO_SetOutputLow(&IOSTB);
	mySend(0xC0 | address);
	mySend(data);
	DIGITAL_IO_SetOutputHigh(&IOSTB);
}

void clearDisplay() {
	for (int i = 0; i < 8; i++) {
		sendData(i << 1, 0);
	}
}

void setupDisplay(bool active, uint8_t intensity) {
	uint8_t myCommand = (0x80 | (active ? 8 : 0) | min(7, intensity));
	SEGGER_RTT_printf(0, "myCommand: %02x \r\n", myCommand);
	sendCommand(myCommand);
}

//Low STB
//0x40; Command for writing to incrementing auto address
//High STB
//Low STB
//0xC0; address of the first digit on the left
//0x00; all off
//repeat the data 15 more times
//High STB
void resetLEDKey() {
	sendCommand(0x40); // set auto increment mode
	DIGITAL_IO_SetOutputLow(&IOSTB);
	mySend(0xc0);   // set starting address to 0
	for (uint8_t i = 0; i < 16; i++) {
		mySend(0x00);
	}
	DIGITAL_IO_SetOutputHigh(&IOSTB);
}

void myInitLEDKey() {
	resetLEDKey();	// musi ma byc
	setupDisplay(true, 127);
	clearDisplay();
}

// https://blog.3d-logic.com/2015/01/10/using-a-tm1638-based-board-with-arduino/
int main(void) {

	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U) {
		}
	}

	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

	// str. 253 akapit 12.9.5 RCU Registers (SCU) w XMC1100_AA-Step_v11.pdf
	unsigned int reset_status;
	reset_status = SCU_RESET->RSTSTAT & 0x000003FF; /* get the cause of reset */
	SCU_RESET->RSTCLR = 1U; /* clear status field */
	SEGGER_RTT_printf(0, "reset_status: %d \r\n", reset_status);

	myInitLEDKey();

	while (1U) {
		myDelayMS(200);
		DIGITAL_IO_ToggleOutput(&LED0);

		// wlacza fszyskie ledy
		for (int i = 15; i >= 0; i--) {
			sendData(i, (0xff));
		}

		myDelayMS(100);
		DIGITAL_IO_ToggleOutput(&LED0);

		// a tu wygasza
		clearDisplay();

//		for (int i = 0; i < 16; i++) {
//			sendData(i, (0x00));
//			SEGGER_RTT_printf(0, "%02x \r\n", i);
//		}
	}
}
