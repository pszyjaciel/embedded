#ifndef MANAGERTASK_H_
#define MANAGERTASK_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

extern xSemaphoreHandle notification_semaphore;
extern xTaskHandle worker1_id;
extern xTaskHandle worker2_id;
extern xTaskHandle UARTHandle;
extern xQueueHandle Queue_id;
extern void setByValue(uint8_t myValue);

void vManager_Task(void *pvParameters);

#endif /* MANAGERTASK_H_ */
