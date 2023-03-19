/*
 * SPI.c
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */
#include "SPI.h"

void SPI_Init()
{
	switch (SPI_DOUBLE_SPEED_MODE)
	{
	case DOUBLE_SPEED_MODE_DIS:
		CLEAR_BIT(SPSR, SPI2X);
		break;
	case DOUBLE_SPEED_MODE_EN:
		SET_BIT(SPSR, SPI2X);
		break;
	}
	switch (DATA_ORDER)
	{
	case MSB:
		CLEAR_BIT(SPCR, DORD);
		break;
	case LSB:
		SET_BIT(SPCR, DORD);
		break;
	}
	switch (CLK_POLARITY)
	{
	case RISING_LEADING:
		CLEAR_BIT(SPCR, CPOL);
		break;
	case FALLING_LEADING:
		SET_BIT(SPCR, CPOL);
		break;
	}
	switch (CLK_PHASE)
	{
	case SAMPLE_LEADING:
		CLEAR_BIT(SPCR, CPHA);
		break;
	case SETUP_LEADING:
		SET_BIT(SPCR, CPHA);
		break;
	}
	switch (SPI_INT_ENABLE)
	{
	case SPI_INT_DIS:
		CLEAR_BIT(SPCR, SPIE);
		break;
	case SPI_INT_EN:
		SET_BIT(SPCR, SPIE);
		break;
	}
	switch (SPI_ENABLE)
	{
	case SPI_DIS:
		CLEAR_BIT(SPCR, SPE);
		break;
	case SPI_EN:
		SET_BIT(SPCR, SPE);
		break;
	}
	switch (IS_MSTR)
	{
	case SLAVE:
		CLEAR_BIT(DDRB, MOSI);
		CLEAR_BIT(DDRB, SCK);
		CLEAR_BIT(DDRB, SS);
		SET_BIT(DDRB, MISO);
		CLEAR_BIT(SPCR, MSTR);
		break;
	case MASTER:
		SET_BIT(DDRB, MOSI);
		SET_BIT(DDRB, SCK);
		SET_BIT(DDRB, SS);
		CLEAR_BIT(DDRB, MISO);
		SET_BIT(PORTB, SS);
		SET_BIT(SPCR, MSTR);
		break;
	}
	SET_BIT(SPCR, SPR0);
	CLEAR_BIT(SPCR, SPR1);
}
u8 SPI_DATA_RW(u8 Copy_u8data)
{
	SPDR = Copy_u8data;
	while (!CHECK_BIT(SPSR, SPIF))
		;
	return SPDR;
}
