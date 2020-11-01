/*
 *********************************************************************************************************
 *                                           Atmel ATmega2560/ATMEGA2561
 *                                         Board Support Package
 *
 *                                (c) Copyright 2005, Micrium, Weston, FL
 *                                          All Rights Reserved
 *
 *
 * File : BSP.C
 * By   : Jean J. Labrosse - Ported to ATMEGA2560/ATMEGA2561 and WinAVR by Ib Havn, 2010.
 *
 * 2010-04-12, IHA:  BSP_Int0_Disable(void) and BSP_Int0_Enable(INT8U clear_pending) implemented.
 * 2010-04-14, IHA:  SW_in(INT8U sw) implemented.
 * 2010-04-14a, IHA: SW_in(INT8U sw) bug solved - sorry!
 * 2010-04-19, IHA:  BSP_ADC_init(OS_EVENT *sem), BSP_voltage_in(INT8U channel, OS_EVENT *sem) and
 * 					 BSP_ADC_ISR_Handler(void) are implemented.
 * 					 LED_On(), LED_Off() and LED_Toggle() are optimized.
 * 2012-05-01, IHA	 Changed to accept DASH BOARD if DASH_BOARD is defined:
 *					 voltage_in(), INT0/SW0 interrupt disabled
 *					 SW(1-8) moved to PORTC
 *********************************************************************************************************
 */

#include <includes.h>

/*
 *********************************************************************************************************
 *                                              PROTOTYPES
 *********************************************************************************************************
 */

static void BSP_InitTickISR(void);
static void LED_Init(void);

#ifndef DASH_BOARD
static void BSP_InitInt0ISR(void);
static OS_EVENT *adc_sem = 0; // Pointer to the ADC semaphore

#define SW_PORT PINC
#else
#define SW_PORT PIND
#endif
/*
 *********************************************************************************************************
 *                                         BSP INITIALIZATION
 *
 * Description : This function should be called by your application code before you make use of any of the
 *               functions found in this module.
 *
 * Arguments   : none
 *********************************************************************************************************
 */

void BSP_Init(void)
{
   LED_Init();
   BSP_InitTickISR();
#ifndef DASH_BOARD
   BSP_InitInt0ISR();
#endif
}

/*
 *********************************************************************************************************
 *                                        SETUP THE TICK RATE
 *
 * Note(s): 1) OCR0 = CPU_CLK_FREQ / (2 * Prescaler * OC_freq) - 1
 *          2) The equation actually performs rounding by multiplying by 2, adding 1 and then divising by 2
 *             in integer math, this is equivalent to adding 0.5
 *********************************************************************************************************
 */
static void BSP_InitTickISR(void)
{
   TCCR0A |= _BV(WGM01); /* Set TIMER0 to CTC Mode              */
   TCCR0B |= _BV(CS02) | _BV(CS00); /* Set TIMER0 prescaler CLK/1024       */
   TCNT0 = 0; /* Start TCNT at 0 for a new cycle                          */
   OCR0A = CPU_CLK_FREQ / OS_TICKS_PER_SEC / 1024 - 1;
   TIFR0 |= _BV(OCF0A); /* Clear  TIMER0 compare Interrupt Flag                     */
   TIMSK0 |= _BV(OCIE0A); /* Enable TIMER0 compare Interrupt                          */
}

#ifndef DASH_BOARD
/*
 *********************************************************************************************************
 *                                        SETUP INT0 interrupt
 * Interrupt on rising edge of INT0
 *********************************************************************************************************
 */
static void BSP_InitInt0ISR(void)
{
   EICRA |= _BV(ISC00) | _BV(ISC01);
   EIMSK |= _BV(INT0);
}


/**
 *********************************************************************************************************
 * Disable INT0 interrupt
 *********************************************************************************************************
 */
void inline BSP_Int0_Disable(void)
{
   EIMSK &= ~_BV(INT0);
}

/**
 ********************************************************************************************************
 * Enable INT0 interrupt
 * \param clear_pending true: clears pending INT0 interrupt before enabling
 *********************************************************************************************************
 */
void inline BSP_Int0_Enable(uint8_t clear_pending)
{
   if (clear_pending)
   {
      EIFR &= ~_BV(INTF0); // Clear INT0 Flag
   }
   EIMSK |= _BV(INT0);
}

/**
 * Initialize the ADC.
 * \note When you initialize the ADC the digital inputs in Port F is disabled!
 * \param *sem a pointer to the semaphore that will be used to synchronize the ADC's conversion time with.
 */
void BSP_ADC_init(OS_EVENT *sem)
{
#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif

   OS_ENTER_CRITICAL();

   // Store the semaphore to be used with the ADC.
   adc_sem = sem;

   // Disable the Digital pins corresponding to the ADC0 - ADC7 inputs
   DIDR0 = 0xFF;

   // Internal 2.56V reference
   ADMUX |= _BV(REFS0) | _BV(REFS1);

   // Enable ADC, enable ADC Interrupt, prescaler = 1/128 => 156.250 khz @ 20Mhz
   ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

   OS_EXIT_CRITICAL();
}

/**
 ********************************************************************************************************
 * Read the voltage on the specified channel. The calling task will be suspended until the
 * ADC finish the conversion.
 * \note This function must only be called from inside a task!
 * \note To initialize the ADC the BSP_ADC_init(OS_EVENT *sem) must be called before this function is called.
 * \param channel the AD MUX channel (ADC0..ADC7) to measure from [0..7].
 * \return the voltage as a 10-bit binary value, or -1 if channel out of range.
 *********************************************************************************************************
 */
INT16S BSP_voltage_in(INT8U channel)
{
   INT8U err;

   if (channel > 7)
   {
#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
      OS_CPU_SR cpu_sr = 0;
#endif

      OS_ENTER_CRITICAL();
      // setup mux to specified channel
      ADMUX &= ~(_BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
      ADMUX |= channel;
      // Start conversion
      ADCSRA |= _BV(ADSC);
      // Wait for the ADC Semaphore to be posted
      // It will be posted in the BSP_ADC_ISR_Handler when the conversion is done
      OSSemPend(adc_sem, 0, &err);

      OS_EXIT_CRITICAL();

      return ADC;
   }

   return -1;
}

/*
 *********************************************************************************************************
 *                                     HANDLE THE ADC INTERRUPT
 *
 * Note(s): 1) No need to clear the interrupt source sines the interrupt
 * is automatically cleared in hardware when the ISR runs.
 *********************************************************************************************************
 */
void BSP_ADC_ISR_Handler(void)
{
   OSSemPost(adc_sem);
}

/*
 *********************************************************************************************************
 *                                     HANDLE THE INT0 INTERRUPT
 *
 * Note(s): 1) No need to clear the interrupt source since we use INT0 and
 *             the interrupt is automatically cleared in hardware when the ISR runs.
 *********************************************************************************************************
 */

void BSP_Int0ISR_Handler(void)
{
   OSSemPost(a_sem);
}

#endif

/*
 *********************************************************************************************************
 *                                        SETUP PWM on Timer 1
 *********************************************************************************************************
 */
void  BSP_InitPWM1(void)
{
   // set OC1A/PB5 to output
   DDRB |= _BV(DDB5);

   // Set PWM Freq to 20 khz @ F_CPU = 10Mhz and prescaler = 1
   ICR1 = 499;

   // Set PWM duty cycle to 0
   OCR1A = 0;

   // Compare Match Output mode: Fast PWM
   // Set OC1A on BOTTON, Clear on Compare match
   TCCR1A |= _BV(COM1A1);

   // Setup Timer 1 to mode 14
   TCCR1A |= _BV(WGM11);
   TCCR1B |= _BV(WGM12) | _BV(WGM13);

   // Set prescaler to 1
   TCCR1B |= _BV(CS10);
}

/**
 ********************************************************************************************************
 * Read the status of a switch connected to SW_PORT.
 * \param sw switch to read the status of. [1..8]
 * \return 0: switch is not activated, <>0: switch is activated.
 *********************************************************************************************************
 */
INT8U BSP_sw_in(INT8U sw)
{
#if OS_CRITICAL_METHOD == 3       /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif

   OS_ENTER_CRITICAL();
   
   INT8U result = (SW_PORT & _BV(--sw)) == 0;
   
   OS_EXIT_CRITICAL();

   return result;
}

/**
 ********************************************************************************************************
 * Set the width of the PWM1 signal.
 * \param percent wanted duty cycle [0..100]
  *********************************************************************************************************
 */
void  BSP_SetPwm1(INT8U percent)
{
   OCR1A = percent/5;
}

/*
 *********************************************************************************************************
 *                                     HANDLE THE TICK INTERRUPT
 *
 * Note(s): 1) No need to clear the interrupt source since we use output compare mode for Timer #0 and
 *             the interrupt is automatically cleared in hardware when the ISR runs.
 *********************************************************************************************************
 */
void BSP_TickISR_Handler(void)
{
   OSTimeTick();
}

/*$PAGE*/
/*
 *********************************************************************************************************
 *                                       uC/Probe, INITIALIZE TIMER
 *
 * Description: This function initializes a 16 or 32-bit free-running timer for uC/Probe.
 *
 * Arguments  : none
 *
 * Note(s)    : none
 *********************************************************************************************************
 */
#if OS_PROBE_HOOKS_EN > 0                                               /* Do not compile this section if Probe is disabled         */
void OSProbe_TmrInit (void)
{
#if (OS_PROBE_TIMER_SEL == 1)
   TCCR1B = 0x00; /* Stop timer                                               */
   TCNT1 = 0xFFFF; /* Setup TCNT                                               */
   TCCR1A = 0x00; /* Normal Mode, count up 0x0000 to 0xFFFF                   */
   TCCR1B = 0x04; /* Start timer, prescale by 256                             */
#endif

#if (OS_PROBE_TIMER_SEL == 3)
   TCCR3B = 0x00; /* Stop timer                                               */
   TCNT3 = 0xFFFF; /* Setup TCNT                                               */
   TCCR3A = 0x00; /* Normal Mode, count up 0x0000 to 0xFFFF                   */
   TCCR3B = 0x04; /* Start timer, prescale by 256                             */
#endif
}
#endif                                                                  /* #if OS_PROBE_HOOKS_EN > 0                                */

/*$PAGE*/
/*
 *********************************************************************************************************
 *                                       uC/Probe, TIMER READ
 *
 * Description: This function reads a 16-bit free-running timer for uC/Probe.
 *
 * Arguments  : none
 *
 * Returns    : none
 *********************************************************************************************************
 */
#if OS_PROBE_HOOKS_EN > 0                                               /* Do not compile this section if Probe is disabled         */
CPU_INT32U OSProbe_TmrRd (void)
{
   INT16U cnts;

#if (OS_PROBE_TIMER_SEL == 1)
   cnts = (INT16U)TCNT1; /* Read current counts of Timer #1                          */
#endif

#if (OS_PROBE_TIMER_SEL == 3)
   cnts = (INT16U)TCNT3; /* Read current counts of Timer #3                          */
#endif

   return ((INT32U)cnts);
}
#endif                                                                  /* #if OS_PROBE_HOOKS_EN > 0                                */

/*
 *********************************************************************************************************
 *                                         LED INITIALIZATION
 *
 * Description : This function should be called by your application code before you make use of any of the
 *               LED functions found in this module.
 *
 * Arguments   : none
 *********************************************************************************************************
 */
static void LED_Init(void)
{
   DDRA = 0xFF; /* All PORTA pins are outputs                               */
   LED_Off(0); /* Turn ON all the LEDs                                     */
}


/*
 *********************************************************************************************************
 *                                             LED ON
 *
 * Description : This function is used to control any or all the LEDs on the board.
 *
 * Arguments   : led    is the number of the LED to control
 *                      0    indicates that you want ALL the LEDs to be ON
 *                      1    turns ON LED1 on the board
 *                      .
 *                      .
 *                      8    turns ON LED8 on the board
 *********************************************************************************************************
 */
void LED_On(INT8U led)
{
#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif

   OS_ENTER_CRITICAL();

   if (led)
   {
      PORTA &= ~_BV(--led);
   }
   else
   {
      PORTA = 0x00;
   }

   OS_EXIT_CRITICAL();
}

/*
 *********************************************************************************************************
 *                                             LED OFF
 *
 * Description : This function is used to control any or all the LEDs on the board.
 *
 * Arguments   : led    is the number of the LED to turn OFF
 *                      0    indicates that you want ALL the LEDs to be OFF
 *                      1    turns OFF LED1 on the board
 *                      .
 *                      .
 *                      8    turns OFF LED8 on the board
 *********************************************************************************************************
 */
void LED_Off(INT8U led)
{
#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif

   OS_ENTER_CRITICAL();

   if (led)
   {
      PORTA |= _BV(--led);
   }
   else
   {
      PORTA = 0xFF;
   }

   OS_EXIT_CRITICAL();
}

/*
 *********************************************************************************************************
 *                                        LED TOGGLE
 *
 * Description : This function is used to toggle the state of any or all the LEDs on the board.
 *
 * Arguments   : led    is the number of the LED to toggle
 *                      0    indicates that you want ALL the LEDs to toggle
 *                      1    Toggle LED1 on the board
 *                      .
 *                      .
 *                      8    Toggle LED8 on the board
 *********************************************************************************************************
 */
void LED_Toggle(INT8U led)
{
#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif

   OS_ENTER_CRITICAL();

   if (led)
   {
      PORTA ^= _BV(--led);
   }
   else
   {
      PORTA ^= 0xFF;
   }

   OS_EXIT_CRITICAL();
}
