#ifndef KEYPAD_CFG_H
#define KEYPAD_CFG_H

#include "../LIB/std_types.h"
#include "keyPad.h"
#include "DIO/dio.h"

typedef struct
{
	dio_portId_t bport;
	dio_channelId_t bchannel;
	PULL_State_t pullState;
}Button_config_t;

typedef struct
{
	Button_config_t rows[4]; 	 	/*Rows are outputs*/
	Button_config_t cols[4]; 		/*columns are inputs*/
	dio_level_t defState;			    /*default state*/
}KeypadConfg_t;


extern KeypadConfg_t Keypads[];
extern u8 KeypadsCount;

extern u8 KeypadChars[4][4];

#endif
