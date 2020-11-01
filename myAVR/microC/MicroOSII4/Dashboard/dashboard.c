/*
 * dashboard.c
 *
 * Version: 2012-05-01
 *  Author: IHA
 */

#ifdef DASH_BOARD
#include <includes.h>
#include <dashboard.h>
#include <math.h>
#include <interrupt_driven/OWIIntFunctions.h>
#include <interrupt_driven/OWIInterruptDriven.h>
#include <common_files/OWIcrc.h>

#define SPEED_FACTOR 60.0*F_CPU/1024.0

// Holds the last retrieved temperature
static int ds1820_temperature = 0;

// Holds the last gas pedal reading
static uint16_t adc0 = 0;

// Holds the last RPM calculated from the motor speed sensor
static unsigned long _motor_speed_timer_ticks = 0xFFFF;

void db_init()
{
   // Signal indicators
   DDRF |= _BV(DDF7) | _BV(DDF4);

   // Temp indicator
   DDRF |= _BV(DDF5) | _BV(DDF3);
   DDRE |= _BV(DDE7) | _BV(DDE5);
   db_temp_indicator(0);

   // DS1820 Temp sensor
   OWI_Init();
   // Led on Temperature board
   DDRH |= _BV(DDH2);

   // Timer 3 Used to generate PWM signals for the H-Bridge
   DDRE |= _BV(DDE6) | _BV(DDE4) | _BV(DDE3) | _BV(DDE2);
   // Setup to Fast PWM mode = 14
   TCCR3A |= _BV(WGM31);
   TCCR3B |= _BV(WGM33) | _BV(WGM32);
   // CTC mode
   // Clear OC3A/OC3B on compare match, set OC3A/OC3B at BOTTOM (non-inverting mode)
   TCCR3A |= _BV(COM3A1) | _BV(COM3B1);
   //PWM freq = 25 kHz
   // TOP = ICR3
   ICR3 = F_CPU/(1*25000L)-1; // @ Prescaler 1
   db_motor_speed(0,0);
   db_motor_speed(1,10);
   // Prescaler = 1; START timer
   TCCR3B |= _BV(CS30);

   // Setup ADC channel 0 for measuring gas pedal state
   // Disable the Digital pins corresponding to the ADC0 inputs
   DIDR0 = 0x01;
   // VCC reference
   ADMUX |= _BV(REFS0);
   // Enable ADC, enable ADC Interrupt, prescaler = 1/128 => 156.250 khz @ 20Mhz, free running mode, MUX=0
   ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0)  | _BV(ADATE);
   // Start conversion
   ADCSRA |= _BV(ADSC);

   // Speed Sensor
   // Setup INT0 for handling the speed sensor.
   // Rising edge
   EICRA |= _BV(ISC01) | _BV(ISC00);
   // Enable INT0 interrupt
   EIMSK |= _BV(INT0);
   // Setup Timer 4 to time the distance between speed sensor test's
   // Normal mode => TOP = 0xFFFF
   // Enable TIMER0 Overflow interrupt
   TIMSK4 = _BV(TOIE4);
   // Pre scaler = 1024
   // Start timer
   TCCR4B |= _BV(CS42) | _BV(CS40);
}

//************************************
// Method:    db_motor_speed
// Parameter: uint8_t motor [0, 1]
// Parameter: int8_t percent [-100 - 100]
//************************************
void db_motor_speed(uint8_t motor, int8_t percent)
{
   if (percent < -100)
   {
      percent = -100;
   }
   else if (percent > 100)
   {
      percent = 100;
   }

#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif
   OS_ENTER_CRITICAL();

   uint16_t ocr =(ICR3*abs(percent)/100);

   if ( motor == 0)
   {
      if (percent < 0)
      {
         OCR3A = ICR3-ocr;
         PORTE |= _BV(PE6);
      }
      else
      {
         OCR3A = ocr;
         PORTE &= ~_BV(PE6);
      }
   }
   else if (motor == 1)
   {
      if (percent < 0)
      {
         OCR3B = ICR3-ocr;
         PORTE |= _BV(PE2);
      }
      else
      {
         OCR3B = ocr;
         PORTE &= ~_BV(PE2);
      }
   }

   OS_EXIT_CRITICAL();
}

//************************************
// Method:    db_signal_indicator
// Returns:   void
// Note:	  Used PF7 & PF4
// Parameter: uint8_t dir 0: off, 1: Left, 2: Right
//************************************
void db_signal_indicator(uint8_t dir)
{
#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif
   OS_ENTER_CRITICAL();

   if (dir == 1)
   {
      PORTF |= _BV(PF7);
      PORTF &= ~(_BV(PF4));
   }
   else if (dir == 2)
   {
      PORTF |= _BV(PF4);
      PORTF &= ~(_BV(PF7));
   }
   else
   {
      PORTF &= ~(_BV(PF7) | _BV(PF4));
   }
   OS_EXIT_CRITICAL();
}

//************************************
// Method:    db_gear_shifter
// Returns:   uint8_t  0: None, 1: DOWN, 2: UP
//************************************
uint8_t db_gear_shifter()
{
   return ~PINE & (_BV(0) | _BV(1));
}

//************************************
// Method:    db_signal_shifter
// Returns:   uint8_t 0: None, 1: Left, 2: Right
//************************************
uint8_t db_signal_shifter()
{
   return (~PINF & (_BV(PF2) | _BV(PF1))) >> 1;
}

//******************************************************************************************
// Method:    db_gas_pedal
// Note:	  Multiplied by two because the pot-meter (47K) is in serie with a 47K resistor.
// Returns:   uint16_t position of gas pedal
//******************************************************************************************
uint16_t db_gas_pedal()
{
   return adc0 << 1;
}

//************************************
// Method:    db_temp_indicator
// Parameter: uint8_t percent 0-100
//************************************
void db_temp_indicator(uint8_t percent)
{
   if (percent > 100) percent=100;

   percent /= 10;

#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif
   OS_ENTER_CRITICAL();

   // STR low
   PORTF &= ~(_BV(PF3));

   uint8_t zero;


   // Shift zero's into shiftregister => LED OFF
   // D low
   PORTF &= ~(_BV(PF5));
   for (zero = 0; zero < (12-percent); zero++)
   {
      // Generate one clock cycle
      PORTE |= _BV(PE7);
      PORTE &= ~(_BV(PE7));
   }

   //shift one's in to shiftregister => LED ON
   // D high
   PORTF |= _BV(PF5);
   for (uint8_t one = zero; one < 12; one++)
   {
      // Generate one clock cycle
      PORTE |= _BV(PE7);
      PORTE &= ~(_BV(PE7));
   }

   // STR High
   PORTF |= _BV(PF3);
   // EO High
   PORTE |= _BV(PE5);

   OS_EXIT_CRITICAL();
}

//************************************
// Method:    db_temp_sensor
// Returns:   int16_t temperature in Celcius
// Note:	  in 0.5 C steps
//************************************
int16_t db_temp_sensor()
{
   return ds1820_temperature;
}

//*******************************************
// Method:    db_speed_sensor
// Returns:   uint16_t motor speed in RPM
//*******************************************
uint16_t db_speed_sensor()
{
   if (_motor_speed_timer_ticks == 0xFFFF)
   {
      return 0;
   }
   else if (_motor_speed_timer_ticks > 117)
   {
      return (int16_t)(round(SPEED_FACTOR/_motor_speed_timer_ticks));
   }
   else
   {
      return 5000;
   }
}

/************************************************************************/
// ONE-WIRE below
// Ported from AVR 318 Application note, IHA 2012-04-24                                                                  */
/************************************************************************/
// Defines used only in code example.
#define OWI_STATE_IDLE                  0
#define OWI_STATE_DETECT_PRESENCE1      1
#define OWI_STATE_WAIT_FOR_CONVERSION1  2
#define OWI_STATE_WAIT_FOR_CONVERSION2  3
#define OWI_STATE_DETECT_PRESENCE2      4
#define OWI_STATE_READ_SCRATCHPAD       5
#define OWI_STATE_CHECK_CRC             6

#define DS1820_START_CONVERSION         0x44    //!< DS1820 start conversion command
#define DS1820_READ_SCRATCHPAD          0xbe    //!< DS1820 Read scratchpad command

extern OWIflags OWIStatus;
extern unsigned char *OWIDataBuffer;

/*! \brief  The state machine that controls communication on the 1-Wire bus
 *
 *  This function is called from main every time the 1-Wire driver is not
 *  busy. The state machine will read the temperature from a DS1820 temperature
 *  sensor, crc check it, and put it in the global variable temperature if
 *  everything is OK.
 */
void OWI_StateMachine()
{
   static uint8_t state = OWI_STATE_IDLE;
   static uint8_t buf[9];
   uint8_t i;
   uint8_t crc;


#if OS_CRITICAL_METHOD == 3                                             /* Allocate storage for CPU status register                 */
   OS_CPU_SR cpu_sr = 0;
#endif
   OS_ENTER_CRITICAL();

   // If an error has occurred since last time, clear all flags and
   // return to idle state.
   if (OWIStatus.error)
   {
      state = OWI_STATE_IDLE;
      OWIStatus.allFlags = FALSE;
   }

   switch (state)
   {
   case OWI_STATE_IDLE:
   {
      // Send reset signal and update state.
      OWI_DetectPresence();
      state = OWI_STATE_DETECT_PRESENCE1;
      break;
   }

   case OWI_STATE_DETECT_PRESENCE1:
   {
      // If no presence was detected, go back to idle state.
      if(OWIStatus.presenceDetected == FALSE)
      {
         state = OWI_STATE_IDLE;
      }
      // If presence was detected, send Skip ROM and Start conversion
      // signals.
      else
      {
         // Turn on Led
         PORTH |= _BV(PH2);
         buf[0] = OWI_ROM_SKIP;
         buf[1] = DS1820_START_CONVERSION;
         OWI_TransmitData(buf, 16);
         state = OWI_STATE_WAIT_FOR_CONVERSION1;
      }
      break;
   }

   case OWI_STATE_WAIT_FOR_CONVERSION1:
   {
      // Receive one byte of data to check for completion of the
      // temperature conversion.
      OWI_ReceiveData(buf, 8);
      state = OWI_STATE_WAIT_FOR_CONVERSION2;
      break;
   }

   case OWI_STATE_WAIT_FOR_CONVERSION2:
   {
      // If everything received was zero. Jump to the last state
      // to receive a new byte.
      if (buf[0] == 0x00)
      {
         state = OWI_STATE_WAIT_FOR_CONVERSION1;
      }
      // If there was at least 1 one received, continue with a new
      // reset.
      else
      {
         OWI_DetectPresence();
         state = OWI_STATE_DETECT_PRESENCE2;
      }
      break;
   }

   case OWI_STATE_DETECT_PRESENCE2:
   {
      // If no presence was detected, go back to idle state.
      if(OWIStatus.presenceDetected == FALSE)
      {
         state = OWI_STATE_IDLE;
      }
      // If presence was detected, send Skip ROM and Read scratchpad
      // signals.
      else
      {
         buf[0] = OWI_ROM_SKIP;
         buf[1] = DS1820_READ_SCRATCHPAD;
         OWI_TransmitData(buf, 16);
         state = OWI_STATE_READ_SCRATCHPAD;
      }
      break;
   }

   case OWI_STATE_READ_SCRATCHPAD:
   {
      // Read the 9 bytes of scratchpad data.
      OWI_ReceiveData(buf, 9 * 8);
      state = OWI_STATE_CHECK_CRC;
      break;
   }

   case OWI_STATE_CHECK_CRC:
   {
      // Compare the computed crc with the crc read from the
      // scratchpad.
      crc = 0;
      for(i = 0; i < 8; i++)
      {
         crc =  OWI_ComputeCRC8(buf[i], crc);
      }
      // If they match, update the temperature variable.
      if (crc == buf[8])
      {
         ds1820_temperature = buf[0] | (buf[1] << 8);
         state = OWI_STATE_IDLE;
         // Turn off Led
         PORTH &= ~_BV(PH2);
      }
      // If they don't match, go back to the second Reset to
      // read the scratchpad again.
      else
      {
         OWI_DetectPresence();
         state = OWI_STATE_DETECT_PRESENCE2;
      }
      break;
   }
   }

   OS_EXIT_CRITICAL();
}

//************************************
// Method:    db_handle_one_wire
// FullName:  db_handle_one_wire
// Handle the one-wire state machine.
// Must be called continuously
//************************************
void db_handle_one_wire()
{
   if (!OWIStatus.busy)
   {
      OWI_StateMachine();
   }
}

/*!
 Interrupt service routine for handling ADC when a conversion is complided.
*/
ISR(ADC_vect)
{
   adc0 = ADC;
}

/*!
 Interrupt service routine for handling the speed sensor.
*/
ISR(INT0_vect)
{
   _motor_speed_timer_ticks = TCNT4;
   TCNT4 = 0;
}

/*!
 Interrupt service routine for handling the TIMER4 overflow.
 If this occurs then the speed sensor has not interrupted during the count up of TIMER 4.
*/
ISR(TIMER4_OVF_vect)
{
   _motor_speed_timer_ticks = 0xFFFF;
}

#endif /* DASH_BOARD */