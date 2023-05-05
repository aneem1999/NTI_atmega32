/*
 * mainTrfLights_freertos.c
 *
 * Created: 4/30/2023 8:46:25 PM
 *  Author: ncm
 */ 


#if 0
#define F_CPU 16000000U
#include "../SERVICES/FreeRTOS/FreeRTOSConfig.h"
#include "../SERVICES/FreeRTOS/FreeRTOS.h"
#include "../SERVICES/FreeRTOS/task.h"
#include "../SERVICES/FreeRTOS/semphr.h"
#include "../SERVICES/FreeRTOS/queue.h"

#include "../HAL/LED/led.h"
#include "../HAL/SSD/seven_seg.h"
#include "../HAL/LCD/LCD.h"



enum TrafLigt_state_t
{
	Go_State,
	SteadyToStop_state,
	Stop_state,
	SteadyToGo_State
}TrafLigt_state;

u8 SSD_seconds =0 ;
u8 ftime=0;


void LED_R(void *ptr)
{
	while(1)
	{
		led_viToggle(LED_RED);
	    vTaskDelay(60000);
	}
	
}

void LED_Y(void *ptr)
{
	while(1)
	{
		if(ftime == 1)
		{
			led_viToggle(LED_YELLOW);
		}
		
		vTaskDelay(30000);
		if(ftime == 0)
		ftime = 1;
	}
}

void LED_G(void *ptr)
{
	while(1)
	{
		if (ftime == 1)
		{
		led_viToggle(LED_GREEN);
		
		}
	vTaskDelay(60000);
	
		
	}
}
void state_change(void *ptr)
{
	while(1)
	{
		
		vTaskDelay(20000);
		SSD_seconds =0 ;
		
		vTaskDelay(40000);
		SSD_seconds =0 ;
		
		
	}
}
void SSD_Display(void *ptr)
{
	while(1)
	{
		SSD_vDisplayNum(SSD_seconds);
		vTaskDelay(2);
		
		
	}
}

void SSD_update(void *ptr)
{
	while(1)
	{
		SSD_seconds++;
		vTaskDelay(1000);
		
	}
}



int tlFreemain()
{
	
	led_viInit();
	SSD_vInit();
	
	
	
	
	vTaskStartScheduler();
	
	
	
	
	
	while (1)
	{
	}
}
#endif