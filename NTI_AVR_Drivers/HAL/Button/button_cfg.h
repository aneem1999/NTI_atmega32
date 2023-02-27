/*
 * buutom_cfg.h
 *
 * Created: 2/17/2023 3:56:11 PM
 *  Author: ncm
 */ 

#ifndef BUTTON_CFG_H
#define BUTTON_CFG_H

#include "button.h"

typedef struct
{
	Button_Num_t buttonNum;
	dio_portId_t bport;
	dio_channelId_t bchannel;
	PULL_State_t pullState;
}Button_config_t;

extern Button_config_t Button_configurations[];
extern u8 Buttons_count;

#endif
