/*
 * Worker3Task.h
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#ifndef WORKER3TASK_H_
#define WORKER3TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker3_id;
extern void setByValue(uint8_t myValue);

void vWorker3_task(void *pvParameters);

#endif /* WORKER3TASK_H_ */
