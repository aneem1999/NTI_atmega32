/*
 * uart_cfg.h
 *
 * Created: 3/3/2023 2:05:18 PM
 *  Author: ncm
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

#include "../LIB/std_types.h"

/*---------------  Configurations types ------------------*/
/* @ref UART_MODE_DEFINE */
typedef enum
{
	UART_MODE_RX,
	UART_MODE_TX,
	UART_MODE_TX_RX

} UART_MODE_t;

/* UART_PARITY_DEFINE */
typedef enum
{
	UART_PARTY_DISABLE,
	UART_PARTY_EVEN,
	UART_PARTY_ODD
} UART_PARITY_t;

/************************************************************
 -------------- UART Configuration   -----------------
 ***********************************************************/

/* internal clock Fosc */
#define CPU_CLK 16000000UL

typedef struct
{
	UART_MODE_t Mode;	  /* mode TX or RX @ref UART_MODE_DEFINE */
	u8 DataLength;		  /* Data length 5 -- > 9 */
	UART_PARITY_t Parity; /*even or odd or disabled  @ref UART_PARITY_DEFINE*/
	u8 Stopbts;			  /* 1 or 2 stop bits */
	u32 BR;				  /* Baud rate */
} UART_Config_t;

extern UART_Config_t UART_Configuration;

#endif /* UART_CFG_H_ */