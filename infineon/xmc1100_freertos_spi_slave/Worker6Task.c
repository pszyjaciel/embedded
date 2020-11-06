/*
 * Worker6Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker6Task.h"

void vWorker6_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	/* Worker task Loop. */
	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		setByValue(6);

		/* Suspend Task */
		vTaskSuspend(worker6_id);
	}
	/* Should never go there */
	vTaskDelete(worker6_id);
}
