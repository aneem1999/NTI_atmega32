/***************************************************************************************
 *  @file 	:  * UnipolarStepperMotor_cfg.h
 *  @date	: 2/27/2023 9:17:06 PM
 *  @author : Ahmed Naeem
 **************************************************************************************/

#ifndef UNIPOLARSTEPPERMOTOR_CFG_H_
#define UNIPOLARSTEPPERMOTOR_CFG_H_

typedef enum
{
	uStpWave_Mode,
	uStpFullStep_Mode,
	uStpHalfStep_Mode

} uStpMotor_DrivingMode_t;

typedef struct
{
	uStpMotor_DrivingMode_t uStpMotorDrivingMode;
	dio_portId_t uStpMotorPort;
	u8 mask;

} uStpMotor_Config_t;

extern uStpMotor_Config_t uStpMotor_Configurations[];
extern u8 uStpMotor_ConfigCounts;

#endif /* UNIPOLARSTEPPERMOTOR_CFG_H_ */