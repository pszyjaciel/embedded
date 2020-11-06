// SN 591096897 (slave) piny pionowe prostopadle do plytki

// (!)http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42247-Introduction-to-Basic%20RTOS-Features-using-SAM4L-EK-FreeRTOS-Port_Training-Manual.pdf

//USE_PREEMPTION:
//Kernel will be used in Preemption mode which means that task with lower priority can be
//interrupted by task with higher priority.
//• USE_IDLE_HOOK:
//An idle task will be created at scheduler start-up. This task has the lowest priority level possible. It
//will help us analyze when the CPU has no task to execute.
//• USE_TRACE_FACILITY:
//Enable Kernel Trace function for FreeRTOS+Trace Analyzer.

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"
#include "ManagerTask.h"
#include "UartTask.h"
#include "SpiTask.h"
#include "Worker1Task.h"
#include "Worker2Task.h"

/* Declared globally. */
QueueHandle_t xQueue = NULL;
xQueueHandle Queue_id;
xSemaphoreHandle notification_semaphore;
xTimerHandle Timer_handle;
xTaskHandle UARTHandle = NULL;
xTaskHandle SPIHandle = NULL;
xTaskHandle worker1_id;
xTaskHandle worker2_id;

typedef struct parameter_struct {
	const char Parameter1;
	const uint32_t Parameter2;
/*...*/
} parameter_struct_t;

typedef struct SEMAPHORE_PARAMETERS {
	xSemaphoreHandle xSemaphore;
	volatile unsigned long *pulSharedVariable;
	portTickType xBlockTime;
} xSemaphoreParameters_t;


void MyErrorHandler(TaskHandle_t xUARTHandle) {
	if (xUARTHandle != NULL) {
		vTaskDelete(xUARTHandle);
	}

	while (true) {
		MyLEDsToggling(2);
		vTaskDelay(pdMS_TO_TICKS(3500));
	}
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName) {
	TaskHandle_t bad_task_handle = pxTask; // this seems to give me the crashed task handle
	signed char *bad_task_name = pcTaskName;

	while (true) {
		MyLEDsToggling(8);
		vTaskDelay(pdMS_TO_TICKS(4500));
	}
}

void vApplicationMallocFailedHook() {
	while (true) {
		MyLEDsToggling(9);
		vTaskDelay(pdMS_TO_TICKS(5500));
	}
}

void vApplicationIdleHook() {
	MyLEDsToggling(10);
	vTaskDelay(pdMS_TO_TICKS(10000));
}

// Unblock the task by releasing the semaphore.
void myTimerCallback(xTimerHandle pxTimer) {
	/* Notify Manager task to start data processing. */
	xSemaphoreGive(notification_semaphore);
}

// (void*)x is an expression that converts the int x to a pointer.

int main(void) {

	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");
		while (1U) {
		}
	}

	Timer_handle = xTimerCreate("Timer", 10, pdTRUE, 0, myTimerCallback);
	xTimerStart(Timer_handle, 0);

	xQueue = xQueueCreate(8, sizeof(uint8_t));
	Queue_id = xQueueCreate(3, sizeof(uint32_t));

	void* pxFirstSemaphoreParameters = pvPortMalloc(sizeof(xSemaphoreParameters_t));
	void* pxParameterStruct = pvPortMalloc(sizeof(parameter_struct_t));

	//str. 33 w Atmel-42247-Introduction-to-Basic RTOS-Features-using-SAM4L-EK-FreeRTOS-Port_Training-Manual.pdf
	xTaskCreate(vManager_Task, "manager", configMINIMAL_STACK_SIZE + 100,
			pxFirstSemaphoreParameters, tskIDLE_PRIORITY + 5, NULL);

	/* Create Worker 1 task */
	xTaskCreate(vWorker1_task, "Worker 1", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 4, &worker1_id);
	/* Create Worker 2 task */
	xTaskCreate(vWorker2_task, "Worker 2", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 3, &worker2_id);

	BaseType_t rs = xTaskCreate(vUART_Task, "UART",
	configMINIMAL_STACK_SIZE + 100U, NULL, tskIDLE_PRIORITY + 2, &UARTHandle); // pacz TRZECI PARAMETR
	if (rs != pdPASS) {
		MyErrorHandler(UARTHandle);
	}

//	rs = xTaskCreate(SPI_Slave_Task, "SPI_SLAVE", configMINIMAL_STACK_SIZE + 60U, NULL, tskIDLE_PRIORITY + 0,
//			&SPIHandle);
//	if (rs != pdPASS) {
//		MyErrorHandler(SPIHandle);
//	}

	/* Start the RTOS scheduler, this function should not return as it causes the execution
	 context to change from main() to one of the created tasks. */
	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}
