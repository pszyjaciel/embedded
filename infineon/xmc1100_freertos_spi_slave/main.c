// SN 591096897 (slave) piny pionowe prostopadle do plytki

// (!)http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42247-Introduction-to-Basic%20RTOS-Features-using-SAM4L-EK-FreeRTOS-Port_Training-Manual.pdf
// zamiast "Start GDB server localy" uzyj zewnetrznego servera:
// "c:\Program Files (x86)\SEGGER\JLink\JLinkGDBServer.exe"

// eclipse problem with jlink:
// https://eclipse-embed-cdt.github.io/debug/jlink/

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
#include "Worker3Task.h"
#include "Worker4Task.h"
#include "Worker5Task.h"
#include "Worker6Task.h"
#include "Worker7Task.h"


/* Declared globally. */
QueueHandle_t xQueue = NULL;
xQueueHandle Queue_id;
xSemaphoreHandle notification_semaphore;
xTimerHandle Timer_handle;
xTimerHandle UART_Timer_handle;

xTaskHandle UARTHandle_id = NULL;
xTaskHandle SPIHandle_id = NULL;
xTaskHandle worker1_id;
xTaskHandle worker2_id;
xTaskHandle worker3_id;
xTaskHandle worker4_id;
xTaskHandle worker5_id;
xTaskHandle worker6_id;
xTaskHandle worker7_id;


typedef struct parameter_struct {
	const char Parameter1;
	const uint32_t Parameter2;
/*...*/
} parameter_struct_t;

// vManager_Task tforzy semafora
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
		MyLEDsToggling(7);
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

// niby jest ale go nie ma..
void myUARTTimerCallback(xTimerHandle pxTimer) {
	/* Notify Manager task to start data processing. */
	//xSemaphoreGive(notification_semaphore);
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

	// timer dostal prio9 : pacz stawienia dla freertos_0 w dave ce
	Timer_handle = xTimerCreate("Timer", pdMS_TO_TICKS(250), pdTRUE, 0, myTimerCallback);
	xTimerStart(Timer_handle, 0);
//	UART_Timer_handle = xTimerCreate("UART_Timer", pdMS_TO_TICKS(500), pdTRUE, 0, myUARTTimerCallback);
//	xTimerStart(UART_Timer_handle, 0);

	// The queue can hold a maximum of one (1) value
	Queue_id = xQueueCreate(1, sizeof(uint8_t));

	void* pxFirstSemaphoreParameters = pvPortMalloc(sizeof(xSemaphoreParameters_t));
	void* pxParameterStruct = pvPortMalloc(sizeof(parameter_struct_t));

	//str. 33 w Atmel-42247-Introduction-to-Basic RTOS-Features-using-SAM4L-EK-FreeRTOS-Port_Training-Manual.pdf
	xTaskCreate(vManager_Task, "manager", configMINIMAL_STACK_SIZE + 100,
			pxFirstSemaphoreParameters, tskIDLE_PRIORITY + 2, NULL);

	/* Create Worker 1 task, im wieksza cyfra tskIDLE_PRIORITY + 4, tym wiekszy priorytet */
	xTaskCreate(vWorker1_task, "Worker 1", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker1_id);
	/* Create Worker 2 task */
	xTaskCreate(vWorker2_task, "Worker 2", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker2_id);
	/* Create Worker 3 task */
	xTaskCreate(vWorker3_task, "Worker 3", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker3_id);
	/* Create Worker 4 task */
	xTaskCreate(vWorker4_task, "Worker 4", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker4_id);
	/* Create Worker 5 task */
	xTaskCreate(vWorker5_task, "Worker 5", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker5_id);
	/* Create Worker 6 task */
	xTaskCreate(vWorker6_task, "Worker 6", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker6_id);
	/* Create Worker 7 task */
	xTaskCreate(vWorker7_task, "Worker 7", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker7_id);



	BaseType_t rs = xTaskCreate(vUART_Task, "UART",	configMINIMAL_STACK_SIZE + 100U, NULL,
			tskIDLE_PRIORITY + 1, &UARTHandle_id); // pacz TRZECI PARAMETR
	if (rs != pdPASS) {
		MyErrorHandler(UARTHandle_id);
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
