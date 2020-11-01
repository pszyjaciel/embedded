
#ifndef MYSERVO_H_
#define MYSERVO_H_

#define F_CPU 7372800UL	
#define PRESCALER 64

#define TOP (F_CPU/50/(2*PRESCALER))					// 50Hz
#define MIN ((F_CPU*0.75/2/PRESCALER/1000) + TOP)
#define CENTER ((F_CPU*1.5/2/PRESCALER/1000) + TOP)
#define MAX ((F_CPU*2.25/2/PRESCALER/1000) + TOP)		// brackets make the integer

#include <avr/io.h>
#include <stdlib.h>


void setPrescaler(uint16_t speed);
void init_rc_servo();
void rc_servo2(int8_t angle);
void rc_servo(int8_t percent);


#endif /* MYSERVO_H_ */