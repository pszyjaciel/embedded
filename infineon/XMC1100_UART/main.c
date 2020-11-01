#include <DAVE.h> // Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// LED Blinking:
#define ON 1
#define OFF 0

// SoftwareTimer:
#define ONESEC 1500000U

// Transmit:
const char ucArrayMenu[] = "\r\n"
		"1 ... LEDs ON\r\n"
		"2 ... LEDs OFF\r\n"
		"3 ... LEDs Toggle\r\n"
		"4 ... LEDs Blinking\r\n"
		"\r\n"
		"your choice: ";

uint32_t ucStringLength1 = 0;
uint32_t ucStringLength2 = 0;

char mb[200]; // MessageBuffer for sprintf()
int iMainMenuLoopCounter = 0;
int iISRLoopCounter = 0;

bool bTransmitBusy = true;

// LED Blinking:
bool bLEDsBlinkingStatusGlobal = OFF; // used by the BLINKING INTERRUPT
bool bLEDsOnOffStatusGlobal = OFF; // used by the fLEDs_TOGGLE function

// ***** function prototypes: *****
// Receive:
uint8_t ucUartReceivedDataGlobal = '\0';
volatile unsigned int uiReceivedCounterGlobal = 0;
unsigned int uiReceivedCounterOLD_Global = 0;

// Transmit:
void fMyPrintf(const char* p);
void fEndOfTransmitCallback(void);

// LEDs:
void fLEDs_ON(void);
void fLEDs_OFF(void);
void fLEDs_TOGGLE(void);

// LEDs Blinking:
void fEverySecond(void);

int main(void) {
	uint32_t SoftwareTimer;
	SYSTIMER_STATUS_t statusSYSTIMER;

	DAVE_Init(); // Initialization of DAVE APPs

	SoftwareTimer = (uint32_t) SYSTIMER_CreateTimer(ONESEC, SYSTIMER_MODE_PERIODIC, (void*) fEverySecond, NULL);
	if (SoftwareTimer != 0U) {
		; // Software timer is created successfully
	} else {
		while (1)
			; // Software timer creation is failed
	}
	statusSYSTIMER = SYSTIMER_StartTimer(SoftwareTimer);
	if (statusSYSTIMER == SYSTIMER_STATUS_SUCCESS) {
		; // Software timer is running
	} else {
		while (1)
			; // Error during Software timer start operation
	}

	iMainMenuLoopCounter++;
	sprintf(mb, "*** MainMenuLoopCounter = %d ***\r\n", iMainMenuLoopCounter);

	// Write formatted data to string mb (MesssageBuffer)
	fMyPrintf(mb);
	while (bTransmitBusy)
		;

	fMyPrintf(ucArrayMenu);
	while (bTransmitBusy)
		;

	const char* myUARTMessage;
	while (1U) {
		if (uiReceivedCounterOLD_Global != uiReceivedCounterGlobal) {
			switch (ucUartReceivedDataGlobal) {
			case '1':
				myUARTMessage = "*** LEDs ON !!! ***\r\n";
				bLEDsBlinkingStatusGlobal = OFF;
				fLEDs_ON();
				break;
			case '2':
				myUARTMessage = "*** LEDs OFF !!! ***\r\n";
				bLEDsBlinkingStatusGlobal = OFF;
				fLEDs_OFF();
				break;
			case '3':
				myUARTMessage = "*** LEDs TOGGLED !!! ***\r\n";
				bLEDsBlinkingStatusGlobal = OFF;
				fLEDs_TOGGLE();
				break;
			case '4':
				myUARTMessage = "*** LEDs BLINKING !!! ***\r\n";
				bLEDsBlinkingStatusGlobal = ON;
				break;
			case '5':
				;
				break;
			default:
				;
				break;
			}
			fMyPrintf(myUARTMessage);
			while (bTransmitBusy) {
				;
			}
			uiReceivedCounterOLD_Global = uiReceivedCounterGlobal;
			iMainMenuLoopCounter++;

			// Write formatted data to string mb
			sprintf(mb, "*** MainMenuLoopCounter = %d ***\r\n", iMainMenuLoopCounter);
			fMyPrintf(mb);
			while (bTransmitBusy) {
				; // pacz pszerwanie fEndOfTransmitCallback()
			}
		}
	}
}


// pacz UART_0 i Interrupt Settings
void fEndOfTransmitCallback(void) {
	bTransmitBusy = false;
}

void fEverySecond(void) {
	iISRLoopCounter++;
	if (bLEDsBlinkingStatusGlobal == ON) {
		fLEDs_TOGGLE();
	}
	if (iISRLoopCounter % 10 == 0) {
		sprintf(mb, "%d\r\n", iISRLoopCounter);
	} else {
		sprintf(mb, "%d ", iISRLoopCounter);
	}
	fMyPrintf(mb);
}

void fLEDs_ON(void) {
	DIGITAL_IO_SetOutputHigh(&LED0);
	DIGITAL_IO_SetOutputHigh(&LED1);
	bLEDsOnOffStatusGlobal = ON;
}

void fLEDs_OFF(void) {
	DIGITAL_IO_SetOutputLow(&LED0);
	DIGITAL_IO_SetOutputLow(&LED1);
	bLEDsOnOffStatusGlobal = OFF;
}

void fLEDs_TOGGLE(void) {
	//const char* myUARTMessage2;
	if (bLEDsOnOffStatusGlobal == ON) {
		fLEDs_OFF();
	} else {
		fLEDs_ON();
	}
	//myUARTMessage2 = "*** LEDs TOGGLED !!! ***\r\n";
	//fMyPrintf(myUARTMessage2);
}

void INT_UART_Receive_ISR(void) {
	uiReceivedCounterGlobal++;
	UART_Receive(&UART_0, &ucUartReceivedDataGlobal, 1);
}

void fMyPrintf(const char* p) {
	const char *helpStartTextPointer = p;
	bTransmitBusy = true; // will be cleared by fEndOfTransmitCallback
	ucStringLength1 = 0;
	ucStringLength2 = strlen(p);

	while (*p) {
		ucStringLength1++;
		*p++;
	}

	if (ucStringLength1 == ucStringLength2) {
		UART_Transmit(&UART_0, (uint8_t*) helpStartTextPointer, ucStringLength2);
	}
}
