/*
 * US_HC_SR04.h
 *
 * Created: 3/16/2023 10:51:05 AM
 *  Author: ncm
 */

#ifndef US_HC_SR04_H_
#define US_HC_SR04_H_

#include "../LIB/std_types.h"
#include "US_HC_SR04_cfg.h"

void US_voidInit();
f32 US_u8dRead_Distance_cm(US_Channel_Num_t US_channel);

#endif /* US_HC_SR04_H_ */