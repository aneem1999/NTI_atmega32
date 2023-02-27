/***************************************************************************************
 *  @file 	:  * UnipolarStepperMotor_interface.h
 *  @date	: 2/27/2023 9:17:06 PM
 *  @author : Ahmed Naeem
 **************************************************************************************/

#ifndef UNIPOLARSTEPPERMOTOR_INTERFACE_H_
#define UNIPOLARSTEPPERMOTOR_INTERFACE_H_

/**************************************************************************************
 *         APIs
 **************************************************************************************/

void uStepMotor_voidInit(u8 uStpMotorId);

void uStepMotor_voidRoteCW(u8 uStpMotorId, u16 stpCounts);

void uStepMotor_voidRoteACW(u8 uStpMotorId, u16 stpCounts);

#endif /* UNIPOLARSTEPPERMOTOR_INTERFACE_H_ */