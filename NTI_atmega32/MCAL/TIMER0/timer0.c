/*
 * timer0.c
 *
 * Created: 2/26/2023 10:55:31 AM
 *  Author: ncm
 */
/***************************************************************
 *  Includes
 ****************************************************************/
#include "../LIB/std_types.h"
#include "../LIB/register.h"
#include "../LIB/bit_math.h"
#include "timer0_interface.h"
#include "timer0_cfg.h"
void (*T0_OC_CallBackFun)();
void (*T0_OVF_CallBackFun)();

/***************************************************************
 *  Timer0 APIs
 ****************************************************************/

/*****************************************************************
 *   @param T0_MODE_t
 *   @brief This function used to initialize timer0 with mode
 *   @retval void
 *****************************************************************/
void T0_voidInit()
{
    /* 1- Set mode */
    CLEAR_BIT(TCCR0, 3);
    CLEAR_BIT(TCCR0, 6);
    /*first bit at bit6 WGM00 */
    TCCR0 |= ((TIM0_MOD << 6) & 0x40);
    /* second bit at bit3 WGM01 */
    TCCR0 |= (((TIM0_MOD >> 1) << 3) & 0x08);
}

void T0_voidEnableInteruptOV()
{

    /* TOV0 enable */
    SET_BIT(TIMSK, 0);
}

void T0_voidEnableInterruptOC()
{
    /* OCF0 enable */
    SET_BIT(TIMSK, 1);
}

void T0_voidStart()
{
    /* clear first 3 bits in TCCR0 then put value of TIM0_CLOCK_SELECT */
    TCCR0 &= ~(0x07);
    TCCR0 |= (TIM0_CLOCK_SELECT & 0x07);
}

void T0_voidStop()
{
    TCCR0 &= ~(0x07);
}

void T0_voidSetTimerReg(u8 timValue)
{
    TCNT0 = timValue;
}

void T0_voidSetOutputCompareReg(u8 value)
{
    OCR0 = value;
}

u8 T0_u8ReadTimer()
{
    return TCNT0;
}

void T0_voidWait_us(u64 period)
{
    u32 NumOfOverflows = 0;
    u8 T0preload = 0;

    u64 DesiredTicks, requiredNumOfOverflows;
    /* Calculate tick time*/

    DesiredTicks = (u64)period / (f32)TickTime;

    if (DesiredTicks < TIMER0_MAX_TICKS)
    {
        T0preload = TIMER0_MAX_TICKS - DesiredTicks;
        NumOfOverflows = 0;
    }
    else if (DesiredTicks == TIMER0_MAX_TICKS)
    {
        T0preload = 0;
        NumOfOverflows = 1;
    }
    else if (DesiredTicks > TIMER0_MAX_TICKS)
    {
        /* Calculate pre-load and number of overflows */
        requiredNumOfOverflows = ((u64)DesiredTicks * 100) / TIMER0_MAX_TICKS; // scaled x100 to get fraction

        NumOfOverflows = requiredNumOfOverflows / 100;

        // Method 1  --> prload for every *T0preload overflow
        if ((requiredNumOfOverflows - NumOfOverflows * 100) > 0)
        {
            NumOfOverflows++;
        }
        // *T0preload = TIMER0_MAX_TICKS - (fraction *  TIMER0_MAX_TICKS /100 )
        T0preload = TIMER0_MAX_TICKS - DesiredTicks / NumOfOverflows;
    }
    while (NumOfOverflows)
    {
        TCNT0 = T0preload;

        while (!CHECK_BIT(TIFR, 0))
            ;
        SET_BIT(TIFR, 0);

        NumOfOverflows--;
    }
}
void T0_voidSetCallbackOV(pf copyofCB)
{
    T0_OVF_CallBackFun = copyofCB;
}
void T0_voidSetCallbackOC(pf copyofCB)
{
    T0_OC_CallBackFun = copyofCB;
}
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (T0_OC_CallBackFun != NULL)
    {
        T0_OC_CallBackFun();
    }
}

/*
 *		 @fun			 : TIMER0_SetOutputComparePinMode
 *		 @Description	 : Set Output Compare Pin Mode according to @ref  TIMER0_OC0_MOd
 *						   The OC0 value will not be visible on the port pin unless
 *						   the data direction for the pin is set to output
 *
 */
void T0_voidSetOC0Mode(OC0_MOd_t MODE)
{
    /* Set bit PB2 as output if connected */
    if (MODE > 0)
    {
        SET_BIT(DDRB, 3);
    }

    /* Set mode of OC0 pin mode
       COM01 bit5   COM00 bit4  in RCCR0
     */
    TCCR0 &= ~(0x30);
    TCCR0 |= ((MODE << 4) & 0x30);
}
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (T0_OVF_CallBackFun != NULL)
    {
        T0_OVF_CallBackFun();
    }
}
