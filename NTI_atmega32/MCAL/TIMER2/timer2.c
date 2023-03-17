/*
 * timer2.c
 *
 * Created: 2/26/2223 12:55:31 AM
 *  Author: ncm
 */
/***************************************************************
 *  Includes
 ****************************************************************/
#include "../LIB/std_types.h"
#include "../LIB/register.h"
#include "../LIB/bit_math.h"
#include "timer2_interface.h"
#include "timer2_cfg.h"

void (*T2_OC_CallBackFun)();
void (*T2_OVF_CallBackFun)();

/***************************************************************
 *  Timer2 APIs
 ****************************************************************/

/*****************************************************************
 *   @param T2_MODE_t
 *   @brief This function used to initialize timer2 with mode
 *   @retval void
 *****************************************************************/
void T2_voidInit()
{
    /* 1- Set mode */
    CLEAR_BIT(TCCR2, 3);
    CLEAR_BIT(TCCR2, 6);
    /*first bit at bit6 WGM20 */
    TCCR2 |= ((TIM2_MOD << 6) & (1<<6)) | ((TIM2_MOD << 2) & (1<<3)) ;
    /* second bit at bit3 WGM21 */
    //TCCR2 |= (((TIM2_MOD >> 1) << 3) & 0x28);
}

void T2_voidEnableInteruptOV()
{

    /* TOV2 enable */
    SET_BIT(TIMSK, 6);
}

void T2_voidEnableInterruptOC()
{
    /* OCF2 enable */
    SET_BIT(TIMSK, 7);
}

void T2_voidStart()
{
    /* clear first 3 bits in TCCR2 then put value of TIM2_CLOCK_SELECT */
    TCCR2 &= ~(0x7);
    TCCR2 |= (TIM2_CLOCK_SELECT & 0x7);
}

void T2_voidStop()
{
    TCCR2 &= ~(0x7);
}

void T2_voidSetTimerReg(u8 timValue)
{
    TCNT2 = timValue;
}

void T2_voidSetOutputCompareReg(u8 value)
{
    OCR2 = value;
}

u8 T2_u8ReadTimer()
{
    return TCNT2;
}


/*
 *		 @fun			 : TIMER2_SetOutputComparePinMode
 *		 @Description	 : Set Output Compare Pin Mode according to @ref  TIMER2_OC2_MOd
 *						   The OC2 value will not be visible on the port pin unless
 *						   the data direction for the pin is set to output
 *
 */
void T2_voidSetOC2Mode(OC2_MOd_t MODE)
{
    /* Set bit PB2 as output if connected */
    if (MODE > 2)
    {
        SET_BIT(DDRB, 3);
    }

    /* Set mode of OC2 pin mode
       COM21 bit5   COM22 bit4  in RCCR2
     */
    TCCR2 &= ~(0x3);
    TCCR2 |= ((MODE << 4) & 0x3);
}

void T2_voidSetCallbackOV(pf copyofCB)
{
    T2_OVF_CallBackFun = copyofCB;
}
void T2_voidSetCallbackOC(pf copyofCB)
{
    T2_OC_CallBackFun = copyofCB;
}
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
    if (T2_OC_CallBackFun != NULL)
    {
        T2_OC_CallBackFun();
    }
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
    if (T2_OVF_CallBackFun != NULL)
    {
        T2_OVF_CallBackFun();
    }
}
