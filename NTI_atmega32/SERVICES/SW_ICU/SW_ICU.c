/*
 * SW_ICU.c
 *
 * Created: 3/16/2023 8:29:38 AM
 *  Author: ncm
 */

#include "SW_ICU.h"
#include "../HAL/LED/led.h"

static volatile u16 ICU_T2_OVF = 0;
static volatile u8 SW_ICU_Flag = 0;
static volatile u8 SW_ICU_Done_Read_Flag = 0;

static volatile u8 SW_ICU_Ton = 0;
static volatile u8 SW_ICU_Toff = 0;

static EXTI_num_t EXTIx = 0;

void ICU_T2_OVF_CallBack()
{

    ICU_T2_OVF++;
}

void ICU_EXTI_CallBack()
{

    if (SW_ICU_Flag == 0)
    {
        SW_ICU_Done_Read_Flag = 0;
        TCNT2 = 0;
        ICU_T2_OVF = 0;

        T2_voidStart();
        EXTI_Init(EXTIx, FALLING_EDGE);
        SW_ICU_Flag = 1;
    }
    else if (SW_ICU_Flag == 1)
    {

        SW_ICU_Done_Read_Flag = 0;
        SW_ICU_Ton = (TCNT2 + ICU_T2_OVF * 256) * T2_TICK_TIME;
        TCNT2 = 0;
        ICU_T2_OVF = 0;
        EXTI_Init(EXTIx, RISINING_EDGE);
        SW_ICU_Flag = 2;
    }
    else if (SW_ICU_Flag == 2)
    {
        led_viToggle(LED_RED);

        SW_ICU_Toff = (TCNT2 + ICU_T2_OVF * 256) * T2_TICK_TIME;
        TCNT2 = 0;
        ICU_T2_OVF = 0;
        EXTI_Init(EXTIx, FALLING_EDGE);
        SW_ICU_Done_Read_Flag = 1;
        SW_ICU_Flag = 1;
    }
}

void SW_ICU_voidInit(EXTI_num_t EXTI_num)
{
    EXTIx = EXTI_num;
    /* init T2 */
    T2_voidInit();
    /* enable ovf interrupt*/
    GIE_ENABLE();
    T2_voidSetCallbackOV(ICU_T2_OVF_CallBack);
    T2_voidEnableInteruptOV();

    // init EXTI0 at rising edge
    EXTI_voidSetCallbackFunction(EXTIx, ICU_EXTI_CallBack);
    EXTI_Init(EXTIx, RISINING_EDGE);
}

u16 SW_ICU_u16ReadTon_us()
{
    while (SW_ICU_Done_Read_Flag == 0)
        ;
    return (SW_ICU_Ton * T2_TICK_TIME);
}

u16 SW_ICU_u16ReadToff_us()
{
    while (SW_ICU_Done_Read_Flag == 0)
        ;
    return (SW_ICU_Toff * T2_TICK_TIME);
}

void SW_ICU_voidStop()
{
    T2_voidStop();
    EXTI_DeInit(EXTIx);
}