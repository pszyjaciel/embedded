#include "ManagerTask.h"


void vManager_Task(void *pvParameters) {

// jak dziala komunikacja mjendzy taskami?

	static uint32_t someValue = 120;

	/* Create the notification semaphore and set the initial state. */
	// we will use a semaphore in order to synchronize a “Manager task”
	// with the previously created timer.
	vSemaphoreCreateBinary(notification_semaphore);
	vQueueAddToRegistry(notification_semaphore, "Notification Semaphore");	// nie istotny drugi parametr
	xSemaphoreTake(notification_semaphore, 0);	// 0 to xBlockTime

	/* Producer task Loop. */
	while (1) {
		/* Try to take the semaphore. */
		// pacz Macro to release a semaphore xSemaphoreGive(notification_semaphore)
		// w myTimerCallback(xTimerHandle pxTimer) w pliku main.c

		if (xSemaphoreTake(notification_semaphore, 1000)) {
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker1_id);
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker2_id);
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker3_id);
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker4_id);
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker5_id);
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker6_id);
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(worker7_id);

			someValue++;
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(UARTHandle_id);

			setByValue(9);
		}
		/* The lock is only released in the Timer callback function
		 * pacz myTimerCallback() w main.c:
		 * xSemaphoreGive(notification_semaphore); */
	}
}
