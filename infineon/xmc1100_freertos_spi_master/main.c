// SN 591098061 (master) piny poziome ruwnolegle do plytki
// Both FREERTOS and SYSTIMER APP need the systick hardware resource exclusively, therefore the conflict.

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"
#include "Worker1Task.h"
#include "Worker2Task.h"

/* Data and buffers used */
#define DATA_COUNT 100
#define BUFFER_SIZE 10
#define PERIOD 100000U
//#define MYMODE SYSTIMER_MODE_PERIODIC

xTaskHandle worker1_id;
xTaskHandle worker2_id;
xQueueHandle Queue_id;

uint8_t master_send_data[] = { 0x55, 0xaa, 0xa5, 0x5a, 0x0f, 0xf0, 0x11, 0x22,
		0x33, 0x44 };
uint16_t slave_send_data[BUFFER_SIZE];
uint32_t slave_send_index = 0;

typedef struct parameter_struct {
	const char Parameter1;
	const uint32_t Parameter2;
/*...*/
} parameter_struct_t;

void SPI_Master_Task(void *pvParameters) {

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {
		/* Master Transmit Data */
		SPI_MASTER_Transmit(&SPI_MASTER_0, master_send_data, 8);

		/* Wait until the data transmission is finished */
		while (SPI_MASTER_0.runtime->tx_busy) {
		}

		/* Ensure the last byte is shifted out from the buffer at lower baud rates, when frame end mode is disabled. */
		while (SPI_MASTER_GetFlagStatus(&SPI_MASTER_0,
				(uint32_t) XMC_SPI_CH_STATUS_FLAG_MSLS) != 0U) {
		}

		DIGITAL_IO_ToggleOutput(&LED0);
		vTaskDelay(pdMS_TO_TICKS(7500));
	}
}

void MyCallback(void) {
	DIGITAL_IO_ToggleOutput(&LED0);
	DIGITAL_IO_ToggleOutput(&LED1);
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

	// Create Software Timer with one second time interval in order to generate software timer callback event at
	// every second
//	uint32_t TimerId, tStatus;
//	TimerId = SYSTIMER_CreateTimer(PERIOD, MYMODE,
//			(void*) MyCallback, NULL);
//	if (TimerId != 0U) {
//		//Timer is created successfully
//		// Start/Run Software Timer
//		tStatus = SYSTIMER_StartTimer(TimerId);
//		if (tStatus == SYSTIMER_STATUS_SUCCESS) {
//			// Timer is running
//		} else {
//			// Error during software timer start operation
//		}
//	} else {
//		// Timer ID Can not be zero
//	}

	void* pxParameterStruct = pvPortMalloc(sizeof(parameter_struct_t));

	/* Create Worker 1 task, im wieksza cyfra tskIDLE_PRIORITY + 4, tym wiekszy priorytet */
	xTaskCreate(vWorker1_task, "Worker 1", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker1_id);
	/* Create Worker 2 task */
	xTaskCreate(vWorker2_task, "Worker 2", configMINIMAL_STACK_SIZE + 100,
			pxParameterStruct, tskIDLE_PRIORITY + 1, &worker2_id);
	/* Create SPI_Master task */
	BaseType_t rs = xTaskCreate(SPI_Master_Task, "SPI",
	configMINIMAL_STACK_SIZE + 100U, NULL, (tskIDLE_PRIORITY + 0),
			&xSPIMasterHandle);
	if (rs != pdPASS) {
		MyErrorHandler(xSPIMasterHandle);
	}
	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}

