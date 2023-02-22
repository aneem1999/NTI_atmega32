#include "button_cfg.h"

 Button_config_t Button_configurations[] = {	    {Button_0, DIO_PORTD , DIO_PIN3 , PULL_UP},
													{Button_1, DIO_PORTD , DIO_PIN5 , PULL_UP},
													{Button_2, DIO_PORTD , DIO_PIN6 , PULL_UP},
													{Button_3, DIO_PORTD , DIO_PIN7 , PULL_UP},
												};
 u8 Buttons_count = sizeof(Button_configurations)/sizeof(Button_config_t);