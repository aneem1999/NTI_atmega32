/***************************************************************************************
 *  @file 	:  * UnipolarStepperMotor.c
 *  @date	: 2/27/2023 9:17:06 PM
 *  @author : Ahmed Naeem
 **************************************************************************************/

/**************************************************************************************
         Includes
**************************************************************************************/
#include "../LIB/std_types.h"
#include "../MCAl/DIO/dio.h"
#include "UnipolarStepperMotor_cfg.h"
#include "UnipolarStepperMotor_interface.h"


void uStepMotor_voidInit(u8 uStpMotorId)
{
    switch (uStpMotor_Configurations[uStpMotorId].uStpMotorPort)
    {
    case DIO_PORTA:
        DDRA = uStpMotor_Configurations[uStpMotorId].mask;
        break;

    case DIO_PORTB:
        DDRB = uStpMotor_Configurations[uStpMotorId].mask;

        break;

    case DIO_PORTC:
        DDRC = uStpMotor_Configurations[uStpMotorId].mask;
        break;

    case DIO_PORTD:
        DDRD = uStpMotor_Configurations[uStpMotorId].mask;

        break;
    }
}

void uStepMotor_voidRoteCW(u8 uStpMotorId, u16 stpCounts)
{
    u8 stp = 0;
    switch (uStpMotor_Configurations[uStpMotorId].uStpMotorDrivingMode)
    {
    case uStpWave_Mode:
        while (stp != stpCounts)
        {
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x8,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x4,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x2,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x1,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
        }
        break;
    case uStpFullStep_Mode:
        while (stp != stpCounts)
        {
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x09,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x0C,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x06,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x03,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
        }
        break;
    case uStpHalfStep_Mode:
        while (stp != stpCounts)
        {
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x09,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x08,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x0C,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x04,
                                     uStpMotor_Configurations[uStpMotorId].mask);

            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x06,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x03,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x01,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
        }
        break;
    }
}
void uStepMotor_voidRoteACW(u8 uStpMotorId, u16 stpCounts)
{
    u8 stp = 0;
    switch (uStpMotor_Configurations[uStpMotorId].uStpMotorDrivingMode)
    {
    case uStpWave_Mode:
        while (stp != stpCounts)
        {
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x8,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x1,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x2,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x4,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
        }
        break;
    case uStpFullStep_Mode:
        while (stp != stpCounts)
        {
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x09,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x03,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x06,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x0C,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
        }
        break;
    case uStpHalfStep_Mode:
        while (stp != stpCounts)
        {
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x09,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x01,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x03,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x09,
                                     uStpMotor_Configurations[uStpMotorId].mask);

            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x04,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x08,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
            dio_vidWriteChannelGroup(uStpMotor_Configurations[uStpMotorId].uStpMotorPort, 0x08,
                                     uStpMotor_Configurations[uStpMotorId].mask);
            _delay_ms(5);
            stp++;
            if (stp == stpCounts)
                break;
        }
        break;

    default:
        break;
    }
}
