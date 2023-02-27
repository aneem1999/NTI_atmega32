/*
 * button.c
 *
 * Created: 2/17/2023 3:54:38 PM
 *  Author: Ahmed Naeem
 */ 

#include "button.h"
#include "button_cfg.h"


/***************** Funtions protypes **********************/

void button_viInit(void)
{
	u8 buttonIndex =0;
	for(buttonIndex=0; buttonIndex < Buttons_count ; buttonIndex++)
	{
		dio_vidConfigChannel(Button_configurations[buttonIndex].bport,Button_configurations[buttonIndex].bchannel,INPUT);
	}
}
Button_State_t button_getState(Button_Num_t buttonx)
{
	u8 buttonIndex =0;
	dio_level_t buttonChannelStatus = STD_LOW ;
	Button_State_t buttonState = NOT_PRESSED;
	for(buttonIndex=0; buttonIndex < Buttons_count ; buttonIndex++)
	{
		if(buttonx == Button_configurations[buttonIndex].buttonNum)
		{
			buttonChannelStatus=dio_dioLevelReadChannel(Button_configurations[buttonIndex].bport,Button_configurations[buttonIndex].bchannel);
			break;
		}
	}
	
	if((((buttonChannelStatus == STD_HIGH) && (Button_configurations[buttonIndex].pullState == PULL_DOWN)) )||((buttonChannelStatus == STD_LOW) && (Button_configurations[buttonIndex].pullState == PULL_UP)))
	{
		buttonState = PRESSED;
	}
	if((((buttonChannelStatus == STD_HIGH) && (Button_configurations[buttonIndex].pullState == PULL_UP)) ||((buttonChannelStatus == STD_LOW) && (Button_configurations[buttonIndex].pullState == PULL_DOWN))))
	{
		buttonState = NOT_PRESSED;
	}
	
	return buttonState;
	
}
