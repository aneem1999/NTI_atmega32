/*
 * system.c
 *
 * Created: 5/1/2023 7:05:11 PM
 *  Author: ncm
 */
#if 0
#define F_CPU 16000000U
#include "../../../SERVICES/FreeRTOS/FreeRTOSConfig.h"
#include "../../../SERVICES/FreeRTOS/FreeRTOS.h"
#include "../SERVICES/FreeRTOS/task.h"
#include "../SERVICES/FreeRTOS/semphr.h"
#include "../SERVICES/FreeRTOS/queue.h"

/************************************************************
 *      Includes
 *************************************************************/
#include "../HAL/LED/led.h"
#include "../HAL/Ultrasonic_HC_SR04/US_HC_SR04.h"
#include "../HAL/SERVO_MOTOR/servo.h"
#include "../HAL/LCD/LCD.h"
#include "../SERVICES/Delay/TD_delay.h"
#include "../HAL/KEYPAD/keyPad.h"
#include "../MCAL/USART/uart_interface.h"

#include "../HAL/OLED/OLED_interface.h"

#include "RFID_Take_Compare.h"

/***************************************************************
 *   Global Variables
 */

u8 G_Entered_Num;

/* Init entrance  */
void Entrance_Init(void)
{
    /* Init UltraSonic Init led */
    US_voidInit();

    /* Init servo  */
    SERVO_voidInit();
    OLED_ResetDisplay();

    /* Init led */
    led_viInit();

    /* Init Entrance method (FP/RFID/Keypad) */
    mcrf522_init();

    KeyPad_init();
    SPI_Init();

    /* Init Communication metod */
    UART_Init();

    /* Init Display */
    LCD_Init();
    OLED_vInit();

    SERVO_voidGotoAngle(0);
}

/***************************************************************
 *   Tasks
 */

void Entrance_Start()
{
    u8 detectedDistance_1 = 0, detectedDistance_2 = 0;
    u8 TryingNun = 0, Take_State = 0xff;
    u8 UserIndex = 0xff;

    detectedDistance_1 = US_u8dRead_Distance_cm(US_CHANNEL_0);

    while (detectedDistance_1 <= DETECT_DISTANCE_MIN)
    {
        /* Welcome and wait  massege  */
        OLED_ClearDisplay();

        LCD_ClearDisplay();
        LCD_GoToXY(0, 2);
        LCD_WriteString("Welcome");
        LCD_GoToXY(1, 0);
        LCD_WriteString("Enter Password ");
        OLED_sendStr_xy2("Welcome", 1, 1);
        OLED_sendStr_xy2("Enter Password", 2, 1);

        /* Yellow Led On */
        led_viOn(LED_YELLOW);
        /* RED Led OFF */
        led_viOff(LED_RED);
        /* Green Led OFF */
        led_viOff(LED_GREEN);

        /* Take registery */
        /////////////////////////////////////////////////
        /////////////////////////////////////////////////

        detectedDistance_1 = US_u8dRead_Distance_cm(US_CHANNEL_0);

        Take_State = Take_Compare_RFID(&UserIndex);

        if (Take_State == 1)
        {
            G_Entered_Num++;
            /* RED Led ON */
            led_viOn(LED_GREEN);
            led_viOff(LED_RED);

            /* Welcome  massege  */

            LCD_ClearDisplay();
            LCD_GoToXY(0, 2);
            LCD_WriteString("Welcome");
            OLED_sendStr_xy2("Welcome", 1, 1);

            LCD_GoToXY(1, 0);
            LCD_WriteString("Correct Password");
            OLED_sendStr_xy2("Correct Password", 2, 0);

            /* open gate */
            SERVO_voidGotoAngle(90);
            /* wait until US 2 read */
            detectedDistance_2 = US_u8dRead_Distance_cm(US_CHANNEL_1);
            while (detectedDistance_2 > DETECT_DISTANCE_MIN)
            {
                detectedDistance_2 = US_u8dRead_Distance_cm(US_CHANNEL_1);
            }
            /* close gate */
            SERVO_voidGotoAngle(0);

            /* SEND Index of user*/
            UART_TransmitBusyWait(UserIndex);
            break;
        }
        else if (Take_State == 2)
        {
            TryingNun++;
            if (TryingNun >= MAX_TRYING_NUM)
            {
                /* RED Led ON */
                led_viOn(LED_RED);

                /* Blocking massege */
                LCD_ClearDisplay();
                LCD_GoToXY(0, 2);
                LCD_WriteString("Try again");
                OLED_sendStr_xy2("TRY again after 5 secs", 1, 0);

                LCD_GoToXY(1, 0);
                LCD_WriteString("after 5 secs");

                /* delay 5 sec to take second registry  */
                TD_delay_ms(5000);
                break;
            }
            else
            {

                /* RED Led ON */
                led_viOn(LED_RED);

                /* Try again massege  */
                LCD_ClearDisplay();
                LCD_GoToXY(0, 2);
                LCD_WriteString("Wrong Password");
                LCD_GoToXY(1, 0);
                LCD_WriteString("Try again");
                OLED_sendStr_xy2(" Wrong PasswordTRY again ", 1, 1);

                /* delay 2 sec to take second registry  */
                TD_delay_ms(2000);
                /* RED Led OFF */
                led_viOff(LED_RED);
            }
        }
    }

    LCD_ClearDisplay();
    led_viOff(LED_RED);
    led_viOff(LED_YELLOW);
    led_viOff(LED_GREEN);
}


#endif