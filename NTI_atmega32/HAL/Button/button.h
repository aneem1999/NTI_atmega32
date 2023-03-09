/*
 * button.h
 *
 * Created: 2/17/2023 3:58:30 PM
 *  Author: ncm
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

/****************************** includes *************************************/
#include "../MCAL/DIO/dio.h"

typedef enum
{
	Button_0,
	Button_1,
	Button_2,
	Button_3,
}Button_Num_t;

typedef enum
{
	NOT_PRESSED,
	PRESSED,
}Button_State_t;





/***************** Funtions protypes **********************/

void button_viInit(void);
Button_State_t button_getState(Button_Num_t buttonx);

#endif /* BUTTON_H_ */