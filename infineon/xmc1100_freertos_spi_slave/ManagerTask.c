#include "ManagerTask.h"


void vManager_Task(void *pvParameters) {

	static uint32_t Delay1 = 0xa5, Delay2 = 20;
	static uint32_t someValue = 120;

	/* Create the notification semaphore and set the initial state. */
	vSemaphoreCreateBinary(notification_semaphore);
	vQueueAddToRegistry(notification_semaphore, "Notification Semaphore");
	xSemaphoreTake(notification_semaphore, 0);	// 0 to xBlockTime

	/* Producer task Loop. */
	while (1) {
		/* Try to take the semaphore. */
		if (xSemaphoreTake(notification_semaphore, 1000)) {
			xQueueSend(Queue_id, &Delay1, 0);
			vTaskResume(worker1_id);
			xQueueSend(Queue_id, &Delay2, 0);
			vTaskResume(worker2_id);

			someValue++;
			xQueueSend(Queue_id, &someValue, 0);
			vTaskResume(UARTHandle);

			setByValue(3);
		}
		/* The lock is only released in the Timer callback function
		 * pacz myTimerCallback() w main.c:
		 * xSemaphoreGive(notification_semaphore); */
	}
}
