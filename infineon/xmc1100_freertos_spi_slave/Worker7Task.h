/*
 * Worker7Task.h
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#ifndef WORKER7TASK_H_
#define WORKER7TASK_H_

#include <DAVE.h>

extern xQueueHandle Queue_id;
extern xTaskHandle worker7_id;
extern void setByValue(uint8_t myValue);

void vWorker7_task(void *pvParameters);

#endif /* WORKER7TASK_H_ */
