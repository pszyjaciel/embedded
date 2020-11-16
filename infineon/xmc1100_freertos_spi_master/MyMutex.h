/*
 * MyMutex.h
 *
 *  Created on: Nov 13, 2020
 *      Author: arleta
 */

// stont:
// https://github.com/iotexpert/PSoC-FreeRTOS-Examples/blob/master/3-Queue.cydsn/main.c
// https://community.nxp.com/t5/MQX-Software-Solutions-Knowledge/How-to-use-mutex-and-semaphores-in-a-FreeRTOS-and-SDK2-0-Project/ta-p/1114196

#ifndef MYMUTEX_H_
#define MYMUTEX_H_

#include <DAVE.h>
#include "MyUtils.h"

extern xTaskHandle worker1_id;
extern xTaskHandle worker2_id;
extern SemaphoreHandle_t xMutex;
extern QueueHandle_t counterQueue;
extern QueueHandle_t Queue_id;

void vWorker1_task(void *pvParameters);
void vWorker2_task(void *pvParameters);

#endif /* MYMUTEX_H_ */
