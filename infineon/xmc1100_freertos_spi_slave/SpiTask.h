
#ifndef SPITASK_H_
#define SPITASK_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#define DATA_COUNT 8

void SPI_Slave_Task(void *pvParameters);

#endif /* SPITASK_H_ */
