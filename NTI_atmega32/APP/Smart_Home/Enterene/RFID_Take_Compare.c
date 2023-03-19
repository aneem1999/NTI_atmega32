/*
 * RFID_Take_Compare.c
 *
 * Created: 3/18/2023 10:16:34 AM
 *  Author: ncm
 */

#include "../HAL/LED/led.h"
#include "../HAL/LCD/LCD.h"

#include "string.h"
#define NUM_OF_USERS 1

u8 ID_Arr[][4] = {{39, 132, 72, 214}};
char *NAME_Arr[] = {"Jo"};

u8 Take_Compare_RFID(u8 *index)
{

    u8 byte;
    u8 buffer[4];
    u8 state = 0;

    byte = DetectCard();

    if (byte == 1)
    {
        GetCardId(buffer);
        for (u8 i = 0; i < NUM_OF_USERS; i++)
        {
            if (memcmp(buffer, ID_Arr[i], 4) == 0)
            {
                *index = i;
                state = 1;
                return state;
            }
        }

        state = 2;
    }
    else
    {
        state = 0;
    }

    return state;
}