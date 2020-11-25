/*
 * MyUtils.h
 *
 *  Created on: Nov 6, 2020
 *      Author: arleta
 */

#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <DAVE.h>

void MyLEDsToggling(uint8_t tyleRazy);
void setByValue(uint8_t myValue);
void MyErrorHandler(TaskHandle_t myTaskErrorHandle);

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName);
void vApplicationMallocFailedHook();
void vApplicationIdleHook();
void vApplicationTickHook();

#endif /* MYUTILS_H_ */
