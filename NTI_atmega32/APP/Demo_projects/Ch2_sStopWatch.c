/*
 * CFile1.c
 *
 * Created: 2/22/2023 5:41:46 PM
 *  Author: ncm
 */ 

/*
 * NTI_AVR_Drivers.c
 *
 * Created: 2/17/2023 11:50:41 AM
 * Author : ncm
 */ 

#define F_CPU 16000000U
#include "../HAL/LED/led.h"
#include "../HAL/Button/button.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KEYPAD/keyPad.h"
#include "../HAL/SSD/seven_seg.h"



#include <util/delay.h>


int main3(void)
{
	
	u8   count=50 , Mod=0;
	u16 tim=0;
	SSD_vInit();
	button_viInit();
	led_viInit();
    while (1) 
    {
		if(Mod == 0)
		{
			// set mode
			led_viOff(LED_RED);
			
			SSD_vDisplayNum(tim);
			if(button_getState(Button_0) == PRESSED)
			{
				tim+=10;
				while(button_getState(Button_0) == PRESSED);
			}
			else if((button_getState(Button_1) == PRESSED)&& (tim >0))
			{
				tim-=10;
				while(button_getState(Button_1) == PRESSED);
			}
			else if((button_getState(Button_3) == PRESSED))
			{
				tim=0;
				while(button_getState(Button_3) == PRESSED);
			}
			
		}
		else if(Mod == 1)
		{
			// timing mode
			led_viOn(LED_RED);
			 
			while(count)
			{
				SSD_vDisplayNum(tim);
				count--;
			}
			count =50;
			tim--;
			if(tim ==0)
			{
				Mod=0;
			}
		}
		
		
		 if((button_getState(Button_2) == PRESSED) )
		{
			if(Mod == 0) Mod =1 ;else if(Mod==1) Mod =0;
			while(button_getState(Button_2) == PRESSED);
		}
		
		
		
	}
		
	
}




