/*
 * rc_servo.h
 *
 * Created: 02-04-2014 14:53:36
 *  Author: IHA
 */ 


#ifndef RC_SERVO_H_
#define RC_SERVO_H_

#include <stdint.h>

void init_rc_servo();
void rc_servo(uint8_t id, int8_t position);

#endif /* RC-SERVO_H_ */