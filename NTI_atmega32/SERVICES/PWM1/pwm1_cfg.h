/*
 * pwm1.h
 *
 * Created: 3/13/2023 9:30:12 AM
 *  Author: ncm
 */

#ifndef PWM1_H_
#define PWM1_H_

/* PWM1_MODE Select*/

#define PWM1_PHASE_CORRECT_10BIT 3
#define PWM1_FAST_10BIT 7
#define PWM1_FAST_TOP_ICT1 14

#define PWM1_MODE PWM1_FAST_TOP_ICT1

/* PWM1_POLARITY Select */
#define NON_INVERTING 2
#define INVERTING 3

#define PWM1_POLARITY NON_INVERTING

/* TOP value in  mode 3 , 7*/
#define PWM1_TOP 0x03ff

/* in other modes*/
#define PWM1_FREQ 50

#endif /* PWM1_H_ */