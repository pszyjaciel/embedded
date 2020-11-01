#include <DAVE.h>  //Declarations from DAVE Code Generation (includes SFR declaration)

/* Kernel includes. */
#include "FREERTOS/task.h"

const TickType_t xDelay = 200 / portTICK_PERIOD_MS;

static void LED_Task0(void *pvParameters);
static void LED_Task1(void *pvParameters);
static void LED_Task2(void *pvParameters);
static void LED_Task3(void *pvParameters);
static void LED_Task4(void *pvParameters);
static void LED_Task5(void *pvParameters);
static void LED_Task6(void *pvParameters);

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

//To create an idle hook:
//Set configUSE_IDLE_HOOK to 1 in FreeRTOSConfig.h.
//Define a function that has the following name and prototype: void vApplicationIdleHook( void );
//It is common to use the idle hook function to place the microcontroller CPU into a power saving mode.
void vApplicationIdleHook(void) {
	setByValue(0);
}

void vApplicationTickHook(void) {
	;
}

void vApplicationMallocFailedHook(void) {
	;
}

void vApplicationStackOverflowHook(void) {
	;
}

// wg mnie preemptive to przerywa taska ale nigdy go nie konczy..
int main(void) {
//	XMC_GPIO_EnableDigitalInput(P2_10);
//	XMC_GPIO_SetMode( P2_10, XMC_GPIO_MODE_OUTPUT_PUSH_PULL );

	DAVE_STATUS_t status;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status == DAVE_STATUS_FAILURE) {
		while (1U) {
		}
	}

	/* Creating tasks defined within main.c */
	// for configIDLE_SHOULD_YIELD: the application creates tasks that run at the idle priority.
	xTaskCreate(LED_Task0, "Task0", 40U, NULL, ( tskIDLE_PRIORITY + 3), NULL);
	xTaskCreate(LED_Task1, "Task1", 40U, NULL, ( tskIDLE_PRIORITY + 2), NULL);
	xTaskCreate(LED_Task2, "Task2", 40U, NULL, ( tskIDLE_PRIORITY + 1), NULL);
//	xTaskCreate(LED_Task3, "Task3", 40U, NULL, ( tskIDLE_PRIORITY + 0), NULL);
//	xTaskCreate(LED_Task4, "Task4", 40U, NULL, ( tskIDLE_PRIORITY + 0), NULL);
//	xTaskCreate(LED_Task5, "Task5", 40U, NULL, ( tskIDLE_PRIORITY + 0), NULL);
//	xTaskCreate(LED_Task6, "Task6", 40U, NULL, ( tskIDLE_PRIORITY + 0), NULL);

	/* Start the RTOS scheduler, this function should not return as it causes the execution
	 context to change from main() to one of the created tasks. */
	vTaskStartScheduler();

	/* Should never reach here */
	return 0;
}

// vTaskDelay(pdMS_TO_TICKS(x)) defines the frequency of the task
static void LED_Task0(void *pvParameters) {
	while (1) {
		setByValue(1);
		for (int var = 0; var < 3400; ++var) {
			;
		}
		vTaskDelay(pdMS_TO_TICKS(xDelay));
	}
}

static void LED_Task1(void *pvParameters) {
	while (1) {
		setByValue(2);
		for (int var = 0; var < 900; ++var) {
			;
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

static void LED_Task2(void *pvParameters) {
	while (1) {
		setByValue(3);
		for (int var = 0; var < 1500; ++var) {
			;
		}
		vTaskDelay(pdMS_TO_TICKS(30));
		//taskYIELD();	// musi ma byc dla preemptive
	}
}

static void LED_Task3(void *pvParameters) {
	while (1) {
		setByValue(4);
		for (int var = 0; var < 500; ++var) {
			;
		}
		vTaskDelay(pdMS_TO_TICKS(xDelay));
		//taskYIELD();
	}
}

static void LED_Task4(void *pvParameters) {
	while (1) {
		setByValue(5);
		for (int var = 0; var < 600; ++var) {
			;
		}
		vTaskDelay(pdMS_TO_TICKS(xDelay));
		//taskYIELD();
	}
}

static void LED_Task5(void *pvParameters) {
	while (1) {
		setByValue(0);
		vTaskDelay(pdMS_TO_TICKS(1));
		setByValue(6);
	}
}

static void LED_Task6(void *pvParameters) {
	while (1) {
		setByValue(0);
		vTaskDelay(pdMS_TO_TICKS(1));
		setByValue(7);
	}
}

//		setByValue(0);
//vTaskDelay(10);
//		vTaskDelay(pdMS_TO_TICKS(1));
//DIGITAL_IO_ToggleOutput(&LED1);	// P1.1
//LED0.gpio_port->OMR = 0x00010001U << 1;
// 18.8.5 Port Output Modification Register
// 0..15: PSxx
// 16..31: PRxx

//		PRx PSx Function
//		0   0   Bit Pn_OUT.Px is not changed.
//		0   1   Bit Pn_OUT.Px is set.
//		1   0   Bit Pn_OUT.Px is reset.
//		1   1   Bit Pn_OUT.Px is toggled.
//LED0.gpio_port->OMR = 0x00020002U;

//		setByValue(2);

//DIGITAL_IO_ToggleOutput(&LED0);
//XMC_GPIO_ToggleOutput(LED0.gpio_port, LED0.gpio_pin);

//port->OMR = 0x10001U << pin;

//#define XMC_GPIO_PORT1 ((XMC_GPIO_PORT_t *) PORT1_BASE)
//#define PORT1_BASE 0x40040100UL
//LED0.gpio_port->OMR = (0x10001U << LED0.gpio_pin);	// P1.0
//LED0.gpio_port->OMR = 0x00010001U;
