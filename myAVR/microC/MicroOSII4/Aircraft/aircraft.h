/*
 * aircraft.h
 *
 * Created: 12-04-2013 12:27:13
 *  Author: IHA
 */ 

#include <stdint.h>

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#define LED_YELLOW PB7
#define LED_RED PB6
#define LED_GREEN PB5
#define LED_ON 1
#define LED_OFF 0

void init_aircraft(void);

int16_t get_temp(void);
float get_x_acc(void);
float get_y_acc(void);
float get_z_acc(void);

void set_led(uint8_t led, uint8_t led_state);

#endif /* AIRCRAFT_H_ */