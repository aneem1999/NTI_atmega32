/*
 * dht.c
 *
 * Created: 3/13/2023 7:52:43 PM
 *  Author: ncm
 */

#define F_CPU 16000000U
#include "util/delay.h"
#include "../LIB/bit_math.h"
#include "../MCAL/DIO/dio.h"
#include "dht.h"
#include "dht_cfg.h"

#ifdef DEBUG
#include <stdlib.h>
#include "../HAL/LCD/LCD.h"
#include "../HAL/LED/led.h"
#endif

void DHT_voidRequest(void)
{
    /* Init pin as output */
    dio_vidConfigChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN, OUTPUT);
    /*
    the programme of MCU will set Data Single-bus voltage level from high to low
    and this process must take at least 18ms to ensure DHT’s detection of MCU's signal,
    then MCUwill pull up voltage and wait 20-40us for DHT’s response.
    */
    dio_vidWriteChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN, STD_LOW);
    _delay_ms(20);
    dio_vidWriteChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN, STD_HIGH);
}

void DHT_voidResponse(void)
{
    /* Init pin as input */
    dio_vidConfigChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN, INPUT);
    /*
    Once DHT detects the start signal, it will send out a low-voltage-level response signal,
     which lasts 80us*/
    while (dio_dioLevelReadChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN) == STD_HIGH)
        ;

    /*
    Then the programme of DHT sets Data Single-bus voltage level from low to high and
    keeps it for 80us for DHT’s preparation for sending data.*/
    while (dio_dioLevelReadChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN) == STD_LOW)
        ;
    while (dio_dioLevelReadChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN) == STD_HIGH)
        ;
}

u8 DHT_u8Recive(void)
{
    u8 data = 0;
    for (u8 i = 0; i < 8; i++)
    {
        /* check received bit 0 or 1 */
        while (dio_dioLevelReadChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN) == STD_LOW)
            ;

        _delay_us(30);
        /* if high pulse is greater than 30ms */
        if (dio_dioLevelReadChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN) == STD_HIGH)
        {
            /* then its logic HIGH */
            data = (data << 1) | (0x01);
        }
        else
        { /* otherwise its logic LOW */
            data = (data << 1);
        }
        while (dio_dioLevelReadChannel(DHT_CONTROL_PORT, DHT_CONTROL_PIN) == STD_HIGH)
            ;
    }
    return data;
}

DHT_Read_t DHT_enuReadData(u16 *RH_Value, u16 *Temp_Value)
{
    DHT_Read_t DHT_State = ERROR_READ;
    u8 I_RH = 0, D_RH = 0, I_Temp = 0, D_Temp = 0, CheckSum = 0;
    char data[5];
    DHT_voidRequest();  /* send start pulse */
    DHT_voidResponse(); /* receive response */

    I_RH = DHT_u8Recive(); /* store first eight bit in I_RH */

    D_RH = DHT_u8Recive(); /* store next eight bit in D_RH */

    I_Temp = DHT_u8Recive(); /* store next eight bit in I_Temp */

    D_Temp = DHT_u8Recive(); /* store next eight bit in D_Temp */

    CheckSum = DHT_u8Recive(); /* store next eight bit in CheckSum */

#ifdef DEBUG

    itoa((I_RH + D_RH + I_Temp + D_Temp), data, 10);
    LCD_GoToXY(3, 0);
    LCD_WriteString(data);
    LCD_WriteString(" == ");
    itoa(CheckSum, data, 10);
    LCD_WriteString(data);

#endif

    if ((I_RH + D_RH + I_Temp + D_Temp) == CheckSum)
    {
        *RH_Value = (I_RH << 8) + D_RH;
        *Temp_Value = (I_Temp << 8) + D_Temp;
        DHT_State = SUCCESS_READ;
    }
    else
    {
        DHT_State = ERROR_READ;
    }

    return DHT_State;
}
