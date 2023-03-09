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
#include "./MCAL/TWI/twi_interface.h"

#define F_CPU 16000000U
#include "util/delay.h"

#if 1
volatile u8 d =0x20 ;

void ISRspi()
{
	d =SPDR;
}

int main()
{
   
	TWI_SetBitRate(100000);
		
	
    while (1) 
    {
		TWI_Start();
		TWI_SlaveSelect(0x0f , WRITE_OP);
		TWI_SendByte(d);
		TWI_Stop();
		
		d++;
		
		_delay_ms(1000);
		
		
    }
}

#endif

#if 0

int ISRs()
{
	SPDR = d;
}
int main(void)
{
	
			
	while (1)
	{
		
		
	}
}

#endif
