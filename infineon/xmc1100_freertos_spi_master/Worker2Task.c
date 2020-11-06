#include "Worker2Task.h"

// gdy dam 'static' to undefined reference to `worker2_task'
void vWorker2_task(void *pvParameters) {
	static uint32_t Delay;
	Delay = 0;
	xQueueReceive(Queue_id, &Delay, 100);

	/* Worker task Loop. */
	while (true) {
		DIGITAL_IO_ToggleOutput(&LED1);

		/* Suspend Task */
		vTaskSuspend(worker2_id);
		setByValue(2);
	}
	/* Should never go there */
	vTaskDelete(worker2_id);
}
