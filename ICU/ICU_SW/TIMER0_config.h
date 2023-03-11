




#ifndef _TIMER0_CONFIG_H_
#define _TIMER0_CONFIG_H_





/*********************************************/
/* Here you can choose the prescaler factor  */
/* You have 7 options                        */
/* 0, 1, 8, 64, 256, 1024, EXTERNAL_FALLING  */
/* or EXTERNAL_RISING                        */
/* 0 is no clock                             */
/*********************************************/
#define TIMER0_PRESCALER            1024



/********************************************/
/* This is to choose the timer mode         */
/* There are 4 options                      */
/* NORMAL, PWM_PHASE_CORRECT, CTC, FAST_PWM */
/********************************************/
#define MODE                       NORMAL




  




#endif
