/************************************************************/
/* 	Author 	 	 : Ahmed Atia Atia                          */
/* 	Date   		 : 20 April 2019                            */
/* 	Version 	 : 1V 									    */
/* 	Description	 : Config.c for DC Motor                    */
/************************************************************/

#include "Std_types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "LCD_int.h"
#include "LCD_priv.h"
#include "LCD_config.h"

#include <util/delay.h>


void LCD_vidInit( void )
{
	/* wait 35 */
	_delay_ms(35);

	/*  function set */

	LCD_vidSendCmd(0b00111000);
	/* wait 1 */
	_delay_ms(1);

	/*  function set (on/off) */
	LCD_vidSendCmd(0b00001100);
	/* wait 1 */
	_delay_ms(1);

	/*  function set (Clear  Display) */


	/*****************************/
	/*LCD_vidSendCmd(0b00000001);*/
	/*	 wait 2                  */
	/*_delay_ms(2);	             */
	/*****************************/

	LCD_vidClear();

	/*  function set (Entry mode set - cursor increase or decrease ) */
	LCD_vidSendCmd(0b00000110);
	/* wait 2 */
	_delay_ms(2);

	/* latch = 0 */
	DIO_voidSetPinValue( LCD_u8EN , DIO_u8_LOW );

}

void LCD_vidSendCmd( u8 u8CmdCpy )
{
	/** to send command  ( RS = 0 and R/W = 0 ) =====> (write instruction) */

	/* RS  0 CMD */  
	DIO_voidSetPinValue( LCD_u8RS , DIO_u8_LOW );
	/* write 0 CMD*/
	DIO_voidSetPinValue( LCD_u8RW , DIO_u8_LOW );

	/* take data pass data bu */
	vidPutOnBus(u8CmdCpy);

}

void LCD_vidWriteChar( u8 u8CharCpy )
{
	/** to write command   ( RS = 1 and R/W = 0 ) =====> (write to DR Reg) */

	/* RS  1 CMD */
	DIO_voidSetPinValue( LCD_u8RS , DIO_u8_HIGH );
	/* write 0 CMD*/
	DIO_voidSetPinValue( LCD_u8RW , DIO_u8_LOW );

	/* take data pass data bu */
	vidPutOnBus(u8CharCpy);
}

static void vidPutOnBus( u8 u8CmdDataCpy )
{
	u8 LOC_u8Loop = LCD_DATA_D0_START ;

	DIO_voidSetPinValue( LCD_u8DATA_0 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_1 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_2 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_3 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_4 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_5 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_6 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));
	DIO_voidSetPinValue( LCD_u8DATA_7 , GET_BIT(u8CmdDataCpy , LOC_u8Loop++ ));

	/* lach  */
	DIO_voidSetPinValue( LCD_u8EN , DIO_u8_HIGH );
	_delay_ms(2);
	DIO_voidSetPinValue( LCD_u8EN , DIO_u8_LOW );
	_delay_ms(2);

}

void LCD_vidClear( void )
{
	/*  function set (Clear  Display) */
	LCD_vidSendCmd(0b00000001);
	/* wait 2 */
	_delay_ms(2);
}


void LCD_vidGotoXY( u8 u8LineNbCpy , u8 u8CharNbCpy )
{
 /* switchcase over line */
	if(  u8LineNbCpy == 1 )
	{
		/*  function set (Line1 position " x ") */
		LCD_vidSendCmd( (LCD_BEGINNING_FIRST_LINE + u8CharNbCpy) );
			
	}
	
	else if( u8LineNbCpy == 2 )
	{
		/*  function set (Line1 position " x ") */
		LCD_vidSendCmd( (LCD_BEGINNING_SECOND_LINE + u8CharNbCpy) );
		
	}
	
	
}


/* warnning avoid (u8*)"ahmed" */
void LCD_vidWriteString( u8 * pu8StringCpy )
{
	u8 Loc_u8Counter = 0 ;
	
	while(pu8StringCpy[Loc_u8Counter] !='\0')
	{
		LCD_vidWriteChar(pu8StringCpy[Loc_u8Counter]);
		Loc_u8Counter++;		
	}
	

}



/*
Description: Write any number starting from 0 to 65535 on the LCD
Inputs:  Copy_u16NB: a U16 variable to hold the required number
Outputs: Error state -> 0 No Error
					 -> 1 Error
 */

u8 LCD_u8WriteINT(u16 Copy_u16NB)
{
	u8 Local_u8Error=0;

	if(Copy_u16NB==0)
	{
		LCD_vidWriteChar(48);
	}
	else
	{
		u8 Local_u8Digits=0,Local_u8Counter;
		u16 Local_u16CopyOfNB=Copy_u16NB;

		/*		Get the number of digits of the Number*/
		while(Local_u16CopyOfNB !=0)
		{
			Local_u8Digits++; //Increment no of digits by one

			Local_u16CopyOfNB/=10; //get rid of the most right digit
		}

		Local_u16CopyOfNB=Copy_u16NB;

		/*		Loop on the number and print every single digit alone each iteration*/
		for(Local_u8Counter=0;Local_u8Counter<Local_u8Digits;Local_u8Counter++)
		{
			/*Get the most left digit*/
			Local_u16CopyOfNB/=Private_u16Power(10,Local_u8Digits-Local_u8Counter-1);

			/*Print the most left digit*/
			LCD_vidWriteChar(48+Local_u16CopyOfNB);

			/*Load the original number*/
			Local_u16CopyOfNB=Copy_u16NB;

			/*Get rid of the left most digit*/
			Local_u16CopyOfNB%=Private_u16Power(10,Local_u8Digits-Local_u8Counter-1);
		}
	}
	return Local_u8Error;
}

u16 Private_u16Power(u8 Copy_u8Op1, u8 Copy_u8Op2)
{
	u8 Local_u8Counter;
	u16 Local_u16Result=1;
	for(Local_u8Counter=0;Local_u8Counter<Copy_u8Op2;Local_u8Counter++)
	{
		Local_u16Result*=Copy_u8Op1;
	}
	return Local_u16Result;
}
