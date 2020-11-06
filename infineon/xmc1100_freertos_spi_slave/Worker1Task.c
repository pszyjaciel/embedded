#include "Worker1Task.h"

void vWorker1_task(void *pvParameters) {
	static uint32_t receivedFromQueue;

	/* Worker task Loop. */
	while (true) {
		xQueueReceive(Queue_id, &receivedFromQueue, 100);
		receivedFromQueue++;
		xQueueSend(Queue_id, &receivedFromQueue, 0);

		DIGITAL_IO_ToggleOutput(&LED0);
		setByValue(1);

		/* Suspend Task */
		vTaskSuspend(worker1_id);
	}
	/* Should never go there */
	vTaskDelete(worker1_id);
}
