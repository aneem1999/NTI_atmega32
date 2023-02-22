/*
 * led_cfg.h
 *
 * Created: 2/17/2023 3:25:07 PM
 *  Author: ncm
 */ 


#ifndef LED_CFG_H_
#define LED_CFG_H_
#include "led.h"

typedef struct
{
	Led_t ledn;
	dio_portId_t portn;
	dio_channelId_t ledchannel;
	LED_Active_State_t ledactive;
	
	}LED_Config_t;
	
extern LED_Config_t ledsConfigurations[];
extern u8 ledsCount;

#endif /* LED_CFG_H_ */