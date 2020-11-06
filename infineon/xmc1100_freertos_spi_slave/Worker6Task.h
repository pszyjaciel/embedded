/*
 * Worker6Task.h
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#ifndef WORKER6TASK_H_
#define WORKER6TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker6_id;
extern void setByValue(uint8_t myValue);

void vWorker6_task(void *pvParameters);

#endif /* WORKER6TASK_H_ */
