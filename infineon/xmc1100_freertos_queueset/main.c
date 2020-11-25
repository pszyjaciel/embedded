// to bedzie dobry pszykuat na odbieranie danych przez UARTa:
// https://microcontrollerslab.com/freertos-queue-set-arduino/

//.. i huj jak zafsze..
// wyglonda jakby sie kolejka zapelniala i huj i wjencej nie pszyjmuje.

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"

/* Define the lengths of the queues that will be added to the queue set. */
#define QUEUE_LENGTH_1		1
#define QUEUE_LENGTH_2		1

/* Define the size of the item to be held by queue 1 and queue 2 respectively.
 The values used here are just for demonstration purposes. */
#define ITEM_SIZE_QUEUE_1	sizeof( uint32_t )
#define ITEM_SIZE_QUEUE_2	sizeof( uint8_t )
#define COMBINED_LENGTH ( QUEUE_LENGTH_1 + QUEUE_LENGTH_2 )

static QueueSetHandle_t xQueueSet;
QueueHandle_t xQueue1, xQueue2;
SemaphoreHandle_t xMutex;

// https://www.freertos.org/Embedded-RTOS-Queues.html
static void myHighPrioTask(void *pvParameters) {
	char myKey;
	BaseType_t bt;

	for (;;) {
		//setByValue(3);
		DIGITAL_IO_SetOutputHigh(&LED0);
		DIGITAL_IO_SetOutputLow(&LED1);

		if (!SEGGER_RTT_HasKey()) {
//			myKey = 0;
//			xQueueSend(xQueue1, &myKey, 0);
//			xQueueSend(xQueue2, &myKey, 0);
			//setByValue(4);
			vTaskDelay(pdMS_TO_TICKS(50));
			//setByValue(0);
			continue;
		}

		myKey = SEGGER_RTT_GetKey();
		if (myKey == 49) {
			bt = xQueueSend(xQueue1, &myKey, 0);
		} else if (myKey == 50) {
			bt = xQueueSend(xQueue2, &myKey, 0);
		}

		vTaskDelay(pdMS_TO_TICKS(100));
		setByValue(0);
	}
}

void vProcessValueFromQueue1(uint32_t xReceivedFromQueue1) {
	//SEGGER_RTT_printf(0, "vProcessValueFromQueue1(): %d\r\n", xReceivedFromQueue1);
	SEGGER_RTT_WriteString(0, "vProcessValueFromQueue1()\r\n");
	setByValue(1);
}

static void myTask1(void *pvParameters) {
	QueueSetMemberHandle_t xActivatedMember;
	uint32_t xReceivedFromQueue1;
	BaseType_t bt;

	while (1) {
		//setByValue(2);
		//xActivatedMember = xQueueSelectFromSet(xQueueSet, 200 / portTICK_PERIOD_MS);
		//xActivatedMember = xQueueSelectFromSet(xQueueSet, 0);
		xActivatedMember = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

		if (xActivatedMember == xQueue1) {
			bt = xQueueReceive(xActivatedMember, &xReceivedFromQueue1, 0);
			if (bt == pdTRUE) {
				vProcessValueFromQueue1(xReceivedFromQueue1);
			}
		}

		DIGITAL_IO_SetOutputLow(&LED0);
		DIGITAL_IO_SetOutputHigh(&LED1);

		//setByValue(0);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

void vProcessValueFromQueue2(uint8_t xReceivedFromQueue2) {
	//SEGGER_RTT_printf(0, "vProcessValueFromQueue2(): %d\r\n", xReceivedFromQueue2);	// wypierdala
	SEGGER_RTT_WriteString(0, "vProcessValueFromQueue2()\r\n");
	setByValue(2);
}

static void myTask2(void *pvParameters) {
	QueueSetMemberHandle_t xActivatedMember;
	uint8_t xReceivedFromQueue2;
	BaseType_t bt;

	while (1) {
		//setByValue(1);
		//xActivatedMember = xQueueSelectFromSet(xQueueSet, 200 / portTICK_PERIOD_MS);
		//xActivatedMember = xQueueSelectFromSet(xQueueSet, 0);
		xActivatedMember = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

		if (xActivatedMember == xQueue2) {
			bt = xQueueReceive(xActivatedMember, &xReceivedFromQueue2, 0);
			if (bt == pdTRUE) {
				vProcessValueFromQueue2(xReceivedFromQueue2);
			}
		}

		//setByValue(0);
		vTaskDelay(pdMS_TO_TICKS(250));
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

	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);		// non-blocking mode
	//SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);		// blocking mode
	SEGGER_RTT_WriteString(0, "###### SEGGER_printf() ######\r\n");

	xQueueSet = xQueueCreateSet(COMBINED_LENGTH);

	/* Create the queues and semaphores that will be contained in the set. */
	xQueue1 = xQueueCreate( QUEUE_LENGTH_1, ITEM_SIZE_QUEUE_1);
	xQueue2 = xQueueCreate( QUEUE_LENGTH_2, ITEM_SIZE_QUEUE_2);

	/* Check everything was created. */
	configASSERT(xQueueSet);
	configASSERT(xQueue1);
	configASSERT(xQueue2);

	xQueueAddToSet(xQueue1, xQueueSet);
	xQueueAddToSet(xQueue2, xQueueSet);

	xMutex = xSemaphoreCreateMutex();
	if (xMutex != NULL) {
		bt = xTaskCreate(myHighPrioTask, "myHighPrioTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myHighPrioTask\r\n");
		}
		bt = xTaskCreate(myTask1, "WRITE_TASK_1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);	// RED
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask1\r\n");
		}
		bt = xTaskCreate(myTask2, "WRITE_TASK_2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);	// BLUE
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask2\r\n");
		}
//		bt = xTaskCreate(myTask3, "WRITE_TASK_3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);	// GREEN
//		if (bt != pdTRUE) {
//			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask3\r\n");
//		}
//		bt = xTaskCreate(myTask4, "WRITE_TASK_4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);// YELLOW
//		if (bt != pdTRUE) {
//			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask4\r\n");
//		}
//		bt = xTaskCreate(myTask5, "WRITE_TASK_5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);// AQUAMARINE
//		if (bt != pdTRUE) {
//			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask5\r\n");
//		}
//		bt = xTaskCreate(myTask6, "WRITE_TASK_6", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);	// WHITE
//		if (bt != pdTRUE) {
//			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask6\r\n");
//		}
	}
	/* Start scheduling. */
	vTaskStartScheduler();

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {

	}
}
