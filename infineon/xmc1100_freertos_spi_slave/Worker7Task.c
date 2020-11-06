/*
 * Worker7Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker7Task.h"

void vWorker7_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	/* Worker task Loop. */
	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		setByValue(7);

		/* Suspend Task */
		vTaskSuspend(worker7_id);
	}
	/* Should never go there */
	vTaskDelete(worker7_id);
}
