/**************************************************************************************
 *  @file 	: UnipolarStepperMotor_cfg.c
 *  @date	: 2/27/2023 9:17:06 PM
 *  @author : Ahmed Naeem
 **************************************************************************************/

/**************************************************************************************
		 Includes
**************************************************************************************/
#include "../MCAl/DIO/dio.h"
#include "UnipolarStepperMotor_cfg.h"

/**************************************************************************************
uStpMotor_DrivingMode_t

		uStpWave_Mode  		====> Wave Mode
		uStpFullStep_Mode,	====> Full step Mode
		uStpHalfStep_Mode	====> Half step Mode



	uStpMotor_Config_t;
		uStpMotor_DrivingMode_t uStpMotorDrivingMode;
		dio_portId_t uStpMotorPort;
		u8 mask


***************************************************************************************/

uStpMotor_Config_t uStpMotor_Configurations[] =
	{
		{uStpWave_Mode, DIO_PORTA, 0x0f}

};

u8 uStpMotor_ConfigCounts = sizeof(uStpMotor_Configurations) / sizeof(uStpMotor_Config_t);
