/*
 * RFID.h
 *
 * Created: 3/17/2023 8:46:39 PM
 *  Author: katbo
 */

#ifndef RFID_H_
#define RFID_H_

#include "../LIB/std_types.h"
#include "../MCAL/DIO/dio.h"
#include "../MCAL/SPI2/SPI.h"

void mcrf522_write_reg(u8 reg, u8 value);

u8 mcrf522_read_reg(u8 reg);

void mcrf522_clear_bit_mask(u8 reg, u8 mask);

void mcrf522_set_bit_mask(u8 reg, u8 mask);

void mcrf522_reset();

void mcrf522_antenna_on(void);

void mcrf522_init(void);

u8 Communicate(u8 command, u8 *sendData, u8 sendLen, u8 *backData, u8 *backLen);

u8 DetectCard();

u8 getFirmwareVersion();

u8 GetCardId(u8 *uid);

#endif /* RFID_H_ */