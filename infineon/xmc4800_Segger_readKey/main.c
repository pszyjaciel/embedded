/*
 * main.c
 *
 *  Created on: 2020 Nov 25 10:13:33
 *  Author: PKR
 *  na podstawie tego:
 *  https://community.nxp.com/t5/MQX-Software-Solutions-Knowledge/How-to-use-mutex-and-semaphores-in-a-FreeRTOS-and-SDK2-0-Project/ta-p/1114196

sie wydaje rze hiba ten pszykuat bedzie otpowjedni: https://www.freertos.org/xQueueCreateSet.html
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>

SemaphoreHandle_t xMutex;
QueueHandle_t Queue_id;

void myCommonFunction(const char* mySztrink) {
	SEGGER_RTT_printf(0, "myCommonFunction(): %s\r\n", mySztrink);
	vTaskDelay(pdMS_TO_TICKS(500));
	//SEGGER_RTT_printf(0, "EXIT from myCommonFunction()\r\n");
}

// nie moze blokowac!
char myReadKey() {
	char myKey = 0;

//	myKey = SEGGER_RTT_WaitKey();
//	do {
//		vTaskDelay(pdMS_TO_TICKS(0));
//	} while (myKey != '1');

	if (!SEGGER_RTT_HasKey()) {
		return -1;
	}

	myKey = SEGGER_RTT_GetKey();
	return myKey;
}

// https://www.freertos.org/Embedded-RTOS-Queues.html
static void myHighPrioTask(void *pvParameters) {
	BaseType_t bt;
	char myKey;

	while (1) {
		if (!SEGGER_RTT_HasKey()) {
			vTaskDelay(pdMS_TO_TICKS(50));
		}

		myKey = SEGGER_RTT_GetKey();
		bt = xQueueSend(Queue_id, &myKey, 0);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "myHighPrioTask: xQueueSend(): bt != pdTRUE\r\n");
			vTaskDelay(pdMS_TO_TICKS(500));
		}
	}
}

// w zaleznosci od wcisnietego klawisza zapalic odpowiedniom djode
static void myTask1(void *pvParameters) {
	BaseType_t bt;
	char myKey;

	while (1) {
		bt = xSemaphoreTake(xMutex, (TickType_t ) 0);
		if (bt != pdTRUE) {
			continue;		// nie dostal semafora wjenc pomin reszte kodu i jedziesz od poczontku
		}
		DIGITAL_IO_SetOutputLow(&RED_LED);		// RED
		DIGITAL_IO_SetOutputHigh(&BLUE_LED);
		DIGITAL_IO_SetOutputHigh(&GREEN_LED);

		xQueueReceive(Queue_id, &myKey, 200);
		if (myKey == 49) {
			SEGGER_RTT_printf(0, "debuggingEnabled = 0x01\r\n");
		}
		else {
			//xQueueSend(Queue_id, &myKey, 0);	// it's not my key!
		}

		bt = xSemaphoreGive(xMutex);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "Sem[T1] not given\r\n");
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

static void myTask2(void *pvParameters) {
	BaseType_t bt;
	char myKey;

	while (1) {
		bt = xSemaphoreTake(xMutex, (TickType_t ) 0);
		if (bt != pdTRUE) {
			continue;
		}
		DIGITAL_IO_SetOutputLow(&BLUE_LED);	// BLUE
		DIGITAL_IO_SetOutputHigh(&RED_LED);
		DIGITAL_IO_SetOutputHigh(&GREEN_LED);

		//myKey = myReadKey();
		xQueueReceive(Queue_id, &myKey, 200);
		if (myKey == 50) {
			SEGGER_RTT_printf(0, "debuggingEnabled = 0x02\r\n");
		}
		else {
			//xQueueSend(Queue_id, &myKey, 0);	// it's not my key!
		}


		bt = xSemaphoreGive(xMutex);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "Sem[T2] not given\r\n");
		}
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

static void myTask3(void *pvParameters) {
	BaseType_t bt;
	char myKey;

	while (1) {
		bt = xSemaphoreTake(xMutex, (TickType_t ) 0);
		if (bt != pdTRUE) {
			continue;
		}
		DIGITAL_IO_SetOutputHigh(&BLUE_LED);
		DIGITAL_IO_SetOutputHigh(&RED_LED);
		DIGITAL_IO_SetOutputLow(&GREEN_LED);	// GREEN

		//myKey = myReadKey();
		xQueueReceive(Queue_id, &myKey, 200);
		if (myKey == 51) {
			SEGGER_RTT_printf(0, "debuggingEnabled = 0x03\r\n");
		}
		else {
			//xQueueSend(Queue_id, &myKey, 0);	// it's not my key!
		}


		bt = xSemaphoreGive(xMutex);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "Sem[T3] not given\r\n");
		}
		vTaskDelay(pdMS_TO_TICKS(300));
	}
}

static void myTask4(void *pvParameters) {
	BaseType_t bt;
	char myKey;

	while (1) {
		bt = xSemaphoreTake(xMutex, (TickType_t ) 0);
		if (bt != pdTRUE) {
			continue;
		}
		DIGITAL_IO_SetOutputHigh(&BLUE_LED);	// swieci niebieska
		DIGITAL_IO_SetOutputLow(&RED_LED);		// swieci czerwona
		DIGITAL_IO_SetOutputLow(&GREEN_LED);

		//myKey = myReadKey();
		xQueueReceive(Queue_id, &myKey, 200);
		if (myKey == 52) {
			SEGGER_RTT_printf(0, "debuggingEnabled = 0x04\r\n");
		}
		else {
			//xQueueSend(Queue_id, &myKey, 0);	// it's not my key!
		}

		bt = xSemaphoreGive(xMutex);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "Sem[T4] not given\r\n");
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

static void myTask5(void *pvParameters) {
	BaseType_t bt;
	char myKey;

	while (1) {
		bt = xSemaphoreTake(xMutex, (TickType_t ) 0);
		if (bt != pdTRUE) {
			continue;
		}
		DIGITAL_IO_SetOutputLow(&BLUE_LED);		// swieci niebieska
		DIGITAL_IO_SetOutputHigh(&RED_LED);
		DIGITAL_IO_SetOutputLow(&GREEN_LED);	// swieci zielona
		//myCommonFunction("AQUAMARINE from task [5]");

		//myKey = myReadKey();
		xQueueReceive(Queue_id, &myKey, 200);
		if (myKey == 53) {
			SEGGER_RTT_printf(0, "debuggingEnabled = 0x05\r\n");
		}
		else {
			//xQueueSend(Queue_id, &myKey, 0);	// it's not my key!
		}

		bt = xSemaphoreGive(xMutex);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "Sem[T5] not given\r\n");
		}
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

static void myTask6(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		//bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		bt = xSemaphoreTake(xMutex, (TickType_t ) 0);
		if (bt != pdTRUE) {
			continue;
		}
		DIGITAL_IO_SetOutputLow(&BLUE_LED);		// swieci niebieska
		DIGITAL_IO_SetOutputLow(&RED_LED);		// swieci czerwona
		DIGITAL_IO_SetOutputLow(&GREEN_LED);	// swieci zielona
		//myCommonFunction("WHITE from task [6]");

		bt = xSemaphoreGive(xMutex);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "Sem[T6] not given\r\n");
		}
		vTaskDelay(pdMS_TO_TICKS(1175));
	}
}

int main(void) {
	DAVE_STATUS_t status;
	BaseType_t bt;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");
		while (1U) {
			;
		}
	}

	//SEGGER_RTT_Init();
	//SEGGER_RTT_ConfigUpBuffer(0, NULL, pSeggerBuffer, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);		// blocking mode
	SEGGER_RTT_WriteString(0, "###### SEGGER_printf() ######\r\n");

	Queue_id = xQueueCreate(1, sizeof(uint8_t));
	SEGGER_RTT_printf(0, "xQueueCreate(): %d \r\n", Queue_id);

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
		bt = xTaskCreate(myTask3, "WRITE_TASK_3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);	// GREEN
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask3\r\n");
		}
		bt = xTaskCreate(myTask4, "WRITE_TASK_4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);// YELLOW
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask4\r\n");
		}
		bt = xTaskCreate(myTask5, "WRITE_TASK_5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);// AQUAMARINE
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask5\r\n");
		}
		bt = xTaskCreate(myTask6, "WRITE_TASK_6", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);	// WHITE
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for myTask6\r\n");
		}
	}
	/* Start scheduling. */
	vTaskStartScheduler();

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {

	}
}
