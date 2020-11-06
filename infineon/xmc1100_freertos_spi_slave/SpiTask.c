// SN 591096897 (slave) na dlugim kablu

#include "SpiTask.h"

/* Here the queue handle is extern. */
extern QueueHandle_t xQueue;
//extern void MySPIErrorHandler();
//extern void MyLEDsToggling();

void MySPILEDsToggling(uint8_t tyleRazy) {
	for (int var = 0; var < tyleRazy; ++var) {
		DIGITAL_IO_SetOutputHigh(&LED0);
		vTaskDelay(15);
		DIGITAL_IO_SetOutputLow(&LED0);
		vTaskDelay(15);
	}
}

void MySPIErrorHandler(uint8_t errNumber) {
	MySPILEDsToggling(errNumber);
	vTaskDelay(pdMS_TO_TICKS(1500));
}

// decimal to hex converter
void dec2hex(int num, char* myHex) {
	int rem = 0, i = 0;
	//char hex[3];
	while (num > 0 && i >= 0) {
		rem = num % 16;
		myHex[i] = rem < 10 ? (char) rem + 48 : (char) rem + 55;
		num /= 16;
		i++;
	}
	myHex[i] = '\0';
}

// zrobic takom funkcje co zamruga ledami tyle razy ile bedzie w parametrze
// np. led P1.0 mruga 3x, a led P1.1 mruga 6x co daje 36.

// const DIGITAL_IO_t *const handler
//void mrugaj(uint8_t tyleRazy, const DIGITAL_IO_t * const handler) {
//	for (int var = 0; var < tyleRazy; ++var) {
//		DIGITAL_IO_SetOutputHigh(handler);
//		vTaskDelay(15);
//		DIGITAL_IO_SetOutputLow(handler);
//		vTaskDelay(15);
//	}
//}

//void wymrugajCyfre(uint8_t myDigit) {
//	uint8_t starszaCyfra = myDigit / 10;
//	uint8_t mlodszaCyfra = myDigit % 10;
//	mrugaj(starszaCyfra, &LED0);
//	mrugaj(mlodszaCyfra, &LED1);
//}

void SPI_Slave_Task(void *pvParameters) {
	uint32_t data_index;
	uint8_t slave_rx_data[DATA_COUNT];

	uint32_t DataToSend = 0;
	//const TickType_t xBlockTime = pdMS_TO_TICKS(200);
	BaseType_t rs;

	while (1) {

//		wymrugajCyfre(95);
//
//		DIGITAL_IO_SetOutputLow(&VDIOP0_0);
//		DIGITAL_IO_SetOutputHigh(&VDIOP0_5);
//		for (int var = 0; var < 500; ++var) {
//			asm("nop");
//		}
//		DIGITAL_IO_SetOutputLow(&VDIOP0_5);
//
//		vTaskDelay(500);	// 5sec dla schedulera 100Hz

// If slave select signal is falling
		if (XMC_SPI_CH_GetStatusFlag(SPI_SLAVE_0.channel) & XMC_SPI_CH_STATUS_FLAG_DX2S) {
			SPI_SLAVE_STATUS_t spiss = SPI_SLAVE_Receive(&SPI_SLAVE_0, slave_rx_data, DATA_COUNT);
			if (spiss != SPI_SLAVE_STATUS_SUCCESS) {
				MySPIErrorHandler(2);
			}
		}

		for (data_index = 0; data_index < DATA_COUNT; data_index++) {
			DataToSend = slave_rx_data[data_index];
			rs = xQueueSend(xQueue, &DataToSend, 0);
			//rs = xQueueSend(xQueue, &data_index, 0);

			if (rs != pdTRUE) {
				MySPIErrorHandler(3);
				break;
			}

			//wymrugajCyfre(slave_rx_data[data_index]);
			slave_rx_data[data_index] = 0;	// wykasuj
			DataToSend = slave_rx_data[data_index];	// wykasuj
		}
		//xQueueReceive(xQueue, &DataToReceive, xBlockTime);
		//DIGITAL_IO_ToggleOutput(&LED0);
		//vTaskDelay(pdMS_TO_TICKS(500));
	}

	//DIGITAL_IO_ToggleOutput(&LED0);
	vTaskDelay(pdMS_TO_TICKS(7500));
}
