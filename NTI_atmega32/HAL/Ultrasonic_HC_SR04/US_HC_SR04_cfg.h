/*
 * US_HC_SR04_cfg.h
 *
 * Created: 3/16/2023 11:01:11 AM
 *  Author: ncm
 */

#ifndef US_HC_SR04_CFG_H_
#define US_HC_SR04_CFG_H_
#include "../MCAL/DIO/dio.h"

typedef enum
{
    US_CHANNEL_0,
    US_CHANNEL_1,
    US_CHANNEL_2,
    US_CHANNEL_3

} US_Channel_Num_t;

typedef struct
{
    US_Channel_Num_t Channel_Num;
    dio_portId_t TRIG_PORT_Num;
    dio_channelId_t TRIG_PIN_Num;
    f32 readingDistance;

} US_Channel_Cfg_t;

extern US_Channel_Cfg_t US_arrChannels[];

extern u8 US_countChannels;

#endif /* US_HC_SR04_CFG_H_ */