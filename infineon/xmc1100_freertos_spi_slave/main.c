// SN 591096897 (slave) piny pionowe prostopadle do plytki

// (!)http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42247-Introduction-to-Basic%20RTOS-Features-using-SAM4L-EK-FreeRTOS-Port_Training-Manual.pdf

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
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

void MyLEDsToggling(uint8_t tyleRazy) {
	for (int var = 0; var < tyleRazy; ++var) {
		DIGITAL_IO_ToggleOutput(&LED0);
		DIGITAL_IO_ToggleOutput(&LED1);
		vTaskDelay(15);
	}
}

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
	TaskHandle_t bad_task_handle = pxTask;     // this seems to give me the crashed task handle
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

// Unblock the task by releasing the semaphore.
void myTimerCallback(xTimerHandle pxTimer) {
	/* Notify Manager task to start data processing. */
	xSemaphoreGive(notification_semaphore);
}

// (void*)x is an expression that converts the int x to a pointer.


// function may be used with voltage divider (max 4 bits)
// connected to P0.6, P0.7, P0.8, P0.9
void setByValue(uint8_t myValue) {
	// 18.8.5 Port Output Modification Register
	// 0..15: PSxx
	// 16..31: PRxx
	// PRx PSx Function
	// 0   1   Bit Pn_OUT.Px is set.
	// 1   0   Bit Pn_OUT.Px is reset.

	switch (myValue) {
	case 0x00:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x01:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x02:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x03:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x04:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x05:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x06:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x07:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x02000000\n\t" "str r0, [r1]\n\t");
		break;
	case 0x08:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x09:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x0A:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x0B:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x01000000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x0C:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x0D:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00800000\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x0E:
		asm("ldr r0, =0x00400000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;
	case 0x0F:
		asm("ldr r0, =0x00000040\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000080\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000100\n\t" "str r0, [r1]\n\t");
		asm("ldr r0, =0x00000200\n\t" "str r0, [r1]\n\t");
		break;

	default:
		break;
	}
}


int main(void) {

	DAVE_STATUS_t status;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");
		while (1U) {
		}
	}

	Timer_handle = xTimerCreate("Timer", 1, pdTRUE, 0, myTimerCallback);
	xTimerStart(Timer_handle, 0);

	xQueue = xQueueCreate(8, sizeof(uint8_t));
	Queue_id = xQueueCreate(2, sizeof(uint32_t));

	void* pxFirstSemaphoreParameters = pvPortMalloc(sizeof(xSemaphoreParameters_t));
	void* pxParameterStruct = pvPortMalloc(sizeof(parameter_struct_t));

	//str. 33 w Atmel-42247-Introduction-to-Basic RTOS-Features-using-SAM4L-EK-FreeRTOS-Port_Training-Manual.pdf
	xTaskCreate(Manager_Task, "manager", configMINIMAL_STACK_SIZE + 100, pxFirstSemaphoreParameters,
	tskIDLE_PRIORITY + 3, NULL);

	/* Create Worker 1 task */
	xTaskCreate(worker1_task, "Worker 1", configMINIMAL_STACK_SIZE + 100, pxParameterStruct, tskIDLE_PRIORITY + 1,
			&worker1_id);
	/* Create Worker 2 task */
	xTaskCreate(worker2_task, "Worker 2", configMINIMAL_STACK_SIZE + 100, pxParameterStruct, tskIDLE_PRIORITY + 2,
			&worker2_id);

//	BaseType_t rs = xTaskCreate(UART_Task, "UART", configMINIMAL_STACK_SIZE + 120U, NULL, tskIDLE_PRIORITY + 1,
//			&UARTHandle); // pacz TRZECI PARAMETR
//	if (rs != pdPASS) {
//		MyErrorHandler(UARTHandle);
//	}
//
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
