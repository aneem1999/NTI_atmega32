/*
 * US_HC_SR04_cfg.c
 *
 * Created: 3/16/2023 11:04:02 PM
 *  Author: ncm
 */

#include "US_HC_SR04_cfg.h"
#include "../MCAL/DIO/dio.h"

US_Channel_Cfg_t US_arrChannels[] = {
    {US_CHANNEL_0, DIO_PORTC, DIO_PIN2, 0},
    {US_CHANNEL_1, DIO_PORTC, DIO_PIN3, 0}

};

u8 US_countChannels = sizeof(US_arrChannels) / sizeof(US_arrChannels[0]);