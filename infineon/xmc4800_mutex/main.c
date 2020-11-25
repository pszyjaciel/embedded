/*
 * main.c
 *
 *  Created on: 2020 Nov 25 10:13:33
 *  Author: PKR
 *  na podstawie tego:
 *  https://community.nxp.com/t5/MQX-Software-Solutions-Knowledge/How-to-use-mutex-and-semaphores-in-a-FreeRTOS-and-SDK2-0-Project/ta-p/1114196
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

SemaphoreHandle_t xMutex;

void myCommonFunction(const char* mySztrink) {
	SEGGER_RTT_printf(0, "myCommonFunction(): %s\r\n", mySztrink);
	vTaskDelay(pdMS_TO_TICKS(1000));
}

static void write_task_1(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "write_task_1: bt != pdTRUE\r\n");
		}
		DIGITAL_IO_SetOutputLow(&RED_LED);		// swieci czerwona
		DIGITAL_IO_SetOutputHigh(&BLUE_LED);
		DIGITAL_IO_SetOutputHigh(&GREEN_LED);
		myCommonFunction("RED from task [1]");

		xSemaphoreGive(xMutex);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

static void write_task_2(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "write_task_2: bt != pdTRUE\r\n");
		}
		DIGITAL_IO_SetOutputLow(&BLUE_LED);	// swieci niebieska
		DIGITAL_IO_SetOutputHigh(&RED_LED);
		DIGITAL_IO_SetOutputHigh(&GREEN_LED);
		myCommonFunction("BLUE from task [2]");

		xSemaphoreGive(xMutex);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

static void write_task_3(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "write_task_3: bt != pdTRUE\r\n");
		}
		DIGITAL_IO_SetOutputHigh(&BLUE_LED);
		DIGITAL_IO_SetOutputHigh(&RED_LED);
		DIGITAL_IO_SetOutputLow(&GREEN_LED);	// swieci zielona
		myCommonFunction("GREEN from task [3]");
		xSemaphoreGive(xMutex);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

static void write_task_4(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "write_task_4: bt != pdTRUE\r\n");
		}
		DIGITAL_IO_SetOutputHigh(&BLUE_LED);	// swieci niebieska
		DIGITAL_IO_SetOutputLow(&RED_LED);		// swieci czerwona
		DIGITAL_IO_SetOutputLow(&GREEN_LED);
		myCommonFunction("YELLOW from task [4]");
		xSemaphoreGive(xMutex);
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}

static void write_task_5(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "write_task_5: bt != pdTRUE\r\n");
		}
		DIGITAL_IO_SetOutputLow(&BLUE_LED);		// swieci niebieska
		DIGITAL_IO_SetOutputHigh(&RED_LED);
		DIGITAL_IO_SetOutputLow(&GREEN_LED);	// swieci zielona
		myCommonFunction("AQUAMARINE from task [5]");
		xSemaphoreGive(xMutex);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

static void write_task_6(void *pvParameters) {
	BaseType_t bt;
	while (1) {
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "write_task_6: bt != pdTRUE\r\n");
		}
		DIGITAL_IO_SetOutputLow(&BLUE_LED);		// swieci niebieska
		DIGITAL_IO_SetOutputLow(&RED_LED);		// swieci czerwona
		DIGITAL_IO_SetOutputLow(&GREEN_LED);	// swieci zielona
		myCommonFunction("WHITE from task [6]");
		xSemaphoreGive(xMutex);
		vTaskDelay(pdMS_TO_TICKS(100));
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

	SEGGER_RTT_Init();
	//SEGGER_RTT_ConfigUpBuffer(0, NULL, pSeggerBuffer, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);		// blocking mode
	SEGGER_RTT_WriteString(0, "###### SEGGER_printf() ######\r\n");

	xMutex = xSemaphoreCreateMutex();
	if (xMutex != NULL) {
		bt = xTaskCreate(write_task_1, "WRITE_TASK_1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, NULL);	// RED
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for write_task_1\r\n");
		}
		bt = xTaskCreate(write_task_2, "WRITE_TASK_2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, NULL);	// BLUE
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for write_task_2\r\n");
		}
		bt = xTaskCreate(write_task_3, "WRITE_TASK_3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, NULL);	// GREEN
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for write_task_3\r\n");
		}
		bt = xTaskCreate(write_task_4, "WRITE_TASK_4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, NULL);	// YELLOW
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for write_task_4\r\n");
		}
		bt = xTaskCreate(write_task_5, "WRITE_TASK_5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, NULL);	// AQUAMARINE
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for write_task_5\r\n");
		}
		bt = xTaskCreate(write_task_6, "WRITE_TASK_6", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 6, NULL);	// WHITE
		if (bt != pdTRUE) {
			SEGGER_RTT_printf(0, "main(): bt != pdTRUE for write_task_6\r\n");
		}
	}
	/* Start scheduling. */
	vTaskStartScheduler();

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {

	}
}
