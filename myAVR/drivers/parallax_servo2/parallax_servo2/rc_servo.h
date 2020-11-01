
/*! @file rc_servo.h

@brief Header of rc-servo functions.
@author Pawel Kramarz
@defgroup servo_module Parallax Servo Driver

@{
@brief Servo Control functions.
Functions to manipulate the Servo driver
@}
*/

#ifndef RC_SERVO_H_
#define RC_SERVO_H_

#define F_CPU 7372800UL
#define PRESCALER 64

#define TOP (((F_CPU/50)/PRESCALER) - 1)		// 50Hz
#define MIN (TOP/(20/0.75))						// 20ms = 50Hz
#define CENTER (TOP/(20/1.5))					// brackets make the integer
#define MAX (TOP/(20/2.25))

#include <avr/io.h>

/**
* @ingroup servo_module
* @brief Set the prescaler with a predefined value
* The setPrescaler function sets the timer to a predefined value that is \a speed parameter. \n
* It modifies three lowest bits in TCCR1B register according to the datasheet <A HREF="../docs/p157.pdf"> page 157.</A>
* The function returns nothing.
* @param speed is one of 6 predefined speed values
* @return[void] nothing is returned
* @todo must be optimized next time. */
void setPrescaler(uint16_t speed);

/**
@ingroup servo_module
@brief Initialize the servo device
@return[void] no returning value */
void init_rc_servo();

/**
@ingroup servo_module
@brief This function positions the arm of the RC-Servo to the position specified by
the percent parameter, where the percentage can vary between -100 to 100. \n
-100 is the left position of the arm, 100 is the right position and 0
is the middle position. Thus 50 will give a position halfway to the right.
@param percent	is the position value
@return		no return */
void rc_servo(int8_t percent);


#endif /* RC_SERVO_H_ */