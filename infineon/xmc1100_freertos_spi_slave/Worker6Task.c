/*
 * Worker6Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker6Task.h"

void vWorker6_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		//DIGITAL_IO_ToggleOutput(&LED1);

		/* Suspend Task */
		vTaskSuspend(worker6_id);
		setByValue(6);
	}
	/* Should never go there */
	vTaskDelete(worker6_id);
}
