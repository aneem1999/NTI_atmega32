/*
 * US_Hc_SR04.c
 *
 * Created: 3/16/2023 10:51:27 AM
 *  Author: ncm
 */

/***********************************************************
 * Includes
 ************************************************************/
#include "../MCAL/DIo/dio.h"
#include "../SERVICES/Delay/TD_delay.h"
#include "../MCAL/TIMER2/timer2_interface.h"
#include "../MCAL/EXTI/EXTI_int.h"

#include "US_HC_SR04_cfg.h"
#include "US_HC_SR04.h"

static volatile u16 US_T2_OVF = 0;
static volatile u8 US_Flag = 0;
static volatile u8 US_Done_Read_Flag = 0;

static volatile u16 US_Ton = 0;

void US_T2_OVF_CallBack()
{

    US_T2_OVF++;
}

void US_EXTI_CallBack()
{

    if (US_Flag == 0)
    {
        TCNT2 = 0;
        US_T2_OVF = 0;
        US_Done_Read_Flag = 0;
        // US_Ton = 0;

        T2_voidStart();
        EXTI_Init(EXTI_0, FALLING_EDGE);

        US_Flag = 1;
    }
    else if (US_Flag == 1)
    {

        US_Ton = (TCNT2 + US_T2_OVF * 256) * T2_TICK_TIME;

        US_T2_OVF = 0;
        TCNT2 = 0;

        EXTI_Init(EXTI_0, RISINING_EDGE);
        T2_voidStop();

        US_Done_Read_Flag = 1;
        US_Flag = 0;
    }
}

void US_voidInit()
{
    /* init trig pin as output */
    u8 US_index = 0;
    for (US_index = 0; US_index < US_countChannels; US_index++)
    {
        dio_vidConfigChannel(US_arrChannels[US_index].TRIG_PORT_Num,
                             US_arrChannels[US_index].TRIG_PIN_Num, OUTPUT);
    }

    /* init T2 */
    T2_voidInit();
    /* enable ovf interrupt*/
    GIE_ENABLE();
    T2_voidSetCallbackOV(US_T2_OVF_CallBack);
    T2_voidEnableInteruptOV();

    // init EXTI0 at rising edge
    EXTI_voidSetCallbackFunction(EXTI_0, US_EXTI_CallBack);
    EXTI_Init(EXTI_0, RISINING_EDGE);
}

f32 US_u8dRead_Distance_cm(US_Channel_Num_t US_channel)
{
    f32 distance = 0;
    /*Trig pluse*/

    dio_vidWriteChannel(US_arrChannels[US_channel].TRIG_PORT_Num,
                        US_arrChannels[US_channel].TRIG_PIN_Num, STD_HIGH);
    /*wait 10 usec */
    TD_delay_us(10);
    dio_vidWriteChannel(US_arrChannels[US_channel].TRIG_PORT_Num,
                        US_arrChannels[US_channel].TRIG_PIN_Num, STD_LOW);
    // while (US_Flag != 1)
    //     ;

    TD_delay_ms(500);

    distance = US_Ton / 58.0;

    return distance;
}