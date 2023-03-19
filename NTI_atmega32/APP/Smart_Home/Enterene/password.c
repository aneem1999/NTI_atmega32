/*
 * password.c
 *
 * Created: 3/17/2023 2:12:26 PM
 *  Author: ncm
 */

/******************************************************************/

/******************************************************************/
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/LED/led.h"
#include "../HAL/LCD/LCD.h"

u8 Dpasswords[][5] = {{1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}};
u8 password_Buffer[6];

void Clear_Buffer()
{
    for (u8 i = 0; i < 5; i++)
    {
        password_Buffer[i] = 0;
    }
}

u8 arrCmp(u8 *arr1, u8 *arr2)
{
    for (u8 i = 0; i < 5; i++)
    {
        if (arr1[i] != arr2[i])
            return 0;
    }

    return 1;
}

u8 keypad_take_passwod()
{
    u8 i = 0;
    while (i < 5)
    {
        while (GetKeyPressed(&password_Buffer[i], Keypad_1) == KEY_NOT_PRESSED)
            ;
        led_viOn(BUZZER);
        led_viOn(LED_BLUE);

        while (GetKeyPressed(&password_Buffer[i], Keypad_1) == KEY_PRESSED)
            ;
        led_viOff(BUZZER);
        led_viOff(LED_BLUE);

        LCD_GoToXY(2, 4);
        LCD_WriteData(password_Buffer[i]);
        i++;
    }

    for (u8 i = 0; i < 2; i++)
    {
        if (0 == arrCmp(password_Buffer, Dpasswords))
        {
            Clear_Buffer();
            return 0;
        }
    }

    Clear_Buffer();
    return 1;
}
/****************************************************************/
/******************************************************************/
