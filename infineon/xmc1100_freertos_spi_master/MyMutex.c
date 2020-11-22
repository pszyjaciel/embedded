/*
 * MyMutex.c
 *
 *  Created on: Nov 13, 2020
 *      Author: arleta
 */
#include "MyMutex.h"

// A mutex can be “taken” by one thread before doing a critical operation (like writing a message)
// and if any other thread wants to take the same mutex, it will have to wait until the first one releases it.

void vWorker1_task(void *pvParameters) {
	uint8_t myCounter = 0;
	BaseType_t bt;
	while (true) {
		SEGGER_RTT_printf(0, "vWorker1_task: pszet \r\n");
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		SEGGER_RTT_printf(0, "vWorker1_task:xSemaphoreTake(): %d \r\n", bt);
		if (bt != pdTRUE) {
			vTaskDelay(pdMS_TO_TICKS(50));
		}

		//xQueueSend(counterQueue, &myCounter, 0);
		bt = xQueueSend(Queue_id, &myCounter, 0);
		if (bt != pdTRUE) {
			vTaskDelay(pdMS_TO_TICKS(50));
		}
		SEGGER_RTT_printf(0, "vWorker1_task:xQueueSend(): %d \r\n", bt);

		myCounter++;
		if (myCounter > 16) {
			myCounter = 0;
		}
		setByValue(0);
		bt = xSemaphoreGive(xMutex);
		SEGGER_RTT_printf(0, "vWorker1_task:xSemaphoreGive(): %d \r\n", bt);

		SEGGER_RTT_printf(0, "vWorker1_task: ipo \r\n");
		vTaskDelay(pdMS_TO_TICKS(50));
		//taskYIELD();
	}
	/* Should never go there */
	vTaskDelete(worker1_id);
}

void vWorker2_task(void *pvParameters) {
	//uint8_t myCounter;
	BaseType_t bt;
	while (true) {
		SEGGER_RTT_printf(0, "vWorker2_task: pszet \r\n");
		bt = xSemaphoreTake(xMutex, portMAX_DELAY);
		SEGGER_RTT_printf(0, "vWorker2_task:xSemaphoreTake(): %d \r\n", bt);

		//xQueueReceive(Queue_id, &myCounter, 0);
		//setByValue(myCounter);

		setByValue(1);
		bt = xSemaphoreGive(xMutex);
		SEGGER_RTT_printf(0, "vWorker2_task:xSemaphoreGive(): %d \r\n", bt);

		SEGGER_RTT_printf(0, "vWorker2_task: ipo \r\n");
		vTaskDelay(pdMS_TO_TICKS(40));
		//taskYIELD();
	}
	/* Should never go there */
	vTaskDelete(worker2_id);
}
