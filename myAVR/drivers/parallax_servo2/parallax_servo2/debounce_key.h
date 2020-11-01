
/*!
* \file debounce_key.h
* \brief Header of debounce key functions.
*/

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

// compiler checks for value passed to function, constants ALWAYS in upper-case
typedef enum {SENSE_FALLING, SENSE_RAISING, SENSE_BOTH} sense_mode_t;

// #define SENSE_FALLING 0
// #define SENSE_RAISING 1
// #define SENSE_BOTH 2

void init_debounce_key_interrupt(sense_mode_t sense_mode);
void checkStartButton();


#endif /* INTERRUPTS_H_ */