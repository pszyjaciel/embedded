/**
u:\ICT\4th_semester\SEPI4\retake\avr\MicroOSII4_1sem_v61\MicroOSII4_1sem_v61.atsln
LCD is blocking the code. Is it a bug here?: delay.h line 91

bug in bsp.c while reading the STK600 buttons:
#define SW_PORT PINC
#define SW_PORT PIND
*/


// #define F_CPU 10000000UL
#include <includes.h>

/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/




struct Parameters
{
	//uint8_t acc[50];
	int8_t accx;
	int8_t accy;
	int8_t accz;
	uint16_t tem;
	uint16_t enc;
	uint8_t mode;
	uint8_t stk_key;
} acpar;

// struct Parameters acpar;


OS_STK AppTaskStartStk[OS_TASK_START_STK_SIZE];
OS_STK AppTask1Stk[OS_TASK_1_STK_SIZE];
OS_STK AppTask2Stk[OS_TASK_2_STK_SIZE];
OS_STK AppTask3Stk[OS_TASK_3_STK_SIZE];

OS_EVENT *a_sem;
OS_EVENT *sem_TMR1;
OS_EVENT *sem_TMR2;
OS_EVENT *sem_TMR3;

OS_EVENT *sem_s1;
// OS_EVENT *sem_s2;


/*
**************************************************************************************************************
*                                           FUNCTION PROTOTYPES
**************************************************************************************************************
*/

static void AppTaskStart(void *p_arg);
static void AppTaskCreate(void);
static void AppTask1(void *p_arg);
static void AppTask2(void *p_arg);
static void AppTask3(void *p_arg);

INT8U  err;


// Periodic functions for the timers
void PeriodicFunction1(void *t, void *p_arg) {
	//start the task controlled by timer 1 by releasing semaphore
	OSSemPost(sem_TMR1);		// 2.15V
}

void PeriodicFunction2(void *t, void *p_arg) {
	//start the task controlled by timer 2 by releasing semaphore
	OSSemPost(sem_TMR2);		// 1.85V
}
void PeriodicFunction3(void *t, void *p_arg) {
	//start the task controlled by timer 3 by releasing semaphore
	OSSemPost(sem_TMR3);		// 1.55V
}


/*
**************************************************************************************************************
*                                                MAIN
*
* Note(s): 1) You SHOULD use OS_TASK_STK_SIZE (see OS_CFG.H) when setting OSTaskStkSize prior to calling
*             OSInit() because OS_TASK_IDLE_STK_SIZE and OS_TASK_STAT_STK_SIZE are set to this value in
*             OS_CFG.H.
**************************************************************************************************************
*/

int main(void)
{
	#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
	INT8U err;
	#endif

	// Any initialization code prior to calling OSInit() goes HERE

	// IMPORTANT: MUST be setup before calling 'OSInit()'
	OSTaskStkSize = OS_TASK_IDLE_STK_SIZE; // Setup the default stack size

	OSInit(); // Initialize "uC/OS-II, The Real-Time Kernel"

	// Any initialization code before starting multitasking
	OSTaskStkSize = OS_TASK_START_STK_SIZE;
	
	// If using a semaphore as a signaling mechanism, you should set the initial value to 0.
	a_sem = OSSemCreate(0);
	sem_TMR1 = OSSemCreate(0);
	sem_TMR2 = OSSemCreate(0);
	sem_TMR3 = OSSemCreate(0);
	
	// If there is only one resource, the value should be set to 1.
	// For multiple resources, set the value to the number of resources.
	sem_s1 = OSSemCreate(1);
	//	sem_s2 = OSSemCreate(1);
	
	OSTaskCreateExt(AppTaskStart, (void *) 0,
	(OS_STK *) &AppTaskStartStk[OSTaskStkSize - 1], OS_TASK_START_PRIO,
	OS_TASK_START_PRIO, (OS_STK *) &AppTaskStartStk[0], OSTaskStkSize,
	(void *) 0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
	OSTaskNameSet(OS_TASK_START_PRIO, "Start Task", &err);
	#endif

	OSStart(); // Start multitasking (i.e. give control to uC/OS-II)
	return 0;
}

/*
**************************************************************************************************************
*                                              STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
**************************************************************************************************************
*/

static void AppTaskStart(void *p_arg)
{
	// Prevent compiler warnings
	(void) p_arg;
	uint8_t err;

	// Initialize the BSP driver
	BSP_Init();
	USART_init();				// terminal on RS232
	
	init_rc_servo();			// port H
	init_aircraft();			// port B
	lcd_stk600_init();			// blocks the code in function lcd_init(LCD_DISP_ON)
	
	// Initialize Task switch output pins for DAC (R2-R network)
	DDRG = 0x0F;		// used for R2R-Board (Oscilloscope)
	
	// Run all unit tests.
	uint8_t result = runUnitTest();
	if (result == 0)
	{
		while(1) {
			;			// in case of error stop the program.
		}
	}
	
	// pointers to the periodic functions for the timers
	void(*pt_fun1)(void *t, void *p_arg);
	pt_fun1 = &PeriodicFunction1;
	
	void(*pt_fun2)(void *t, void *p_arg);
	pt_fun2 = &PeriodicFunction2;
	
	void(*pt_fun3)(void *t, void *p_arg);
	pt_fun3 = &PeriodicFunction3;
	
	
	INT8U perr;
	
	INT8U *mytimer_1 = "timer1";
	INT8U *mytimer_2 = "timer2";
	INT8U *mytimer_3 = "timer3";

	// here we create the timers to control of the tasks
	// the frequency of the timer task is defined in OS_CFG.H
	OS_TMR *timer_1;
	timer_1 = OSTmrCreate(0, 2 , OS_TMR_OPT_PERIODIC, *pt_fun1, (void *)42, mytimer_1, &perr);	// period 2 * 20ms
	
	OS_TMR *timer_2;
	timer_2 = OSTmrCreate(0, 3 , OS_TMR_OPT_PERIODIC, *pt_fun2, (void *)42, mytimer_2, &perr);	// period 3 * 20ms
	
	OS_TMR *timer_3;
	timer_3 = OSTmrCreate(0, 15 , OS_TMR_OPT_PERIODIC, *pt_fun3, (void *)42, mytimer_3, &perr);	// period 15 * 20ms

	USART_putstring("\nTimers created. app.c :: AppTaskStart()\r\n");		// RS232 output for debug purposes
	
	OSTmrStart(timer_1, &perr);
	OSTmrStart(timer_2, &perr);
	OSTmrStart(timer_3, &perr);
	
	AppTaskCreate();
	

	while (1)
	{
		OSSemPend(a_sem, 0, &err);
	}
}

/*
**************************************************************************************************************
*                                        CREATE APPLICATION TASKS
*
* Description : This function creates the application tasks.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
**************************************************************************************************************
*/

static void AppTaskCreate(void)
{
	#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
	INT8U err;
	#endif

	// Task initialization code goes HERE!
	OSTaskStkSize = OS_TASK_1_STK_SIZE; // Setup the default stack size
	OSTaskCreateExt(AppTask1,
	(void *) 0,
	(OS_STK *) &AppTask1Stk[OSTaskStkSize - 1],
	OS_TASK_1_PRIO,
	OS_TASK_1_PRIO,
	(OS_STK *) &AppTask1Stk[0],
	OSTaskStkSize,
	(void *) 0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	
	#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
	OSTaskNameSet(OS_TASK_1_PRIO, "Task 1", &err);
	#endif

	// Task initialization code goes HERE!
	OSTaskStkSize = OS_TASK_2_STK_SIZE; // Setup the default stack size
	OSTaskCreateExt(AppTask2,
	(void *) 0,
	(OS_STK *) &AppTask2Stk[OSTaskStkSize - 1],
	OS_TASK_2_PRIO,
	OS_TASK_2_PRIO,
	(OS_STK *) &AppTask2Stk[0],
	OSTaskStkSize,
	(void *) 0,
	OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	
	#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
	OSTaskNameSet(OS_TASK_2_PRIO, "Task 2", &err);
	#endif
	
	// Task initialization code goes HERE!
	OSTaskStkSize = OS_TASK_3_STK_SIZE; // Setup the default stack size
	OSTaskCreateExt(AppTask3,
	(void *) 0,
	(OS_STK *) &AppTask3Stk[OSTaskStkSize - 1],
	OS_TASK_3_PRIO,
	OS_TASK_3_PRIO,
	(OS_STK *) &AppTask3Stk[0],
	OSTaskStkSize,
	(void *) 0,
	OS_TASK_OPT_STK_CHK	| OS_TASK_OPT_STK_CLR);
	
	#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
	OSTaskNameSet(OS_TASK_3_PRIO, "Task 3", &err);
	#endif
	
	USART_putstring("\nTasks created. app.c :: AppTaskCreate()\r\n");
}

/*
**************************************************************************************************************
*                                                   TASKS
**************************************************************************************************************
*/

// Task1: grabbing data from sensors and buttons and storing in a struct acparam
static void AppTask1(void *p_arg)
{
	(void) p_arg;
	
	int8_t faccx = 0;
	int8_t faccy = 0;
	int8_t faccz = 0;
	volatile int16_t encoder = 0;
	volatile int16_t temperature = 0;
	uint8_t sw;
	uint8_t mode = 0;


	while (1)
	{
		OSSemPend(sem_TMR1, 0, &err);				// wait for the timer-semaphore
		LED_On(1);

		OSSemPend(sem_s1, 0, &err);					// wait for the resource
		
		// read the accelerometer
		faccx = (int8_t) get_x_acc() * 100;
		// uint16_t uiaccx = (unsigned int)faccx;
		acpar.accx = faccx;
		
		faccy =  (int8_t) get_y_acc() * 100;
		// uint16_t uiaccy = (unsigned int)faccy;
		acpar.accy = faccy;
		
		faccz =  (int8_t) get_z_acc() * 100;
		// uint16_t uiaccz = (unsigned int)faccz;
		acpar.accz = faccz;

		temperature = get_temp();					// read the temperature
		acpar.tem = temperature;
		
		encoder = ab_encoder_current_position(0);	// read the encoder
		acpar.enc = encoder;
		
		// read the STK600 buttons and store the pressed one
		for (sw = 1; sw < 9; sw++)
		{
			if (BSP_sw_in(sw) != 0) {				// key is pressed when returns != 0
				acpar.stk_key = sw;
			}
		}
		
		// read the LCD-buttons (mode of LCD-display)
		for (sw = 0; sw < 4; sw++)
		{
			mode = lcd_stk600_sw_pressed(sw);
			if (mode == 1)
			{
				acpar.mode = sw;					// switches 0..3
				lcd_clrscr();
			}
		}
		
		OSSemPost(sem_s1);							// release the resource
		
		LED_Off(1);
	}
}

// task2: control of servos, the LED-bar, LEDs of the aircraft
static void AppTask2(void *p_arg)
{
	(void) p_arg;
	
	static int y = -45;
	static int x = -127;
	static int8_t maxForward = -100;
	static int8_t maxBackward = 20;
	static int8_t maxRigth = -105;
	static int8_t maxLeft = 90;
	uint8_t pause = 0, counter1 = 1, state = 0;
	uint8_t tiltEmergency;
	
	while (1)
	{
		OSSemPend(sem_TMR2, 0, &err);		// wait for the timer-semaphore
		
		LED_On(2);
		
		OSSemPend(sem_s1, 0, &err);			// wait for the resource
		
		// control of the aircraft according to the STK-buttons
		switch(acpar.stk_key) {
			case 1:							// Dive BACKWARDS
			if(y < maxBackward)
			{
				tiltEmergency = 0;
				y = y + 2;
				rc_servo(0, y);
			}
			else
			{
				tiltEmergency = 1;
			}
			acpar.stk_key = 0;
			break;

			case 2:							// Dive FORWARDS
			if(y > maxForward)
			{
				tiltEmergency = 0;
				y = y - 2;
				rc_servo(0, y);
			}
			else
			{
				tiltEmergency = 1;
			}
			acpar.stk_key = 0;
			break;
			
			case 3:							// Turn RIGHT
			if(x > maxRigth) {
				tiltEmergency = 0;
				x = x - 2;
				rc_servo(1, x);
			}
			else {
				tiltEmergency = 1;
			}
			acpar.stk_key = 0;
			break;
			
			case 4:							// Turn LEFT
			if(x < maxLeft)
			{
				tiltEmergency = 0;
				x = x + 2;
				rc_servo(1, x);
			}
			else
			{
				tiltEmergency = 1;
			}
			acpar.stk_key = 0;
			break;
			
			default:
			rc_servo(0, y);
			rc_servo(1, x);
		}
		

		// pulse the LEDs of the aircraft
		if (pause != 1) {
			switch (state) {
				case 1:
				set_led(LED_RED, LED_ON);
				set_led(LED_GREEN, LED_ON);
				state = 0;
				break;

				case 0:
				set_led(LED_GREEN, LED_OFF);
				set_led(LED_RED, LED_OFF);
				state = 1;
				pause = 1;
				counter1++;
				break;
			}
		}
		else {
			if ((counter1 % 20) == 0) {
				pause = 0;
			}
			else {
				counter1++;
			}
		}
		
		// check the temperature
		if(acpar.tem > 105) {
			set_led(LED_YELLOW, LED_ON);
		}
		else {
			set_led(LED_YELLOW, LED_OFF);
		}
		
		// display the speed
		put_bar(acpar.enc/2);
		
		
		OSSemPost(sem_s1);					// release the resource
		
		LED_Off(2);
	}
}


// displaying values on the LCD according to the chosen display-mode
static void AppTask3(void *p_arg)
{
	(void) p_arg;

	double abc;
	int angle;
	char buf[64] = {};
	uint8_t state = 0;
	uint8_t counter = 0;
	char *message;

	while (1)
	{
		OSSemPend(sem_TMR3, 0, &err);			// wait for the timer-semaphore
		LED_On(3);
		
		OSSemPend(sem_s1, 0, &err);				// wait for the resource
		
		switch(acpar.mode) {
			case 0:								// greetings message
			if ((counter % 4) == 0) {
				if (state == 0) {
					lcd_gotoxy(0, 0);
					lcd_puts("Welcome to our \nAcft-simulator. ");
					// USART_putstring("Welcome to our Aircraft simulator\r\n");
					state = 1;
				}
				else {
					lcd_gotoxy(0, 0);
					lcd_puts("Press a key.    \n               ");
					// USART_putstring("Press a key.\r\n");
					state = 0;
				}
			}
			counter++;
			break;

			case 1:								// display values from the accelerometer
			lcd_gotoxy(0, 0);
			itoa(acpar.accx, buf, 10);
			lcd_puts("acx: ");
			lcd_puts(buf);
			print_hexByte(acpar.accx);
			
			lcd_gotoxy(8, 0);
			lcd_puts("acy: ");
			itoa(acpar.accy, buf, 10);
			lcd_puts(buf);
			print_hexByte(acpar.accy);
			
			itoa(acpar.tem, buf, 10);			// display the temperature
			lcd_gotoxy(0, 1);
			lcd_puts("Temp: ");
			lcd_puts(buf);
			break;

			case 2:								// display the speed
			angle = abs(acpar.accx * 2.5);
			print_hexByte(angle);
			abc = sin(angle) * 57;
			// height = (pow ((speed * abc), 2)) / 2 * g;
			// print_hexWord(height);			// debug message
			
			lcd_gotoxy(0, 0);
			lcd_puts("Speed: ");
			lcd_gotoxy(0, 1);
			itoa(acpar.enc, buf, 10);
			lcd_puts(buf);
			break;

			case 3:								// display encoder values
			lcd_gotoxy(0, 0);
			lcd_puts("Enc: ");
			lcd_gotoxy(0, 1);
			itoa(acpar.enc, buf, 10);
			lcd_puts(buf);
			
			lcd_gotoxy(8, 0);					// display the speed
			lcd_puts("Speed: ");
			lcd_gotoxy(8, 1);
			itoa(acpar.enc * 4, buf, 10);
			lcd_puts(buf);
			break;
		}
		
		OSSemPost(sem_s1);						// release the resources

		LED_Off(3);
	}
}


/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void App_TaskSwHook(void)
{
	PORTG = ~(OSTCBHighRdy->OSTCBPrio);
}

void App_TaskCreateHook(OS_TCB *ptcb)
{
}
void App_TaskDelHook(OS_TCB *ptcb)
{
}
void App_TaskIdleHook(void)
{
}

void App_TaskStatHook(void)
{
}
void App_TCBInitHook(OS_TCB *ptcb)
{
}
void App_TimeTickHook(void)
{
}

