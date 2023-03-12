/*
 * TWI_tx.c
 *
 * Created: 3/11/2023 9:23:32 AM
 *  Author: ncm
 */ 


/*
 * NTI_atmega32.c
 *
 * Created: 3/3/2023 10:08:32 AM
 * Author : ncm
 */ 

#include "../MCAL/USART/uart_interface.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LED/led.h"
#include "../MCAL/SPI/spi_interface.h"
#include "../MCAL/DIO/dio.h"
#include "../HAL/KEYPAD//keyPad.h"
//#include "./MCAL/TWI/twi_interface.h"

#define F_CPU 16000000U
#include "util/delay.h"

#if 0
volatile u8 d ='A' ;

void ISRspi()
{
	d =SPDR;
}

int main()
{
   
	TWI_Master_voidInit(100000);
	led_viInit();
		
	
    while (1) 
    {
		if(TWI_Master_enuStartCond() ==EVENT_OK_STATE)
		{
			if(TWI_Master_enuSelectSlave(10,WRITE_OP) == SLA_W_SENT_WITH_ACK_STATE)
			{
				if (TWI_Master_enuSendByte(d)== DATA_SENT_WITH_ACK_STATE)
				{
					TWI_Master_voidStopCond();
				
				}
			}
			
		}
		
		d++;
		
		_delay_ms(1000);
		
		
    }
}

#endif

