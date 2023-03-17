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
#include "../MCAL/TWI/twi_interface.h"

#include "../HAL/External_EEPROM/exEEPROM.h"

#define F_CPU 16000000U
#include "util/delay.h"

#if 0
volatile u8 d ='A'  ;

int main()
{
	u8 data='Z';
   
	TWI_Master_voidInit(40000);
	LCD_Init();
		
	
    while (1) 
    {
		exEEPROM_voidWriteByte(0x90, d);
		LCD_WriteString("I write : ",0,0);
		LCD_WriteData(d);
		
		
		exEEPROM_voidReadByte(0x90, &data);
		
		d++;
		_delay_ms(5000);
		
		
    }
}

#endif

