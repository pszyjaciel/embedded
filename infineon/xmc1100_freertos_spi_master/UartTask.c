#include "UartTask.h"

/* Here the queue handle is extern. */
extern QueueHandle_t xQueue;
//extern void MyUARTErrorHandler();
//extern void MyLEDsToggling();

uint8_t DataToSend = 0, DataToReceive;
const TickType_t xBlockTime = pdMS_TO_TICKS(100);

/* Block for 500ms. */
const TickType_t xDelay = pdMS_TO_TICKS(500);

// gdy w *.h to przypisanie wartosci do zmiennych wywala
int iMainMenuLoopCounter = 0;
bool bTransmitBusy = true;
uint32_t ucStringLength1 = 0;
uint32_t ucStringLength2 = 0;
char mb[200]; // MessageBuffer for sprintf()

// Receive:
uint8_t ucUartReceivedDataGlobal = '\0';
volatile unsigned int uiReceivedCounterGlobal = 0;
unsigned int uiReceivedCounterOLD_Global = 0;

void MyUARTLEDsToggling(uint8_t tyleRazy) {
	for (int var = 0; var < tyleRazy; ++var) {
		DIGITAL_IO_SetOutputHigh(&LED1);
		vTaskDelay(15);
		DIGITAL_IO_SetOutputLow(&LED1);
		vTaskDelay(15);
	}
}

void MyUARTErrorHandler() {
	MyUARTLEDsToggling(4);
	vTaskDelay(pdMS_TO_TICKS(3500));
}

// pacz UART_0 i Interrupt Settings
void fEndOfTransmitCallback(void) {
	setByValue(3);
	bTransmitBusy = false;
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
		while (bTransmitBusy) {
			vTaskDelay(0); // czekaj asz przyjdzie pszerwanie od UARTa (pacz fEndOfTransmitCallback())
		}
	}
}

void INT_UART_Receive_ISR(void) {
	UART_Receive(&UART_0, &ucUartReceivedDataGlobal, 1);
}

void UART_Task2(void *pvParameters) {
	BaseType_t rs;
	uint8_t myCounter = 1;

	while (1) {
		rs = xQueueReceive(xQueue, &DataToReceive, pdMS_TO_TICKS(200));
		if (rs != pdTRUE) {
			sprintf(mb, "rs:%d; pdTRUE:%d\r\n", (int) rs, (int) pdTRUE);
			fMyPrintf(mb);
			MyUARTErrorHandler();
			continue;  // pomin reszte
		}

		if (myCounter % 32 == 0) {
			sprintf(mb, "r%d\r\n", DataToReceive);
		} else {
			sprintf(mb, "r%d ", DataToReceive);
		}
		fMyPrintf(mb);

		// Write formatted data to string mb
		iMainMenuLoopCounter++;
		if (iMainMenuLoopCounter % 1U == 0) {
			sprintf(mb, "%d\r\n", iMainMenuLoopCounter);
			//fMyPrintf(mb);	// wyslij stringa na linie UART_TX
		}

		// czy w stringu odebranym z UARTa jest 1?
		if (ucUartReceivedDataGlobal == '1') {
			sprintf(mb, "%d\r\n", ucUartReceivedDataGlobal);
			//fMyPrintf(mb);	// wyslij stringa na linie UART_TX
			ucUartReceivedDataGlobal = 0;
		}

		// oscilloscope
		//DIGITAL_IO_SetOutputLow(&VDIOP0_5);
		//DIGITAL_IO_SetOutputHigh(&VDIOP0_0);
		for (int var = 0; var < 50; ++var) {
			asm("nop");
		}
		//DIGITAL_IO_SetOutputLow(&VDIOP0_0);

//		DIGITAL_IO_ToggleOutput(&LED1);
//		xQueueSend(xQueue, &DataToSend, xBlockTime);
		vTaskDelay(xDelay);
		myCounter++;
	}
}

// zrobic taki error handler, ze w zaleznosci od oczszymanego kodu (myReceivedValue)
// wysle na UARTa stringa z opisem tego bledu
void vUART_task(void *pvParameters) {
	uint32_t myReceivedValue = 0;
	BaseType_t bt;
	while (true) {
		bt = xQueueReceive(Queue_id, &myReceivedValue, 0);
		if (bt != pdTRUE) {
			taskYIELD();
			continue;
		}

		if (myReceivedValue % 10 == 0) {
			sprintf(mb, "%d\r\n", (int) myReceivedValue);	// dodaj nowom linie
		} else {
			sprintf(mb, "%d ", (int) myReceivedValue);
		}
		fMyPrintf(mb);	// wyslij stringa na linie UART_TX
		setByValue(2);

		//taskYIELD();
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	/* Should never go there */
	vTaskDelete(UARTHandle_id);
}
