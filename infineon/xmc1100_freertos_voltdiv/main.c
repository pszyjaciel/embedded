#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

void outputByValue(uint8_t myValue) {
	switch (myValue) {
	case 0:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;
	case 1:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;
	case 2:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;
	case 3:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;

	case 4:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;

	case 5:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;

	case 6:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;

	case 7:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;

	case 8:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 9:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 10:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 11:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 12:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 13:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 14:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	case 15:
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		DIGITAL_IO_SetOutputHigh(&IOp08);
		DIGITAL_IO_SetOutputHigh(&IOp09);
		break;

	default:
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);
		DIGITAL_IO_SetOutputLow(&IOp08);
		DIGITAL_IO_SetOutputLow(&IOp09);
		break;
	}
}

void vApplicationIdleHook(void) {
	//outputByValue(2);
}

void MyTask0(void *pvParameters) {
	const TickType_t xFrequency = 100;
	TickType_t xLastWakeTime;
	while (1) {
		outputByValue(0);
		vTaskDelay(5);
		outputByValue(1);
		vTaskDelay(5);
		outputByValue(2);
		vTaskDelay(5);
		outputByValue(3);
		vTaskDelay(5);
		outputByValue(4);
		vTaskDelay(5);
		outputByValue(5);
		vTaskDelay(5);
		outputByValue(6);
		vTaskDelay(5);
		outputByValue(7);
		vTaskDelay(5);
		outputByValue(8);
		vTaskDelay(5);
		outputByValue(9);
		vTaskDelay(5);
		outputByValue(10);
		vTaskDelay(5);
		outputByValue(11);
		vTaskDelay(5);
		outputByValue(12);
		vTaskDelay(5);
		outputByValue(13);
		vTaskDelay(5);
		outputByValue(14);
		vTaskDelay(5);
		outputByValue(15);
		vTaskDelay(5);

		// same shody zajmuja 80ms, ale po dodaniu 100ms w xFrequency okres bedzie 180ms
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void MyTask1(void *pvParameters) {
	const TickType_t xFrequency = 200;
	TickType_t xLastWakeTime;
	while (1) {
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		//PORT0_BASE = 0x00000000;
		DIGITAL_IO_SetOutputHigh(&IOp06);
		DIGITAL_IO_SetOutputLow(&IOp07);

		//outputByValue(5);
	}
}

void MyTask2(void *pvParameters) {
	const TickType_t xFrequency = 400;
	TickType_t xLastWakeTime;
	while (1) {
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		DIGITAL_IO_SetOutputLow(&IOp06);
		DIGITAL_IO_SetOutputHigh(&IOp07);
		//outputByValue(10);
	}
}

void MyTask3(void *pvParameters) {
	const TickType_t xFrequency = 800;
	TickType_t xLastWakeTime;
	while (1) {
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		outputByValue(11);
	}
}

void MyTask4(void *pvParameters) {
	const TickType_t xFrequency = 900;

	// Initialise the xLastWakeTime variable with the current time.
	TickType_t xLastWakeTime;
	while (1) {
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		outputByValue(14);
	}
}

/*
 void MyTask5(void *pvParameters) {
 const TickType_t xFrequency = 1000;
 TickType_t xLastWakeTime;
 while (1) {
 xLastWakeTime = xTaskGetTickCount();
 vTaskDelayUntil(&xLastWakeTime, xFrequency);
 outputByValue(10);
 }
 }
 */

/*
 void MyTask6(void *pvParameters) {
 const TickType_t xFrequency = 1200;
 TickType_t xLastWakeTime;
 while (1) {
 xLastWakeTime = xTaskGetTickCount();
 vTaskDelayUntil(&xLastWakeTime, xFrequency);
 outputByValue(12);
 }
 }
 */

/*
 void MyTask7(void *pvParameters) {
 const TickType_t xFrequency = 1400;
 TickType_t xLastWakeTim e;
 while (1) {
 xLastWakeTime = xTaskGetTickCount();
 vTaskDelayUntil(&xLastWakeTime, xFrequency);
 outputByValue(14);
 }
 }
 */

int main(void) {
	DAVE_STATUS_t status;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U) {

		}
	}

//	xTaskCreate(MyTask0, "MyTask0", 40U, NULL, (tskIDLE_PRIORITY + 1), NULL);
	xTaskCreate(MyTask1, "MyTask1", 40U, NULL, (tskIDLE_PRIORITY + 1), NULL);
	xTaskCreate(MyTask2, "MyTask2", 40U, NULL, (tskIDLE_PRIORITY + 2), NULL);
//	xTaskCreate(MyTask3, "MyTask3", 40U, NULL, (tskIDLE_PRIORITY + 3), NULL);
//	xTaskCreate(MyTask4, "MyTask4", 40U, NULL, (tskIDLE_PRIORITY + 4), NULL);
//	xTaskCreate(MyTask5, "MyTask5", 40U, NULL, (tskIDLE_PRIORITY + 5), NULL);
//	xTaskCreate(MyTask6, "MyTask6", 40U, NULL, (tskIDLE_PRIORITY + 6), NULL);
//	xTaskCreate(MyTask7, "MyTask7", 40U, NULL, (tskIDLE_PRIORITY + 7), NULL);

	/* Start the RTOS scheduler, this function should not return as it causes the execution
	 context to change from main() to one of the created tasks. */
	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}
