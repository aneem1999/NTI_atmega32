/*
 * led.c
 *
 * Created: 2/17/2023 3:17:09 PM
 *  Author: Ahmed Naeem
 */ 

#include "led.h"
#include "led_cfg.h"

void led_viInit(void)
{
	u8 ledIndex=0;
	for(ledIndex=0 ; ledIndex < ledsCount ; ledIndex++)
	{
		dio_vidConfigChannel(ledsConfigurations[ledIndex].portn,ledsConfigurations[ledIndex].ledchannel,OUTPUT);
	}
}
void led_viOn(Led_t ledx)
{
	u8 ledIndex=0;
	for(ledIndex=0 ; ledIndex < ledsCount ; ledIndex++)
	{
		if(ledsConfigurations[ledIndex].ledn == ledx)
		{
			if(ledsConfigurations[ledIndex].ledactive == LED_ACTIVE_HIGH)
			{
				dio_vidWriteChannel(ledsConfigurations[ledIndex].portn,ledsConfigurations[ledIndex].ledchannel,STD_HIGH);
			}
			else if(ledsConfigurations[ledIndex].ledactive == LED_ACTIVE_LOW)
			{
				dio_vidWriteChannel(ledsConfigurations[ledIndex].portn,ledsConfigurations[ledIndex].ledchannel,STD_LOW);
			}
		}
		
	}
	
	
}
void led_viOff(Led_t ledx)
{
	u8 ledIndex=0;
	for(ledIndex=0 ; ledIndex < ledsCount ; ledIndex++)
	{
		if(ledsConfigurations[ledIndex].ledn == ledx)
		{
			if(ledsConfigurations[ledIndex].ledactive == LED_ACTIVE_HIGH)
			{
				dio_vidWriteChannel(ledsConfigurations[ledIndex].portn,ledsConfigurations[ledIndex].ledchannel,STD_LOW);
			}
			else if(ledsConfigurations[ledIndex].ledactive == LED_ACTIVE_LOW)
			{
				dio_vidWriteChannel(ledsConfigurations[ledIndex].portn,ledsConfigurations[ledIndex].ledchannel,STD_HIGH);
			}
		}
		
	}
	
	
}
void led_viToggle(Led_t ledx)
{
	u8 ledIndex=0;
	for(ledIndex=0 ; ledIndex < ledsCount ; ledIndex++)
	{
		if(ledsConfigurations[ledIndex].ledn == ledx)
		{
			dio_vidFlipChannel(ledsConfigurations[ledx].portn,ledsConfigurations[ledx].ledchannel);
		
		}
		
	}
		
}
