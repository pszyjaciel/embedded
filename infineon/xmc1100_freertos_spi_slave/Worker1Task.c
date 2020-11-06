#include "Worker1Task.h"

void vWorker1_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);
	/* Worker task Loop. */
	while (true) {
		/* Simulate work */
//		for (idelay = 0; idelay < Delay; ++idelay) {
			DIGITAL_IO_ToggleOutput(&LED0);
			setByValue(1);
//		}
		/* Suspend Task */
		vTaskSuspend(worker1_id);
	}
	/* Should never go there */
	vTaskDelete(worker1_id);
}
