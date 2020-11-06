/*
 * Worker3Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker3Task.h"

// gdy dam 'static' to undefined reference to `worker2_task'
void vWorker3_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		/* Suspend Task */
		setByValue(3);

		vTaskSuspend(worker3_id);
	}
	/* Should never go there */
	vTaskDelete(worker3_id);
}
