/************************************************************/
/* 	Author 	 	 : Ahmed Atia Atia                          */
/* 	Date   		 : 20 April 2019                            */
/* 	Version 	 : 1V 									    */
/* 	Description	 : Config.c for DC Motor                    */
/************************************************************/

#ifndef _LCD_INT_H
#define _LCD_INT_H




void LCD_vidInit( void ); 

void LCD_vidSendCmd( u8 u8CmdCpy );

void LCD_vidWriteChar( u8 u8CharCpy );

void LCD_vidClear( void );

void LCD_vidGotoXY( u8 u8LineNbCpy , u8 u8CharNbCpy );

void LCD_vidWriteString( u8 * pu8StringCpy );

u8 LCD_u8WriteINT(u16 Copy_u16NB);

u16 Private_u16Power(u8 Copy_u8Op1, u8 Copy_u8Op2);


#endif 
