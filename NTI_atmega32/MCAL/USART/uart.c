
/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   19/2023 6:28:10 AM
 *       @file   :   UART.c
 *************************************************************/

/*************************************************************
 *    Includes
 *************************************************************/
#include "uart_cfg.h"
#include "uart_interface.h"

#include "../HAL/LCD/LCD.h"

/* Interrupts callback functions*/
void (*UART_RXC_CallBack)();
void (*UART_UDRE_CallBack)();
void (*UART_TXC_CallBack)();

UART_ERROR_t UART_Init()
{
    UART_ERROR_t UART_state = UART_CONFIG_OK;
    u8 UCSRC_temp = 0;
    /* Set baud rate */
    UBRRH = (unsigned char)(UBRR_VAL(UART_Configuration.BR) >> 8);
    UBRRL = (unsigned char)UBRR_VAL(UART_Configuration.BR);
#if 0
    
    /* Enable receiver and transmitter */
    UCSRB = (1 << 4) | (1 << 3);
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (1 << 7) | (3 << 1);
#endif
#if 1

    // UCSRC access
    SET_BIT(UCSRC_temp, 7);
    switch (UART_Configuration.DataLength)
    {
    case 5:
        CLEAR_BIT(UCSRB, 2);

        break;
    case 6:
        SET_BIT(UCSRC_temp, 1);
        CLEAR_BIT(UCSRB, 2);
        break;
    case 7:
        CLEAR_BIT(UCSRC, 1);
        SET_BIT(UCSRC, 2);
        CLEAR_BIT(UCSRB, 2);
        break;
    case 8:
        UCSRC_temp = (1 << 7) | (3 << 1);
        break;
    case 9:
        SET_BIT(UCSRC_temp, 1);
        SET_BIT(UCSRC_temp, 2);
        SET_BIT(UCSRB, 2);
        break;
    default:
        UART_state = UART_CONFIG_ERROR;
    }
    // Parity
    switch (UART_Configuration.Parity)
    {
    case UART_PARTY_DISABLE:
        CLEAR_BIT(UCSRC_temp, 4);
        CLEAR_BIT(UCSRC_temp, 5);
        break;
    case UART_PARTY_EVEN:
        CLEAR_BIT(UCSRC_temp, 4);
        SET_BIT(UCSRC_temp, 5);
        break;
    case UART_PARTY_ODD:
        SET_BIT(UCSRC_temp, 4);
        SET_BIT(UCSRC_temp, 5);
        break;
    default:
        UART_state = UART_CONFIG_ERROR;
    }

    // 1 or 2 stop bits
    switch (UART_Configuration.Stopbts)
    {
    case 1:
        CLEAR_BIT(UCSRC_temp, 3);
        break;
    case 2:
        SET_BIT(UCSRC_temp, 3);
        break;
    default:
        UART_state = UART_CONFIG_ERROR;
    }

    // enable module
    // specify mode TX , RX , TX and RX
    switch (UART_Configuration.Mode)
    {
    case UART_MODE_RX:
        SET_BIT(UCSRB, 4);
        break;
    case UART_MODE_TX:
        SET_BIT(UCSRB, 3);
        break;
    case UART_MODE_TX_RX:
        SET_BIT(UCSRB, 3);
        SET_BIT(UCSRB, 4);
        break;
    default:
        UART_state = UART_CONFIG_ERROR;
    }

    UCSRC = UCSRC_temp;
#endif
    return UART_state;
}

UART_ERROR_t UART_TransmitBusyWait(u8 data)
{
    UART_ERROR_t UART_state = UART_TRANSMIT_OK;

    // polling UDRE flag
    while (!CHECK_BIT(UCSRA, 5))
        ;

    UCSRB |= CHECK_BIT(data, 8); // 9th at bit0 in UCSRB
    UDR = (u8)data;

    return UART_state;
}

/***************************************************************/
u8 RX_No_Block_Buffer ='z';
UART_ERROR_t RX_No_Block_State;

void CB_RX()
{
    if (CHECK_BIT(UCSRA, 2) || CHECK_BIT(UCSRA, 3) || CHECK_BIT(UCSRA, 4))
    {
        /* Error frame , Parity Error , Overrun Error*/
        RX_No_Block_State = UART_RECIEVE_ERROR;
    }
    else
    {
    RX_No_Block_Buffer = UDR;
    
        RX_No_Block_State = UART_RECIEVE_OK;
    }
}
UART_ERROR_t UART_Receive_No_Block(u8 *data)
{

    UART_RXC_IEN(CB_RX);

    *data = RX_No_Block_Buffer;

    return RX_No_Block_State;
}

/***************************************************/
UART_ERROR_t UART_ReceiveBusyWait(u8 *data)
{

    UART_ERROR_t UART_state = UART_RECIEVE_ERROR;

    // polling RXC
    while (!CHECK_BIT(UCSRA, 7))
        ; /* Wait while busy*/
    if (CHECK_BIT(UCSRA, 2) || CHECK_BIT(UCSRA, 3) || CHECK_BIT(UCSRA, 4))
    {
        /* Error frame , Parity Error , Overrun Error*/
        UART_state = UART_RECIEVE_ERROR;
    }
    else
    {
        UART_state = UART_RECIEVE_OK;
    }

    *data = UDR;

    return UART_state;
}

/************************************************************************************/
u8 TX_Buffer[200];

void ISR_TXC()
{

    static u8 index = 1;

    if (TX_Buffer[index] != '\0')
    {
        UDR = TX_Buffer[index];
        index++;
    }
    else
    {
        index = 1;
        // stop interrupt
        CLEAR_BIT(UCSRB, 6);
    }
}
void UART_TransmitString_NoBlock(u8 *str)
{

    u8 index = 0;

    while (str[index] != '\0')
    {
        TX_Buffer[index] = str[index];
        index++;
    }
    TX_Buffer[index] = '\0';

    UART_TXC_IEN(ISR_TXC);
    UART_TransmitBusyWait(TX_Buffer[0]);
}

/************************************************************************************/
/************************************************************************************/
u8 *RX_Buffer;
static void ISR_RXC()
{
    static u8 index = 0;
    RX_Buffer[index] = UDR;
    if (UDR == Default_STOP)
    {
        index = 0;
        // stop interrupt
        CLEAR_BIT(UCSRB, 7);
    }
    else
    {
        index++;
    }
}
void UART_ReceiveString_NoBlock(u8 *str)
{
    RX_Buffer = str;
    UART_RXC_IEN(ISR_RXC);
}

/************************************************************************************/

void UART_RXC_IEN(void (*callbackfun)())
{
    // enable RXI
    SET_BIT(UCSRB, 7);
    // Set callback function
    UART_RXC_CallBack = callbackfun;
}
void UART_TXC_IEN(void (*callbackfun)())
{
    // enable TXI
    SET_BIT(UCSRB, 6);
    // Set callback function
    UART_TXC_CallBack = callbackfun;
}
void UART_UDRE_IEN(void (*callbackfun)())
{
    // enable UDRE
    SET_BIT(UCSRB, 5);
    // Set callback function
    UART_UDRE_CallBack = callbackfun;
}

/*
13	USART Rx Complete			USART_RX_vect
14	USART Data Register Empty	USART_UDRE_vect
15	USART Tx Complete			USART_TX_vect */

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
    if (UART_RXC_CallBack != NULL)
    {
        UART_RXC_CallBack();
    }
}

void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
    if (UART_UDRE_CallBack != NULL)
    {
        UART_UDRE_CallBack();
    }
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
    if (UART_TXC_CallBack != NULL)
    {
        UART_TXC_CallBack();
    }
}