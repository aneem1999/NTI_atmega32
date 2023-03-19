/*
 * uart_cf.c
 *
 * Created: 3/3/2023 2:05:38 PM
 *  Author: ncm
 */

#include "uart_cfg.h"

/********************************************************

	 @ref UART_MODE_DEFINE
		typedef enum
		{
			UART_MODE_RX,
			UART_MODE_TX,
			UART_MODE_TX_RX

		}UART_MODE_t;

		u8 DataLength;           Data length 5 -- > 9


		 UART_PARITY_DEFINE
		typedef enum
		{
			UART_PARTY_DISABLE,
			UART_PARTY_EVEN,
			UART_PARTY_ODD
		}UART_PARITY_t;

		u8 Stopbts;             1 or 2 stop bits

	  u32 BR;                   Baud rate



********************************************************/

UART_Config_t UART_Configuration = {
	.Mode = UART_MODE_TX_RX,
	.DataLength = 8,
	.Parity = UART_PARTY_DISABLE,
	.Stopbts = 1,
	.BR = 9600};
