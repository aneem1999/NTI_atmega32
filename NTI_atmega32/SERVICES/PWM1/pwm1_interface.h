/*
 * pwm1_interface.h
 *
 * Created: 3/13/2023 9:30:37 AM
 *  Author: ncm
 */

#ifndef PWM1_INTERFACE_H_
#define PWM1_INTERFACE_H_

#if PWM1_MODE == PWM1_FAST_TOP_ICT1
#define TOP_VALUE ((F_CPU / ((u32)PWM1_FREQ * (u32)TIM1_PRESCALER_VALUE)) - 1)
#endif

void PWM1_voidInit_Channel_A(void);
void PWM1_voidInit_Channel_B(void);

void PWM1_voidSetDuty_Channel_A(u16 duty);
void PWM1_voidSetDuty_Channel_B(u16 duty);

void PWM1_voidStart();

void PWM1_voidStop(void);

#endif /* PWM1_INTERFACE_H_ */