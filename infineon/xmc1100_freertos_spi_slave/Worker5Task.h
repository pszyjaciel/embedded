/*
 * Worker5Task.h
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#ifndef WORKER5TASK_H_
#define WORKER5TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker5_id;
extern void setByValue(uint8_t myValue);

void vWorker5_task(void *pvParameters);

#endif /* WORKER5TASK_H_ */
