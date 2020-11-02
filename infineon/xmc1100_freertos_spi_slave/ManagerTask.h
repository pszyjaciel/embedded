#ifndef MANAGERTASK_H_
#define MANAGERTASK_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

extern void setByValue(uint8_t myValue);

void Manager_Task(void *pvParameters);

#endif /* MANAGERTASK_H_ */
