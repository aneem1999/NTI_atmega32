/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   stm32f103x6.h
 *************************************************************/

/*************************************************************
 *  Includes
 */

#include "../LIB/std_types.h"
#include "DIO/dio.h"
#include "keypad.h"
#include "keypad_cfg.h"



/*************************************************************
 *   @param [in]- Nothing
 *   @brief  initialization for number of 4x4 Keypads init rows as output and write
 *   		default state to it according to connection
 *   		and init columns as input
 *   @retval none
 */
void KeyPad_init()
{
	u8 index_1 = 0,index_2 = 0;


	for (index_1 = 0; index_1 < KeypadsCount; index_1++)
	{
		for (index_2 = 0; index_2 < 4; index_2++)
		{
			/* Init rows and columns*/
			dio_vidConfigChannel(Keypads[index_1].rows[index_2].bport ,
			Keypads[index_1].rows[index_2].bchannel,OUTPUT);
			dio_vidConfigChannel(Keypads[index_1].cols[index_2].bport ,
			Keypads[index_1].cols[index_2].bport,INPUT);

			/* Write default state to rows pins according to HW connections */
			dio_vidWriteChannel(Keypads[index_1].rows[index_2].bport ,
			Keypads[index_1].rows[index_2].bchannel,Keypads[index_1].defState);
		}
	}
}


/*************************************************************
 *   @param [in] - keypad index according to HW connection
 *   @param [out]- char of key which is pressed
 *   @brief  Get Key pressed or not and key row and column
 *   @retval key pressing status
 */
KeyStatus_t GetKeyPressed(u8 * ch, Keypad_t Keypad_index)
{
	KeyStatus_t pressstatus = KEY_NOT_PRESSED;
	u8 rowindex = 0, colindex = 0, breakFlag = 0;
	dio_level_t drive_state = STD_LOW;


	/*Check drive state by inverting default state*/
	if (STD_LOW == Keypads[Keypad_index].defState)
	{
		drive_state = STD_HIGH;
	}
	else if (STD_HIGH == Keypads[Keypad_index].defState)
	{
		drive_state = STD_LOW;
	}

	/*monitor rows by drive state and check column status */
	for (rowindex = 0; rowindex < 4; rowindex++)
	{
		/*monitor rows by drive state*/
		dio_vidWriteChannel(Keypads[Keypad_index].rows[rowindex].bport,
		Keypads[Keypad_index].rows[rowindex].bchannel,drive_state);
		

		/*check column status */
		for (colindex = 0; colindex < 4; colindex++)
		{
			if (drive_state == dio_dioLevelReadChannel(Keypads[Keypad_index].cols[colindex].bport,
			Keypads[Keypad_index].cols[colindex].bchannel ))
			{
				pressstatus = KEY_PRESSED;
				*ch = KeypadChars[rowindex][colindex];
				breakFlag = 1;
				/*Busy Wait Until Key is OFF */
				while(drive_state ==  dio_dioLevelReadChannel(Keypads[Keypad_index].cols[colindex].bport,
				Keypads[Keypad_index].cols[colindex].bchannel ));
			}
		}
		/* return row state again to default state */
		dio_vidWriteChannel(Keypads[Keypad_index].rows[rowindex].bport,
		Keypads[Keypad_index].rows[rowindex].bchannel,Keypads[Keypad_index].defState );
		
		if(breakFlag == 1)
			break;
	}


	return pressstatus ;

}


