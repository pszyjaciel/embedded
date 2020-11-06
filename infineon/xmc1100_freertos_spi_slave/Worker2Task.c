#include "Worker2Task.h"

// gdy dam 'static' to undefined reference to `worker2_task'
void vWorker2_task(void *pvParameters) {
	static uint32_t idelay, Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		/* Simulate CPU work */
		for (idelay = 0; idelay < Delay; ++idelay) {
			DIGITAL_IO_ToggleOutput(&LED1);
			setByValue(2);
		}
		/* Suspend Task */
		vTaskSuspend(worker2_id);
	}
	/* Should never go there */
	vTaskDelete(worker2_id);
}
