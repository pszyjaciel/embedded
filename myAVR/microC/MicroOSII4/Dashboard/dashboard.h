/*
 * dashboard.h
 *
 * Created: 11-04-2012 08:08:32
 * Version 0.0.1 Alpha
 *  Author: IHA
 */


#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#ifdef DASH_BOARD
/*! \brief  Initialize the Dashboard driver.
 *   This function initialize the MCU to be ready for controlling the hardware
 *   located on the Dashboad.
 *   \note   This has to be called only once in the start of the program.
 */
void db_init();

/*! \brief  Activates the leds showing the signal indicator.
 *   This function turns off both leds, or turn on one of them depending on the parameter.
 *  \param  dir	0: off; 1: Left, 2: Right.
 */
void db_signal_indicator(uint8_t dir);

/*! \brief  Returns the state of the gear shifter switch.
 *   This function polls the state of the gear shifter switch.
 *  \return  0: middle; 1: DOWN; 2: UP
 */
uint8_t db_gear_shifter();

/*! \brief  Returns the state of the left/right signal switch.
 *   This function polls the state of the left/right signal switch.
 *  \return  0: middle; 1: LEFT; 2: RIGHT
 */
uint8_t db_signal_shifter();

/*! \brief  Returns the position of the gas pedal.
 *   This function use the ADC to measure the position of potentiometer
 *   that acts as the gas pedal.
 *  \return  10 bit value from 0-1023.
 */
uint16_t db_gas_pedal();

/*! \brief  Activates the led bar showing the temparature.
 *	 No of leds turned on = percent/10.
 *  \param  percent 0: no leds; 100; all leds on [0..100]
 */
void db_temp_indicator(uint8_t percent);

/*! \brief  Returns the temperature measured with the temperature sensor.
*   This function use the one-wire bus to retrieve the temperature from the sensor.
*  \return  temperature in C - resolution 0.5 degree.
*/
int16_t db_temp_sensor();

/**
 *	\brief Sets the speed and direction of the motor connected to the specified motor output/H-Bridge.
 *	\param motor: specifies the motor output on the dashboard board [0..1].
 *	\param speed in percent from -100 to 100 where -100 is full speed CCW, and 100 is full speed CW.\n
 *   0 will release the motor/free run.
 */
void db_motor_speed(uint8_t motor, int8_t percent);

/*! \brief Returns the speed of the motor on the Dashboard.
 *   \note Max RPM is 5000, Min RPM is 9
 *  \return  speed in RPM [0..5000]
 */
uint16_t db_speed_sensor();

/*! \brief  Handles the one-wire interface.
 *   Must be called continuously to handle the one-wire state machine.
 *   Could be called in App_TaskIdleHook().
 */
void db_handle_one_wire();

#endif /* DASH_BOARD */

#endif /* DASHBOARD_H_ */