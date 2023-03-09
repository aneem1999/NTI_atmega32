/*
 * SPImasterReceiver.c
 *
 * Created: 3/6/2023 10:10:40 PM
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

#define F_CPU 16000000U
#include "util/delay.h"

#if 0
volatile u8 d ='A' ;

void ISRspi()
{
	d =SPDR;
}

int main(void)
{
   dio_vidConfigChannel(DIO_PORTA,DIO_PIN4,OUTPUT);
	
	SPI_voidSlaveInit();
	SPI_voidIEN(ISRspi);
	UART_Init();
	
    while (1) 
    {
		UART_TransmitBusyWait((u16)d);
		
		_delay_ms(1000);
		
		
    }
}

#endif

#if 0

 u8 d ='1' ;
void ISRs()
{
	SPDR = d;
}
int main(void)
{
	
	SPI_voidMasterInit();
	KeyPad_init();
	SPI_voidIEN(ISRs);
	
	SPI_voidTransmit(d);
			
	while (1)
	{
		
		if(GetKeyPressed(&d ,Keypad_1) == KEY_PRESSED )
		{
			
		}
			
	
		
		
		
	}
}

#endif
