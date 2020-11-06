// SN 591098061 (master) piny poziome ruwnolegle do plytki
// Both FREERTOS and SYSTIMER APP need the systick hardware resource exclusively, therefore the conflict.

// stont:
// https://github.com/iotexpert/PSoC-FreeRTOS-Examples/blob/master/3-Queue.cydsn/main.c

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"

/* Data and buffers used */
#define DATA_COUNT 100
#define BUFFER_SIZE 10
#define PERIOD 100000U

/* Declared globally. */
xTimerHandle Timer_handle;
xTaskHandle worker1_id;
xTaskHandle worker2_id;
QueueHandle_t Queue_id;
QueueHandle_t xStructQueue = NULL;
QueueHandle_t colorQueue;

uint8_t master_send_data[] = { 0x55, 0xaa, 0xa5, 0x5a, 0x0f, 0xf0, 0x11, 0x22, 0x33, 0x44 };
uint16_t slave_send_data[BUFFER_SIZE];
uint32_t slave_send_index = 0;

typedef struct parameter_struct {
	const char Parameter1;
	const uint32_t Parameter2;
/*...*/
} parameter_struct_t;

struct AMessage {
	char ucMessageID;
	char ucData[20];
} xMessage;

typedef enum {
	RED, GREEN, BLUE
} Color_t;

void vWorker1_task(void *pvParameters) {
	Color_t tempColor;
	BaseType_t bt;
	while (true) {
		DIGITAL_IO_ToggleOutput(&LED0);
		bt = xQueueSend(colorQueue, &tempColor, 0);
		if (bt != pdTRUE) {
			// error
		}
		setByValue(1);
	}
	/* Should never go there */
	vTaskDelete(worker1_id);
}

void vWorker2_task(void *pvParameters) {
	Color_t currentColor = GREEN;
	while (true) {
		DIGITAL_IO_ToggleOutput(&LED1);

		if (xQueueReceive(colorQueue, &currentColor, 0) == pdTRUE) {
			//RED_Write(1);
			//BLUE_Write(1);
			//GREEN_Write(1);
			setByValue(3);
		}

		if (currentColor == RED) {
		}
		//RED_Write(~RED_Read());
		else if (currentColor == BLUE) {
		}
		//BLUE_Write(~BLUE_Read());
		else {
		}
		//GREEN_Write(~GREEN_Read());

		setByValue(2);
		vTaskDelay(500);
	}
	/* Should never go there */
	vTaskDelete(worker2_id);
}

void SPI_Master_Task(void *pvParameters) {

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {
		/* Master Transmit Data */
		SPI_MASTER_Transmit(&SPI_MASTER_0, master_send_data, 8);

		/* Wait until the data transmission is finished */
		while (SPI_MASTER_0.runtime->tx_busy) {
		}

		/* Ensure the last byte is shifted out from the buffer at lower baud rates, when frame end mode is disabled. */
		while (SPI_MASTER_GetFlagStatus(&SPI_MASTER_0, (uint32_t) XMC_SPI_CH_STATUS_FLAG_MSLS) != 0U) {
		}

		//DIGITAL_IO_ToggleOutput(&LED0);
		vTaskDelay(pdMS_TO_TICKS(7500));
	}
}

void myTimerCallback(xTimerHandle pxTimer) {
	/* Notify Manager task to start data processing. */
	//xSemaphoreGive(notification_semaphore);
}

int main(void) {

	DAVE_STATUS_t status;
	TaskHandle_t xSPIMasterHandle = NULL;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */
	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U) {
		}
	}

	// timer dostal prio4 : pacz ustawienia dla freertos_0 w dave ce
	Timer_handle = xTimerCreate("Timer", pdMS_TO_TICKS(250), pdTRUE, 0, myTimerCallback);
	xTimerStart(Timer_handle, 0);

	xMessage.ucMessageID = 0xab;
	memset(&(xMessage.ucData), 0x12, 20);
	xStructQueue = xQueueCreate(10, sizeof(xMessage));

	// 1 item queue that can hold colors
	colorQueue = xQueueCreate(1, sizeof(Color_t));
	if (colorQueue == NULL) {
		while (1)
			;
	}

	void* pxParameterStruct = pvPortMalloc(sizeof(parameter_struct_t));
	/* Create Worker 1 task, im wieksza cyfra tskIDLE_PRIORITY + 4, tym wiekszy priorytet */
	xTaskCreate(vWorker1_task, "Worker 1", configMINIMAL_STACK_SIZE + 100, pxParameterStruct, tskIDLE_PRIORITY + 1, &worker1_id);
	/* Create Worker 2 task */
	xTaskCreate(vWorker2_task, "Worker 2", configMINIMAL_STACK_SIZE + 100, pxParameterStruct, tskIDLE_PRIORITY + 1, &worker2_id);

	/* Create SPI_Master task */
	BaseType_t rs = xTaskCreate(SPI_Master_Task, "SPI", configMINIMAL_STACK_SIZE + 100U, NULL, (tskIDLE_PRIORITY + 0), &xSPIMasterHandle);
	if (rs != pdPASS) {
		MyErrorHandler(xSPIMasterHandle);
	}

	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}

