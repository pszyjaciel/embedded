/*
 * Worker4Task.h
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#ifndef WORKER4TASK_H_
#define WORKER4TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker4_id;
extern void setByValue(uint8_t myValue);

void vWorker4_task(void *pvParameters);

#endif /* WORKER4TASK_H_ */
