/*
 * timer0.c
 *
 * Created: 2/26/2023 10:55:31 AM
 *  Author: Ahmed Naeem
 */

/***************************************************************
 *  Includes
 ****************************************************************/
#include "../LIB/std_types.h"
#include "../LIB/register.h"
#include "../LIB/bit_math.h"
#include "timer1_interface.h"
#include "timer1_cfg.h"

void (*T1_OCA_CallBackFun)();
void (*T1_OCB_CallBackFun)();
void (*T1_IC_CallBackFun)();
void (*T1_OVF_CallBackFun)();

/***************************************************************
 *  Timer0 APIs
 ****************************************************************/

/*****************************************************************
 *   @param t1ModeMask  values from 0 --> 15 according to cfg file
 *   @brief This function used to initialize timer0 with mode
 *   @retval void
 *****************************************************************/
void T1_voidInit(u8 t1ModeMask)
{
    if (t1ModeMask < 16)
    {
        /* Set mode WGM11 , WGM10  */
        TCCR1A &= ~(3 << 0);
        TCCR1A |= (t1ModeMask & 0x3);
        /* Set mode WGM13 , WGM12  */
        TCCR1B &= ~(3 << 3);
        TCCR1B |= ((t1ModeMask & 0xC) << 1);
    }
}

void T1_voidStart()
{
    TCCR1B &= ~(0x07);
    TCCR1B |= (TIM1_CLOCK_SELECT & 0x07);
}

void T1_voidStop()
{
    TCCR1B &= ~(0x07);
}

void T1_voidSetTimerReg(u16 timValue)
{
    TCNT1 = timValue;
}

void T1_voidSet_OutputCompareAReg(u16 value)
{
    OCR1A = value;
}

void T1_voidSet_OutputCompareBReg(u16 value)
{
    OCR1B = value;
}

void T1_voidSet_InputCapturReg(u16 value)
{
    ICR1 = value;
}
u16 T1_u16ReadTimer()
{
    return TCNT1;
}

/*
 *		 @fun			 : TIMER0_SetOutputComparePinMode
 *		 @Description	 : Set Output Compare Pin Mode according to @ref  TIMER0_OC0_MOd
 *						   The OC0 value will not be visible on the port pin unless
 *						   the data direction for the pin is set to output
 *
 */
void T1_voidSet_OC1AMode(OC_MOd_t MODE)
{
    /* Set bit PB2 as output if connected */
    if (MODE > 0)
    {
        SET_BIT(DDRD, 5);
    }

    TCCR1A &= ~(0xC0);
    TCCR1A |= ((MODE << 6) & 0xC0);
}

void T1_voidSet_OC1BMode(OC_MOd_t MODE)
{
    /* Set bit PB2 as output if connected */
    if (MODE > 0)
    {
        SET_BIT(DDRD, 4);
    }

    TCCR1A &= ~(0x30);
    TCCR1A |= ((MODE << 4) & 0x30);
}

void T1_voidEnable_InteruptOVF(void (*copyofFun)())
{
    /* TOV0 enable */
    SET_BIT(TIMSK, 2);

    T1_OVF_CallBackFun = copyofFun;
}

void T1_voidEnable_InterruptOCA(void (*copyofFun)())
{
    /* OCA enable */
    SET_BIT(TIMSK, 4);

    T1_OCA_CallBackFun = copyofFun;
}

void T1_voidEnable_InterruptOCB(void (*copyofFun)())
{
    /* OCB enable */
    SET_BIT(TIMSK, 3);

    T1_OCB_CallBackFun = copyofFun;
}

void T1_voidEnable_InterruptIC(void (*copyofFun)())
{
    /* OCA enable */
    SET_BIT(TIMSK, 5);

    T1_IC_CallBackFun = copyofFun;
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
    if (T1_OVF_CallBackFun != NULL)
    {
        T1_OVF_CallBackFun();
    }
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
    if (T1_OCB_CallBackFun != NULL)
    {
        T1_OCB_CallBackFun();
    }
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
    if (T1_OCA_CallBackFun != NULL)
    {
        T1_OCA_CallBackFun();
    }
}

void __vector_(void) __attribute__((signal));
void __vector_(void)
{
    if (T1_IC_CallBackFun != NULL)
    {
        T1_IC_CallBackFun();
    }
}
