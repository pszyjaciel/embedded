#ifndef MANAGERTASK_H_
#define MANAGERTASK_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

extern xSemaphoreHandle notification_semaphore;
extern xTaskHandle worker1_id;
extern xTaskHandle worker2_id;
extern xTaskHandle worker3_id;
extern xTaskHandle worker4_id;
extern xTaskHandle worker5_id;
extern xTaskHandle worker6_id;
extern xTaskHandle worker7_id;

extern xTaskHandle UARTHandle_id;
extern xQueueHandle Queue_id;


extern void setByValue(uint8_t myValue);

void vManager_Task(void *pvParameters);

#endif /* MANAGERTASK_H_ */
