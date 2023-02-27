/************************************************************
 *
 * LCD_cfg.h
 *
 *  Created on: Nov 30, 2022
 *      Author: Ahmed Naeem
 *
 *      Here you configure LCD according to board specs and connectons
************************************************************/


#ifndef LCD_CFG_H
#define LCD_CFG_H


/************************************************************/
/* LCD configurations */
#define LCD_NUM_OF_ROWS 				4
#define LCD_NUM_OF_COLUMBS				20
/* LCD Control pins */
#define LCD_CNT_RS_PIN		DIO_PIN3
#define LCD_CNT_RW_PIN		9// Not used
#define LCD_CNT_E_PIN		DIO_PIN2

#define LCD_CONTROL_REG	    DIO_PORTA


/* LCD Data Pins */
#define LCD_DATA_PIN_0	    9// Not used
#define LCD_DATA_PIN_1	    9// Not used
#define LCD_DATA_PIN_2	    9// Not used
#define LCD_DATA_PIN_3	    9// Not used

#define LCD_DATA_PIN_4	    DIO_PIN0
#define LCD_DATA_PIN_5	    DIO_PIN1
#define LCD_DATA_PIN_6		DIO_PIN2
#define LCD_DATA_PIN_7		DIO_PIN4

#define LCD_DATA_REG	    DIO_PORTB

/* LCD Configuration Commands */
#define LCD_CMD_CLEAR_DISPLAY				 (0x01)
#define LCD_CMD_RETURN_HOME 				 (0x02)
#define LCD_CMD_8_BIT_MODE 				     (0x38) /*DL:8 BIT N:2 LINES L:8*5 */
#define LCD_CMD_4_BIT_MODE 					 (0x28) /*DL:4 BIT N:2 LINES L:8*5 */
#define LCD_CMD_DISPLAY_CURSOR_BLINK_ON 	 (0x0F) /*D:ON BIT C:ON BLINK: ON */
#define LCD_CMD_CURSOR_INC_NO_DISPLAY_SHIFT  (0x06) /* I/D: Cursor incrementing, SH: No display shift */
#define LCD_CMD_CURSOR_DEC_NO_DISPLAY_SHIFT  (0x04) /* I/D: Cursor decrementing, SH: No display shift */
#define LCD_CMD_SET_CGRAM 					 (0x40)
#define LCD_CMD_SET_DDRAM 					 (0x80)

/* LCD General Configuration  */
#define LCD_OP_MODE							LCD_CMD_4_BIT_MODE
#define LCD_ENTRY_MODE						LCD_CMD_CURSOR_INC_NO_DISPLAY_SHIFT
#define LCD_DISPLAY_MODE					LCD_CMD_DISPLAY_CURSOR_BLINK_ON


/************************************************************/


#endif 
