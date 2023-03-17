/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   LCD.h
 *************************************************************/
#ifndef LCD_H
#define LCD_H
#include "../LIB/std_types.h"
#include "../LIB/std_types.h"
#include "../LIB/bit_math.h"

/*LCD APIs */
/* specify entery mode, display mode and operation mode then clear LCD*/
void LCD_Init(void);

void LCD_WriteChar(u8 ch, u8 row, u8 col);
void LCD_WriteData(u8 cmd);
 
void LCD_GoToXY(u8 row, u8 col);

void LCD_WriteString(char *str);

void LCD_ClearDisplay(void);

void LCD_CreatCustomChar(u8 *ch, u8 len, u8 index);

void LCD_WriteCustomChar(u8 index, u8 row, u8 col);
#endif
