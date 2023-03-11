/*
 * main.c
 *
 *  Created on: Oct 3, 2019
 *      Author: Boon
 */

#define F_CPU 8000000UL

#include "Std_types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "LCD_int.h"

#include "GIE_int.h"

#include "Timer0_int.h"
#include "Timer0_priv.h"
#include <util/delay.h>

#define ICR1 *((volatile u16 *)0x46)

void __vector_6(void) __attribute__((signal, used)); // for ICU interrupt

volatile u16 counter = 0;

volatile u16 u16temp1;
volatile u16 u16temp2;
volatile u16 u16temp3;

volatile u8 u8flag = 0;

int main()
{
	f32 f32TimerClock = /*0.000001*/ (8 / (f32)8000000); /*Tick Time*/
	u16 u16Duty_cycle;
	u16 u16Period;
	u16 u16Onperiod;
	u16 u16Freq = 0;

	DIO_voidInitialization();

	LCD_vidInit();

	TIMER0_void_Init();
	TIMER0_void_SetCompareVal(127); /*	Duty 50% .. Freq = fcpu/(pre * counts)= (8000000 /8*256) */
	// F = 3906.25 HZ
	/// init TIMER1
	/*Normal Mode .. Pre = 1024 .. enable ICU .. Rissing Edge	*/
	TCCR1A = 0x00;
	TCCR1B = 0b01000010;

	TCNT1H = 0;
	TCNT1L = 0;

	GIE_voidEnable();

	SET_BIT(TIMSK, 5); // enable ICU INT
	//// end init

	while (u8flag != 3)
		;
	// LCD_go_to_xy(2,0);
	// lcd_write_char('a');

	u16Period = u16temp3 - u16temp1;

	u16Onperiod = u16temp2 - u16temp1;

	u16Duty_cycle = ((u16Onperiod * 100) / u16Period);

	u16Freq = (1 / (u16Period * f32TimerClock));
	// lcd_write_char('a');
	/**************************************************/
	// lcd_write_string("Duty Cycle =");
	// LCD_go_to_xy(1,11);
	/********************************************/

	LCD_vidWriteString((u8 *)"Duty Cycle =");
	LCD_vidGotoXY(1, 11);
	LCD_u8WriteINT(u16Duty_cycle);
	/**************************************************/
	// LCD_WriteNumber(u16Duty_cycle);
	// lcd_write_string("%");
	/***************************************/

	LCD_vidWriteChar('%');
	LCD_vidGotoXY(2, 0);

	/**************************************************/
	// LCD_go_to_xy(2,0);
	// lcd_write_string("Period =");
	// LCD_WriteNumber(u16Period);
	/**************************************************/
	// LCD_vidWriteString("Period =");
	// LCD_u8WriteINT(u16Period);
	/*****************************************************/
	LCD_vidWriteString("Freq = ");
	LCD_u8WriteINT(u16Freq);

	while (1)
	{
	}

	return 0;
}

void __vector_6(void)
{

	if (u8flag == 0)
	{
		u16temp1 = ICR1L | (ICR1H << 8);
		CLEAR_BIT(TCCR1B, 6);
	}
	else if (u8flag == 1)
	{

		u16temp2 = ICR1L | (ICR1H << 8);
		SET_BIT(TCCR1B, 6);
	}
	else if (u8flag == 2)
	{
		u16temp3 = ICR1L | (ICR1H << 8);
	}

	u8flag++;
}
