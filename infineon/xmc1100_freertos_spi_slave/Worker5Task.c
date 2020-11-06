/*
 * Worker5Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker5Task.h"

void vWorker5_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		//DIGITAL_IO_ToggleOutput(&LED1);

		/* Suspend Task */
		vTaskSuspend(worker5_id);
		setByValue(5);
	}
	/* Should never go there */
	vTaskDelete(worker5_id);
}
