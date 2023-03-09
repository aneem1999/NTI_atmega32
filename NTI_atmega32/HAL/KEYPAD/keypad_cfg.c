
#include "std_types.h"
#include "keypad_cfg.h"
#include "DIO/dio.h"


/* Available keypads and its pins, ports and default state*/
KeypadConfg_t Keypads[] =
{
	{
		{
			{DIO_PORTC, DIO_PIN5,NO_PULL},
			{DIO_PORTC, DIO_PIN4,NO_PULL},
			{DIO_PORTC, DIO_PIN3,NO_PULL},
			{DIO_PORTC, DIO_PIN2,NO_PULL},
			
		},

		{
			{DIO_PORTD, DIO_PIN7,PULL_UP},
			{DIO_PORTD, DIO_PIN6,PULL_UP},
			{DIO_PORTD, DIO_PIN5,PULL_UP},
			{DIO_PORTD, DIO_PIN3,PULL_UP},
		},

		STD_HIGH
	}
};

 u8 KeypadChars[4][4] = {
										{'7' ,'8' ,'9' ,'A'},
										{'4', '5', '6', 'B'},
										{'1', '2', '3', 'C'},
										{'#' , '=', '0' , 'D'}
};

u8 KeypadsCount = sizeof(Keypads) / sizeof(KeypadConfg_t);
