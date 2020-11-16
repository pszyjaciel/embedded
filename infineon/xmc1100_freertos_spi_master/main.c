// SN 591098061 (master) piny poziome ruwnolegle do plytki
// Both FREERTOS and SYSTIMER APP need the systick hardware resource exclusively, therefore the conflict.

// stont:
// https://github.com/iotexpert/PSoC-FreeRTOS-Examples/blob/master/3-Queue.cydsn/main.c
// https://community.nxp.com/t5/MQX-Software-Solutions-Knowledge/How-to-use-mutex-and-semaphores-in-a-FreeRTOS-and-SDK2-0-Project/ta-p/1114196
// dzielnik napiecia ten ze szkoly; 0.2V na dzialke.

// semafory: https://visualgdb.com/tutorials/freertos/mutexes/

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"
#include "MyMutex.h"
#include "UartTask.h"


/* Data and buffers used */
#define DATA_COUNT 100
#define BUFFER_SIZE 10
#define PERIOD 100000U

/* Declared globally. */
xTimerHandle Timer_handle;
xTaskHandle worker1_id;
xTaskHandle worker2_id;
xTaskHandle UARTHandle_id;

QueueHandle_t Queue_id;
QueueHandle_t xStructQueue = NULL;
QueueHandle_t counterQueue;

SemaphoreHandle_t xMutex;

uint8_t master_send_data[] = { 0x55, 0xaa, 0xa5, 0x5a, 0x0f, 0xf0, 0x11, 0x22, 0x33, 0x44 };
uint16_t slave_send_data[BUFFER_SIZE];
uint32_t slave_send_index = 0;

struct AMessage {
	char ucMessageID;
	char ucData[20];
} AMessage_t;

typedef struct parameter_struct {
	const char Parameter1;
	const uint32_t Parameter2;
	//AMessage_t myStruct;	// jucha-kucha.
/*...*/
} parameter_struct_t;



typedef enum {
	RED, GREEN, BLUE
} Color_t;


void vSPI_Master_Task(void *pvParameters) {

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

//void vMyTimerCallback(xTimerHandle pxTimer) {
//	/* Notify Manager task to start data processing. */
//	//xSemaphoreGive(notification_semaphore);
//}

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
	//Timer_handle = xTimerCreate("Timer", pdMS_TO_TICKS(250), pdTRUE, 0, vMyTimerCallback);
	//xTimerStart(Timer_handle, 0);

	AMessage_t.ucMessageID = 0xab;
	memset(&(AMessage_t.ucData), 0x12, 20);
	xStructQueue = xQueueCreate(10, sizeof(AMessage_t));

	// 1 item queue that can hold colors
	//colorQueue = xQueueCreate(1, sizeof(Color_t));
	//counterQueue = xQueueCreate(1, sizeof(uint8_t));
	Queue_id = xQueueCreate(1, sizeof(uint8_t));

	if ((counterQueue == NULL) || (Queue_id == NULL)) {
		//while (1)
			;
	}

	void* pxParameterStruct = pvPortMalloc(sizeof(parameter_struct_t));

	xMutex = xSemaphoreCreateMutex();

	//xTaskCreate(vSPI_Master_Task, "SPI", configMINIMAL_STACK_SIZE + 100U, NULL, tskIDLE_PRIORITY + 2, &xSPIMasterHandle);
	xTaskCreate(vWorker1_task, "Worker 1", configMINIMAL_STACK_SIZE + 100, pxParameterStruct, tskIDLE_PRIORITY + 1, &worker1_id);
	xTaskCreate(vWorker2_task, "Worker 2", configMINIMAL_STACK_SIZE + 100, pxParameterStruct, tskIDLE_PRIORITY + 2, &worker2_id);

	// uart ma miec najwyzszy priorytet, inaczej nie dziala
	BaseType_t rs = xTaskCreate(vUART_task, "UART", configMINIMAL_STACK_SIZE + 100U, NULL, tskIDLE_PRIORITY + 3, &UARTHandle_id);
	if (rs != pdPASS) {
		MyErrorHandler(UARTHandle_id);
	}

	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}

