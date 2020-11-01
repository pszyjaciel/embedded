
// #define F_CPU 10000000L

#include  <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include  <app_cfg.h>
#include  <ucos_ii.h>

#include  <bsp.h>

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h> 

#include "..\unittest\minunit.h"
#include "../lcd_stk600.h"
#include "../servos/rc-servo.h"
#include "../ledbar/ledbar.h"
#include "../Aircraft/aircraft.h"
#include "../uart/myUart.h"
#include "../uart/myUtil.h"

