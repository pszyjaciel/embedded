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
	while (true) {
		xSemaphoreTake(xMutex, portMAX_DELAY);

		//xQueueSend(counterQueue, &myCounter, 0);
		xQueueSend(Queue_id, &myCounter, 0);

		myCounter++;
		if (myCounter > 16) {
			myCounter = 0;
		}
		setByValue(0);
		xSemaphoreGive(xMutex);
		taskYIELD();
	}
	/* Should never go there */
	vTaskDelete(worker1_id);
}

void vWorker2_task(void *pvParameters) {
	//uint8_t myCounter;
	while (true) {
		xSemaphoreTake(xMutex, portMAX_DELAY);
		//xQueueReceive(Queue_id, &myCounter, 0);
		//setByValue(myCounter);

		setByValue(1);
		xSemaphoreGive(xMutex);
		taskYIELD();
	}
	/* Should never go there */
	vTaskDelete(worker2_id);
}
