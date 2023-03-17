/*
 * servo.c
 *
 * Created: 3/13/2023 11:06:30 AM
 *  Author: ncm
 */

#include "../LIB/std_types.h"
#include "../SERVICES/PWM1/pwm1_interface.h"
#include "servo.h"

void SERVO_voidInit(void)
{
	PWM1_voidInit_Channel_A();
	SERVO_voidGotoAngle(0);
}

void SERVO_voidGotoAngle(s8 angle)
{
	u16 duty = 0;
	if ((angle <= 90) && (angle > 0))
	{
		duty = 120 - (50 - ((f32)(5 * angle) / 9.0));
	}
	else if ((angle < 0) && (angle >= -90))
	{
		duty = angle / 2 + 70;
	}
	else if (angle == 0)
	{
		duty = 70;
	}

	PWM1_voidSetDuty_Channel_A(duty);
	PWM1_voidStart();
}