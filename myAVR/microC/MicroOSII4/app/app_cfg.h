/*
*************************************************************************************************************
*                                APPLICATION SPECIFIC  CONFIGURATION FILE
*
*                                (c) Copyright 2007, Micrium, Weston, FL
*                                          All Rights Reserved
*
* File : APP_CFG.H
* By   : Fabiano Kovalski
* By	   : Ib Havn ported to GNU avr-gcc ATMEGA2560, 2010
*************************************************************************************************************
*/

/*
**************************************************************************************************************
*                                               STACK SIZES
**************************************************************************************************************
*/

#define  OS_TASK_START_STK_SIZE          240
#define  OS_TASK_1_STK_SIZE              240
#define  OS_TASK_2_STK_SIZE              240
#define  OS_TASK_3_STK_SIZE              240

/*
**************************************************************************************************************
*                                             TASK PRIORITIES
**************************************************************************************************************
*/

#define  OS_TASK_TMR_PRIO                  5
#define  OS_TASK_START_PRIO                6

#define  OS_TASK_1_PRIO                    8       // gathering data from sensors
#define  OS_TASK_2_PRIO                    9        // control
#define  OS_TASK_3_PRIO                    10        // display
