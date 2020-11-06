/*
 * Worker5Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker5Task.h"

void vWorker5_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	/* Worker task Loop. */
	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		setByValue(5);

		/* Suspend Task */
		vTaskSuspend(worker5_id);
	}
	/* Should never go there */
	vTaskDelete(worker5_id);
}
