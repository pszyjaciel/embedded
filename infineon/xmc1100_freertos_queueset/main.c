// to bedzie dobry pszykuat na odbieranie danych przez UARTa:
// https://microcontrollerslab.com/freertos-queue-set-arduino/

// eclipse problem with jlink:
// https://eclipse-embed-cdt.github.io/debug/jlink/

// C:\!Lenovo\cp\DAVE-IDE-4.4.2-64Bit\eclipse\ARM-GCC-49/bin/arm-none-eabi-gdb --interpreter=mi2 --nx
// "C:\Program Files (x86)\SEGGER\JLink\JLinkGDBServerCL.exe" -if swd -device XMC1100-Q024x0064 -endian little -speed 1000 -port 2331 -swoport 2332 -telnetport 2333 -vd -ir -localhostonly 1 -singlerun -strict -timeout 0

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "UartTask.h"

/* Define the lengths of the queues that will be added to the queue set. */
#define QUEUE_LENGTH_1		1
#define QUEUE_LENGTH_2		1
#define QUEUE_LENGTH_3		1
#define QUEUE_LENGTH_4		1

/* Define the size of the item to be held by queue 1 and queue 2 respectively.
 The values used here are just for demonstration purposes. */
#define ITEM_SIZE_QUEUE_1	sizeof( uint8_t )
#define ITEM_SIZE_QUEUE_2	sizeof( uint8_t )
#define ITEM_SIZE_QUEUE_3	sizeof( uint8_t )
#define ITEM_SIZE_QUEUE_4	sizeof( uint8_t )
#define COMBINED_LENGTH ( QUEUE_LENGTH_1 + QUEUE_LENGTH_2 + QUEUE_LENGTH_3 + QUEUE_LENGTH_4 )

QueueSetHandle_t xQueueSet;
QueueHandle_t xQueue1, xQueue2, xQueue3, xQueue4, xQueue5;

static void myTask1(void *pvParameters) {

	uint8_t myKey;
	BaseType_t bt;

	myKey = 0x20;
	while (1) {
		//setByValue(2);
		DIGITAL_IO_SetOutputLow(&LED0);
		DIGITAL_IO_SetOutputHigh(&LED1);

		if (myKey < 0x01) {
			myKey = 0x20;
		}
		bt = xQueueSend(xQueue1, &myKey, 0);
		if (bt == pdTRUE) {
			myKey--;
		}
		//setByValue(0);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

static void myTask2(void *pvParameters) {
	uint8_t myKey;
	BaseType_t bt;

	myKey = 0x40;
	while (1) {

		if (myKey > 0x60) {
			myKey = 0x40;
		}
		bt = xQueueSend(xQueue2, &myKey, 0);
		if (bt == pdTRUE) {
			myKey++;
		}

		vTaskDelay(pdMS_TO_TICKS(20));
	}
}

static void myTask3(void *pvParameters) {
	uint8_t myKey;
	BaseType_t bt;

	myKey = 0x80;
	while (1) {

		if (myKey < 0x60) {
			myKey = 0x80;
		}
		bt = xQueueSend(xQueue3, &myKey, 0);
		if (bt == pdTRUE) {
			myKey--;
		}
		vTaskDelay(pdMS_TO_TICKS(15));
	}
}

static void myTask4(void *pvParameters) {
	uint8_t myKey;
	BaseType_t bt;

	myKey = 0x80;
	while (1) {
		if (myKey > 0xa0) {
			myKey = 0x80;
		}
		bt = xQueueSend(xQueue4, &myKey, 0);
		if (bt == pdTRUE) {
			myKey++;
		}
		vTaskDelay(pdMS_TO_TICKS(25));
	}
}

int main(void) {
	BaseType_t bt;
	DAVE_STATUS_t status;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");
		while (1U) {

		}
	}

	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);	// non-blocking mode
	//SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);		// blocking mode
	SEGGER_RTT_WriteString(0, "###### SEGGER_printf() ######\r\n");

	xQueueSet = xQueueCreateSet(COMBINED_LENGTH);

	/* Create the queues and semaphores that will be contained in the set. */
	xQueue1 = xQueueCreate(QUEUE_LENGTH_1, ITEM_SIZE_QUEUE_1);
	xQueue2 = xQueueCreate(QUEUE_LENGTH_2, ITEM_SIZE_QUEUE_2);
	xQueue3 = xQueueCreate(QUEUE_LENGTH_3, ITEM_SIZE_QUEUE_3);
	xQueue4 = xQueueCreate(QUEUE_LENGTH_4, ITEM_SIZE_QUEUE_4);

	char myCharQueue[20] = "";
	xQueue5 = xQueueCreate(1, sizeof(myCharQueue));

	/* Check everything was created. */
	//configASSERT(xQueueSet);	// to makro to wielka hujnia
	//configASSERT(xQueue1);
	//configASSERT(xQueue2);
	xQueueAddToSet(xQueue1, xQueueSet);
	xQueueAddToSet(xQueue2, xQueueSet);
	xQueueAddToSet(xQueue3, xQueueSet);
	xQueueAddToSet(xQueue4, xQueueSet);

	bt = xTaskCreate(myUARTTask, "myUARTTask", configMINIMAL_STACK_SIZE, NULL,
			tskIDLE_PRIORITY + 1, NULL);
	if (bt != pdTRUE) {
		SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myHighPrioTask\r\n");
	}
	bt = xTaskCreate(myTask1, "WRITE_TASK_1", configMINIMAL_STACK_SIZE, NULL,
			tskIDLE_PRIORITY + 2, NULL);	// RED
	if (bt != pdTRUE) {
		SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask1\r\n");
	}
	bt = xTaskCreate(myTask2, "WRITE_TASK_2", configMINIMAL_STACK_SIZE, NULL,
			tskIDLE_PRIORITY + 2, NULL);	// BLUE
	if (bt != pdTRUE) {
		SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask2\r\n");
	}
	bt = xTaskCreate(myTask3, "WRITE_TASK_3", configMINIMAL_STACK_SIZE, NULL,
			tskIDLE_PRIORITY + 2, NULL);	// GREEN
	if (bt != pdTRUE) {
		SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask3\r\n");
	}
	bt = xTaskCreate(myTask4, "WRITE_TASK_4", configMINIMAL_STACK_SIZE, NULL,
			tskIDLE_PRIORITY + 2, NULL);	// YELLOW
	if (bt != pdTRUE) {
		SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask4\r\n");
	}

	/* Start scheduling. */
	vTaskStartScheduler();

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {

	}
}
