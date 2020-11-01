// SN 591098061 (master) piny poziome ronloegle do plytki

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

/* Data and buffers used */
#define DATA_COUNT 100
#define BUFFER_SIZE 10

uint8_t master_send_data[] = { 0x55, 0xaa, 0xa5, 0x5a, 0x0f, 0xf0, 0x11, 0x22, 0x33, 0x44 };
uint16_t slave_send_data[BUFFER_SIZE];
uint32_t slave_send_index = 0;

void MyErrorHandler(TaskHandle_t xUARTHandle) {
	if (xUARTHandle != NULL) {
		vTaskDelete(xUARTHandle);
	}

	while (true) {
		DIGITAL_IO_ToggleOutput(&LED0);
		DIGITAL_IO_ToggleOutput(&LED1);
		vTaskDelay(pdMS_TO_TICKS(3000));
	}
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

		DIGITAL_IO_ToggleOutput(&LED0);
		vTaskDelay(pdMS_TO_TICKS(7500));
	}
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

	//xTaskCreate(UART_Task, "UART", 50U, NULL, (tskIDLE_PRIORITY + 0), NULL);	// pacz TRZECI PARAMETR
	BaseType_t rs = xTaskCreate(SPI_Master_Task, "SPI", 60U, NULL, (tskIDLE_PRIORITY + 0), &xSPIMasterHandle);
	if (rs != pdPASS) {
		MyErrorHandler(xSPIMasterHandle);
	}
	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}

