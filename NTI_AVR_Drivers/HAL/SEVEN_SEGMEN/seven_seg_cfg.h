/*
 * seven_seg_cfg.h
 *
 * Created: 2/18/2023 11:11:33 PM
 *  Author: ncm
 */ 


#ifndef SEVEN_SEG_CFG_H_
#define SEVEN_SEG_CFG_H_

#include "../MCAL/DIO/dio.h"

#define CA_SEG					1
#define CC_SEG					0

#define SEG_TYPE				CA_SEG
#define SEGMENT_NUM				4

#define SEG_DATA_PORT       DIO_PORTB
#define SEG_DATA0_PIN       DIO_PIN0
#define SEG_DATA1_PIN       DIO_PIN1
#define SEG_DATA2_PIN       DIO_PIN2
#define SEG_DATA3_PIN       DIO_PIN4

#define SEG_COM1_PORT		DIO_PORTA
#define SEG_COM1_PIN		DIO_PIN3

#define SEG_COM2_PORT		DIO_PORTA
#define SEG_COM2_PIN		DIO_PIN2

#define SEG_COM3_PORT		DIO_PORTB
#define SEG_COM3_PIN		DIO_PIN5

#define SEG_COM4_PORT		DIO_PORTB
#define SEG_COM4_PIN		DIO_PIN6




#endif /* SEVEN_SEG_CFG_H_ */