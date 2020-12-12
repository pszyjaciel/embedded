#ifndef UARTTASK_H_
#define UARTTASK_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include "MyUtils.h"

//unsigned int uiReceivedCounterOLD_Global = 0;
//./main.o:(.bss.uiReceivedCounterOLD_Global+0x0): multiple definition of `uiReceivedCounterOLD_Global'
//./UartTask.o:(.bss.uiReceivedCounterOLD_Global+0x0): first defined here
//collect2.exe: error: ld returned 1 exit status
//makefile:63: recipe for target 'xmc1100_freertos_spi_slave.elf' failed
//make: *** [xmc1100_freertos_spi_slave.elf] Error 1

extern xTaskHandle UARTHandle_id;
extern xQueueHandle Queue_id;
extern void setByValue(uint8_t myValue);
extern QueueSetHandle_t xQueueSet;
extern QueueHandle_t xQueue1, xQueue2, xQueue3, xQueue4, xQueue5;

// Transmit:
//void fMyPrintf(const char* p);
void fEndOfTransmitCallback(void);

//void vUART_Task(void *pvParameters);
void myUARTTask(void *pvParameters);

#endif /* UARTTASK_H_ */
