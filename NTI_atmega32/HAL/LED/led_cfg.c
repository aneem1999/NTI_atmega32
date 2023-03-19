/*
 * led_cfg.c
 *
 * Created: 2/17/2023 3:25:56 PM
 *  Author: ncm
 */

#include "led_cfg.h"

LED_Config_t ledsConfigurations[] =
	{
		{LED_GREEN, DIO_PORTA, DIO_PIN4, LED_ACTIVE_HIGH},
		{LED_YELLOW, DIO_PORTA, DIO_PIN6, LED_ACTIVE_HIGH},
		{LED_RED, DIO_PORTB, DIO_PIN7, LED_ACTIVE_HIGH},
		{LED_BLUE, DIO_PORTA, DIO_PIN5, LED_ACTIVE_HIGH},
		{BUZZER, DIO_PORTC, DIO_PIN6, LED_ACTIVE_HIGH}

};

u8 ledsCount = sizeof(ledsConfigurations) / sizeof(LED_Config_t);
