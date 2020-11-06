/*
 * Worker7Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker7Task.h"

void vWorker7_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		//DIGITAL_IO_ToggleOutput(&LED1);

		/* Suspend Task */
		vTaskSuspend(worker7_id);
		setByValue(7);
	}
	/* Should never go there */
	vTaskDelete(worker7_id);
}
