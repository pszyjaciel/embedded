/*
 * Worker2Task.h
 *
 *  Created on: Oct 25, 2020
 *      Author: arleta
 */

#ifndef WORKER2TASK_H_
#define WORKER2TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker2_id;
extern void setByValue(uint8_t myValue);

void vWorker2_task(void *pvParameters);

#endif /* WORKER2TASK_H_ */
