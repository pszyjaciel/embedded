#include "Worker2Task.h"

// gdy dam 'static' to undefined reference to `worker2_task'
void vWorker2_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	/* Worker task Loop. */
	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		DIGITAL_IO_ToggleOutput(&LED1);
		setByValue(2);
		/* Suspend Task */
		vTaskSuspend(worker2_id);
	}
	/* Should never go there */
	vTaskDelete(worker2_id);
}
