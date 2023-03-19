/*
 * SPI_REG.h
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#ifndef MCAL_SPI_SPI_REG_H_
#define MCAL_SPI_SPI_REG_H_

#include "std_types.h"
#include "../LIB/register.h"



/*------SPCR------*/
#define SPR0	 	0
#define SPR1 	 	1
#define CPHA 	 	2
#define CPOL     	3
#define MSTR     	4
#define DORD 		5
#define SPE 		6
#define SPIE 		7

/*------SPSR------*/
#define SPI2X	 	0
#define WCOL 		6
#define SPIF 		7

/*------SPDR------*/
#define BIT0	 	0
#define BIT1 	 	1
#define BIT2 	 	2
#define BIT3     	3
#define BIT4     	4
#define BIT5 		5
#define BIT6 		6
#define BIT7 		7

/*-----PORTB------*/
#define SS 		3
#define MOSI 	5
#define MISO 	6
#define SCK 	7


#endif /* MCAL_SPI_SPI_REG_H_ */
