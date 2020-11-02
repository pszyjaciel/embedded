#include "ManagerTask.h"
extern xSemaphoreHandle notification_semaphore;
extern xTaskHandle worker1_id;
extern xTaskHandle worker2_id;
extern xQueueHandle Queue_id;

void Manager_Task(void *pvParameters) {

	static uint32_t Delay1 = 60, Delay2 = 20;

	/* Create the notification semaphore and set the initial state. */
	vSemaphoreCreateBinary(notification_semaphore);
	vQueueAddToRegistry(notification_semaphore, "Notification Semaphore");
	xSemaphoreTake(notification_semaphore, 0);	// 0 to xBlockTime

	/* Producer task Loop. */
	while (1) {
		/* Try to take the semaphore. */
		if (xSemaphoreTake(notification_semaphore, 1000)) {
			xQueueSend(Queue_id, &Delay1, 0);
			xQueueSend(Queue_id, &Delay2, 0);
			vTaskResume(worker1_id);
			vTaskResume(worker2_id);
			setByValue(3);
		}
		/* The lock is only released in the Timer callback function
		 * pacz myTimerCallback() w main.c:
		 * xSemaphoreGive(notification_semaphore); */
	}
}
