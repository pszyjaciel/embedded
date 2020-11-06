/*
 * Worker3Task.c
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#include "Worker3Task.h"

// gdy dam 'static' to undefined reference to `worker2_task'
void vWorker3_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		//DIGITAL_IO_ToggleOutput(&LED1);

		/* Suspend Task */
		vTaskSuspend(worker3_id);
		setByValue(3);
	}
	/* Should never go there */
	vTaskDelete(worker3_id);
}
