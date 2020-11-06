/*
 * Worker4Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker4Task.h"

void vWorker4_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	/* Worker task Loop. */
	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		setByValue(4);

		/* Suspend Task */
		vTaskSuspend(worker4_id);
	}
	/* Should never go there */
	vTaskDelete(worker4_id);
}

