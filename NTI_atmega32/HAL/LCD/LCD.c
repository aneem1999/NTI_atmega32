/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   LCD.h
 *************************************************************/

/************************************************************/
/*includes*/
#include "LCD.h"
#include "LCD_cfg.h"
#include "../MCAl/DIO/dio.h"

#define F_CPU 16000000UL
#include <util/delay.h>



/* Helper function to send command to LCD */

static void LCD_lcd_kick()
{
	dio_vidWriteChannel(LCD_CONTROL_REG,LCD_CNT_E_PIN, STD_HIGH);
	_delay_ms(1);
	dio_vidWriteChannel(LCD_CONTROL_REG,LCD_CNT_E_PIN, STD_LOW);
	_delay_ms(1);
	
}
static void LCD_SendCommand(u8 cmd)
{
	/* R/S --> LOW  command register */
	dio_vidWriteChannel(LCD_CONTROL_REG,LCD_CNT_RS_PIN, STD_LOW);
	/* R/W --> LOW  Write */
	dio_vidWriteChannel(LCD_CONTROL_REG,LCD_CNT_RW_PIN, STD_LOW);
	
	
	/* 4 bit Mode*/
#if (LCD_OP_MODE == LCD_CMD_4_BIT_MODE)
	/*  Send 4 Higher bits */
	//dio_vidWriteChannelGroup(LCD_DATA_REG, (cmd& 0xf0)>>4 , 0xf0);
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_4, CHECK_BIT(cmd,4));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_5, CHECK_BIT(cmd,5));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_6, CHECK_BIT(cmd,6));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_7, CHECK_BIT(cmd,7));
	
	LCD_lcd_kick();
	
	/* Then Send 4 Lower bits */
	//dio_vidWriteChannelGroup(LCD_DATA_REG, (cmd& 0x0f) , 0x0f);
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_4, CHECK_BIT(cmd,0));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_5, CHECK_BIT(cmd,1));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_6, CHECK_BIT(cmd,2));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_7, CHECK_BIT(cmd,3));
	
	LCD_lcd_kick();

	/* 8 bit Mode*/
#elif (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

	/* Write data pins */	
	//LCD_DATA_REG =cmd;
	dio_vidWriteChannelGroup(LCD_DATA_REG, cmd , 0xff);
	
	LCD_lcd_kick();

#endif

}

/* Helper function to send Data to LCD */
 void LCD_WriteData(u8 cmd)
{
	/* R/S --> High  Data register */
	//SET_BIT(LCD_CONTROL_REG,LCD_CNT_RS_PIN);
	dio_vidWriteChannel(LCD_CONTROL_REG,LCD_CNT_RS_PIN, STD_HIGH);
	/* R/W --> LOW  Write */
	//CLEAR_BIT(LCD_CONTROL_REG,LCD_CNT_RW_PIN);
	dio_vidWriteChannel(LCD_CONTROL_REG,LCD_CNT_RW_PIN, STD_LOW);
	
	/* 4 bit Mode*/
#if (LCD_OP_MODE == LCD_CMD_4_BIT_MODE)

	/* Frist Send 4 higher bits */
	//dio_vidWriteChannelGroup(LCD_DATA_REG , ((cmd& 0xf0)>>4) , 0xf0);
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_4, CHECK_BIT(cmd,4));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_5, CHECK_BIT(cmd,5));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_6, CHECK_BIT(cmd,6));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_7, CHECK_BIT(cmd,7));
	
	LCD_lcd_kick();

	/* Then Send 4 Lower bits */
	//dio_vidWriteChannelGroup(LCD_DATA_REG , (cmd &0x0f) , 0xf0);
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_4, CHECK_BIT(cmd,0));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_5, CHECK_BIT(cmd,1));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_6, CHECK_BIT(cmd,2));
	dio_vidWriteChannel(LCD_DATA_REG,LCD_DATA_PIN_7, CHECK_BIT(cmd,3));
	
	LCD_lcd_kick();
	
	/* 8 bit Mode*/
#elif (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

	/* Write data pins */
	//LCD_DATA_REG = cmd;
	dio_vidWriteChannelGroup(LCD_DATA_REG , cmd , 0xff);
	LCD_lcd_kick();

#endif
}


void LCD_WriteChar(u8 ch, u8 row, u8 col)
{
	LCD_GoToXY(row,col);
	LCD_WriteData(ch);
	
}

void LCD_Init(void)
{
	/* init Pins as output */
	dio_vidConfigChannel(LCD_CONTROL_REG, LCD_CNT_RS_PIN, OUTPUT);
	dio_vidConfigChannel(LCD_CONTROL_REG, LCD_CNT_E_PIN, OUTPUT);
	dio_vidConfigChannel(LCD_CONTROL_REG, LCD_CNT_RW_PIN, OUTPUT);
	
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_4, OUTPUT);
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_5, OUTPUT);
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_6, OUTPUT);
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_7, OUTPUT);
	
	/* 8 bit Mode*/
	#if (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)
    dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_0, OUTPUT);
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_1, OUTPUT);
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_2, OUTPUT);
	dio_vidConfigChannel(LCD_DATA_REG, LCD_DATA_PIN_3, OUTPUT);
	#endif

	

	/* Send Operation mode*/
	/* Clear the LCD and return home */
	LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
	LCD_SendCommand(0x02);
	LCD_SendCommand(LCD_OP_MODE);
	/* Send entery mode*/
	LCD_SendCommand(LCD_ENTRY_MODE);
	/* Send display mode command*/
	LCD_SendCommand(LCD_DISPLAY_MODE);
	
	
	}

/* Clear the LCD and return home */
void LCD_ClearDisplay(void)
{
	LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(10);
	LCD_SendCommand(LCD_CMD_RETURN_HOME);
	_delay_ms(10);

}

void LCD_GoToXY(u8 row, u8 col)
{
	 if (row ==0)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM +col );
	}
	else if (row==1)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x40 +col );
	}
	else if(row == 2)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x14 +col );
	}
	else if(row == 3)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x54 +col );
	}
		

}


void LCD_WriteString(char *str)
{

	for (u8 index = 0; str[index] ; index++)
	{
		LCD_WriteData(str[index]);
		
	}
}

void LCD_CreatCustomChar(u8 *ch, u8 len, u8 index)
{
	u8 pos = 0;
	for (pos = 0; pos < len; pos++)
	{
		LCD_SendCommand(LCD_CMD_SET_CGRAM + (8 * index) + pos);
		LCD_WriteData(ch[pos]);
	}
}

void LCD_WriteCustomChar(u8 index, u8 row, u8 col)
{
	if (row == 0)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + col);
	}
	else if (row == 1)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x40 + col);
	}

	LCD_WriteData(index);
}


