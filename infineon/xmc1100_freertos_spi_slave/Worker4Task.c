/*
 * Worker4Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker4Task.h"

void vWorker4_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		//DIGITAL_IO_ToggleOutput(&LED1);

		/* Suspend Task */
		vTaskSuspend(worker4_id);
		setByValue(4);
	}
	/* Should never go there */
	vTaskDelete(worker4_id);
}

