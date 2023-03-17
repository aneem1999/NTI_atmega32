/*
 * Enterence_Control.c
 *
 * Created: 3/17/2023 10:16:33 AM
 *  Author: ncm
 */

/************************************************************
 *      Includes
 *************************************************************/
#include "../HAL/LED/led.h"
#include "../HAL/Ultrasonic_HC_SR04/US_HC_SR04.h"
#include "../HAL/SERVO_MOTOR/servo.h"
#include "../SERVICES/Delay/TD_delay.h"
#include "../HAL/KEYPAD/keypad.h"
#include <string.h>

/***************************************************************
 *   MACROS
 */

#define DETECT_DISTANCE_MIN 50
#define MAX_TRYING_NUM 3

/***************************************************************
 *   Global Variables
 */

u8 Gp_Entered_Num;

/***************************************************************
 *   impelmention
 */

/******************************************************************/
/******************************************************************/

u8 Dpasswords[][5] = {{1, 1, 1, 1}, {1, 1, 1, 0}};
u8 password_Buffer[6];
void keypad_take_passwod()
{
    for (u8 i = 0; i < 5; i++)
    {
        while (GetKeyPressed(&password_Buffer[i], Keypad_1) == KEY_PRESSED)
            ;
    }
}

void Clear_Buffer()
{
    for (u8 i = 0; i < 5; i++)
    {
        password_Buffer[i] = 0;
    }
}

u8 arrCmp()
{
}

u8 VerfiyPassword()
{

    for (u8 i; i < 2; i++)
    {
        if (0 == strcmp(password_Buffer, Dpasswords))
        {

            return 1;
        }
    }

    return 0;
}
/****************************************************************/
/******************************************************************/

/* Init entrance  */
void Entrance_Init(void)
{
    /* Init UltraSonic Init led */
    US_voidInit();
    /* Init servo  */
    SERVO_voidInit();

    /* Init led */
    led_viInit();

    /* Init Entrance method (FP/RFID/Keypad) */
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    KeyPad_init();

    /* Init Communication metod */
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////

    /* Init Display */
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
}

void Entrance_Start()
{
    u8 detectedDistance_1 = 0, detectedDistance_2 = 0;
    u8 reg_State = 0, TryingNun = 0;
    detectedDistance_1 = US_u8dRead_Distance_cm(US_CHANNEL_0);

    if (detectedDistance_1 > DETECT_DISTANCE_MIN)
    {
        /* Yellow Led On */
        led_viOn(LED_YELLOW);
        /* RED Led OFF */
        led_viOff(LED_RED);
        /* Green Led OFF */
        led_viOff(LED_GREEN);

        /* Take registery */
        /////////////////////////////////////////////////
        /////////////////////////////////////////////////
        /////////////////////////////////////////////////
        keypad_take_passwod();

        while ((reg_State == 0 || (TryingNun <= MAX_TRYING_NUM)))
        {
            TryingNun++;
            if (TryingNun == MAX_TRYING_NUM)
            {
                /* RED Led ON */
                led_viOn(LED_RED);

                /* Blocking massege  massege  */
                /////////////////////////////////////////////////
                /////////////////////////////////////////////////
                /////////////////////////////////////////////////

                /* delay 5 sec to take second registry  */
                TD_delay_ms(5000);
                break;
            }
            else
            {
                /* Yellow Led Off */
                led_viOFF(LED_YELLOW);
                /* RED Led ON */
                led_viOn(LED_RED);

                /* Try again massege  */
                /////////////////////////////////////////////////
                /////////////////////////////////////////////////
                /////////////////////////////////////////////////

                /* delay 2 sec to take second registry  */
                TD_delay_ms(2000);
                /* RED Led OFF */
                led_viOff(LED_RED);
                /* Take second registery */
                /////////////////////////////////////////////////
                /////////////////////////////////////////////////
                /////////////////////////////////////////////////
            }
        }

        if (reg_State == 1)
        {
            Gp_Entered_Num++;
            /* RED Led ON */
            led_viOn(LED_GREEN);

            /* Welcome  massege  */
            /////////////////////////////////////////////////
            /////////////////////////////////////////////////
            /////////////////////////////////////////////////

            /* open gate */
            /* wait until US 2 read */
            detectedDistance_2 = US_u8dRead_Distance_cm(US_CHANNEL_2);

            /* Send User ID and state to */
        }
    }
}