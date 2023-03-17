/*
 * pwm1.c
 *
 * Created: 3/13/2023 9:29:55 AM
 *  Author: ncm
 */

#include "../LIB/std_types.h"
#include "../MCAL/TIMER1/timer1_interface.h"
#include "pwm1_cfg.h"
#include "pwm1_interface.h"

void PWM1_voidInit_Channel_A(void)
{

    T1_voidInit(PWM1_MODE);
    T1_voidSet_OC1AMode(PWM1_POLARITY);

#if (PWM1_MODE == PWM1_FAST_TOP_ICT1)
    T1_voidSet_InputCapturReg(TOP_VALUE);
#endif
}
void PWM1_voidInit_Channel_B(void)
{
    T1_voidInit(PWM1_MODE);
    T1_voidSet_OC1BMode(PWM1_POLARITY);
}

void PWM1_voidSetDuty_Channel_A(u16 duty)
{
    u16 Reg_Value = 0;

#if PWM1_MODE == PWM1_PHASE_CORRECT_10BIT
#if PWM1_POLARITY == NON_INVERTING
    Reg_Value = (duty * PWM1_TOP) / 1000;

#elif PWM1_POLARITY == INVERTING
    Reg_Value = ((1000 - duty) * PWM1_TOP) / 1000;
#endif

#endif

#if (PWM1_MODE == PWM1_FAST_10BIT)
#if PWM1_POLARITY == NON_INVERTING
    Reg_Value = (duty * (PWM1_TOP + 1)) / 1000;

#elif PWM1_POLARITY == INVERTING
    Reg_Value = ((1000 - duty) * (PWM1_TOP + 1)) / 1000;
#endif

#endif

#if (PWM1_MODE == PWM1_FAST_TOP_ICT1)

#if PWM1_POLARITY == NON_INVERTING
    Reg_Value = (duty * (TOP_VALUE + 1)) / 1000;

#elif PWM1_POLARITY == INVERTING
    Reg_Value = ((1000 - duty) * (TOP_VALUE + 1)) / 1000;
#endif

#endif
    T1_voidSet_OutputCompareAReg(Reg_Value);
}

/* duty in x1000 scale*/
void PWM1_voidSetDuty_Channel_B(u16 duty)
{
    u16 Reg_Value = 0;

#if PWM1_MODE == PWM1_PHASE_CORRECT_10BIT
#if PWM1_POLARITY == NON_INVERTING
    Reg_Value = (duty * PWM1_TOP) / 1000;

#elif PWM1_POLARITY == INVERTING
    Reg_Value = ((1000 - duty) * PWM1_TOP) / 1000;
#endif

#endif

#if (PWM1_MODE == PWM1_FAST_10BIT)
#if PWM1_POLARITY == NON_INVERTING
    Reg_Value = (duty * (PWM1_TOP + 1)) / 1000;

#elif PWM1_POLARITY == INVERTING
    Reg_Value = ((1000 - duty) * (PWM1_TOP + 1)) / 1000;
#endif

#endif

#if (PWM1_MODE == PWM1_FAST_TOP_ICT1)

#if PWM1_POLARITY == NON_INVERTING
    Reg_Value = (duty * (TOP_VALUE + 1)) / 1000;

#elif PWM1_POLARITY == INVERTING
    Reg_Value = ((1000 - duty) * (TOP_VALUE + 1)) / 100;
#endif

#endif

    T1_voidSet_OutputCompareBReg(Reg_Value);
}

void PWM1_voidStart()
{
    T1_voidStart();
}
void PWM1_voidStop(void)
{
    T1_voidStop();
}