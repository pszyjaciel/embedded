#include "MyUtils.h"

void MyLEDsToggling(uint8_t tyleRazy) {
	for (int var = 0; var < tyleRazy; ++var) {
		DIGITAL_IO_ToggleOutput(&LED0);
		DIGITAL_IO_ToggleOutput(&LED1);
		vTaskDelay(15);
	}
}

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

void MyErrorHandler(TaskHandle_t myTaskErrorHandle) {
	if (myTaskErrorHandle != NULL) {
		vTaskDelete(myTaskErrorHandle);
	}

	while (true) {
		DIGITAL_IO_ToggleOutput(&LED0);
		DIGITAL_IO_ToggleOutput(&LED1);
		vTaskDelay(pdMS_TO_TICKS(300));
	}
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName) {
	TaskHandle_t bad_task_handle = pxTask; // this seems to give me the crashed task handle
	SEGGER_RTT_printf(0, "bad_task_handle: %d \r\n", bad_task_handle);

	signed char *bad_task_name = pcTaskName;
	SEGGER_RTT_printf(0, "bad_task_handle: %s \r\n", bad_task_name);

	while (true) {
		MyLEDsToggling(8);
		vTaskDelay(pdMS_TO_TICKS(45));
	}
}

void vApplicationMallocFailedHook() {
	while (true) {
		MyLEDsToggling(9);
		vTaskDelay(pdMS_TO_TICKS(55));
	}
}

void vApplicationIdleHook() {
	MyLEDsToggling(10);
	vTaskDelay(pdMS_TO_TICKS(100));
}

void vApplicationTickHook() {
	taskYIELD();
}
