#ifndef WORKER1TASK_H_
#define WORKER1TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker1_id;

void worker1_task(void *pvParameters);


#endif /* WORKER1TASK_H_ */
