/*
 * uart_interface.h
 *
 * Created: 3/3/2023 2:04:49 PM
 *  Author: ncm
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*************************************************************
 *    Includes
 *************************************************************/
#include "../LIB/register.h"
#include "../LIB/std_types.h"
#include "../LIB/bit_math.h"

typedef enum
{
	UART_CONFIG_ERROR,
	UART_CONFIG_OK,

	UART_RECIEVE_ERROR,
	UART_TRANSMIT_ERROR,
	UART_RECIEVE_OK,
	UART_TRANSMIT_OK,

} UART_ERROR_t;

/*Baud Rate Calculation */
#define UBRR_VAL(_BAUD) (u8)(((u64)CPU_CLK / (u32)(16 * _BAUD)) - 1)

/*************** UART Default stop condition ******************/
#define Default_STOP '\r'

/*************************************************************
 *   ------------------- UART APIs -------------------
 *************************************************************/

/*************************************************************
 *   @param [in]- UART Configuration instant @ref UART_Config_t @file UART_cfg.h
 *   @brief  initialization of UART Frame , Baud rate and Mode
 *   @retval none
 */
UART_ERROR_t UART_Init();

/*************************************************************
 *   @param  [in]- UART Configuration instant @ref UART_Config_t @file UART_cfg.h
 *   @param  [in]- data in rang of 5 to 9 bits
 *   @brief  send single piece of data char 5 to 8 bits or 9 bits
 *   @retval none
 */
UART_ERROR_t UART_TransmitBusyWait(u8 data);

/*************************************************************
 *   @param  [in]- UART Configuration instant @ref UART_Config_t @file UART_cfg.h
 *   @brief  receive single piece of data char 5 to 8 bits or 9 bits
 *   @retval received  data in rang of 5 to 9 bits
 */
UART_ERROR_t UART_ReceiveBusyWait(u8 *data);

void UART_TransmitString_NoBlock(u8 *str);
void UART_ReceiveString_NoBlock(u8 *str);

/* Enable Interrupts and set call back function */
void UART_RXC_IEN(void (*callbackfun)());
void UART_TXC_IEN(void (*callbackfun)());
void UART_UDRE_IEN(void (*callbackfun)());

UART_ERROR_t UART_Receive_No_Block(u8 *data);

#endif /* UART_INTERFACE_H_ */