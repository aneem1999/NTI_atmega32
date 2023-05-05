/*
 * ComManage.c
 *
 * Created: 3/27/2023 10:48:54 AM
 *  Author: ncm
 */
#include "ComManage.h"

#include "../../MCAL/USART/uart_interface.h"

/*************************** Buffers **********************************/
u8 TRANSMIT_Buffer[30];
u8 RECEIVE_Buffer[30];

/*************************** Received Flag ****************************/

boolean Receive_Mssge_Complete = FALSE;

/**************************** Helper functions ***********************/

/**
 * @brief  TX interrupt handler
 *
 */
static void ISR_TXC()
{

    static u8 index = 1;

    if (TRANSMIT_Buffer[index] != '\0')
    {
        UART_Set_Data_Reg(TRANSMIT_Buffer[index]);
        index++;
    }
    else
    {
        index = 1;
    }
}

static void ISR_RXC()
{
    static u8 index = 0;
    u8 Rva = UART_Read_Data_Reg();

       if (Rva == '\r')
    {

        RECEIVE_Buffer[index] = '\0';
        Receive_Mssge_Complete = TRUE;

        index = 0;
    }
    else
    {
        RECEIVE_Buffer[index] = Rva;
        index++;
    }
}

/********************************************************
 * @brief init communication method
 *
 */

void ComM_Init(void)
{
    /* Init UART */
    UART_Init();
    UART_RXC_IEN(ISR_RXC);
    /* Enable Transmit complete interrupt*/
    UART_TXC_IEN(ISR_TXC);
}

/************************************************************
 * @brief : send massage
 *
 * @param mssg
 */

void ComM_SendMssg(u8 mssg[])
{

    u8 index = 0;

    /* coping in global buffer*/
    while (mssg[index] != '\0')
    {
        TRANSMIT_Buffer[index] = mssg[index];
        index++;
    }

    TRANSMIT_Buffer[index] = '\0';

    /* Transmit first byte busy wait */
    UART_TransmitBusyWait(TRANSMIT_Buffer[0]);
}

/*******************************************************
 * @brief Receive message
 *
 * @param mssg
 */
void ComM_ReceiveMssg(u8 **mssg)
{

    *mssg = RECEIVE_Buffer;
}
boolean ComM_MssgIsReceived(void)
{
    boolean Rvalue = FALSE;
    if (Receive_Mssge_Complete == TRUE)
    {
        Receive_Mssge_Complete = FALSE;
        Rvalue = TRUE;
    }
    else
    {
        Rvalue = FALSE;
    }

    return Rvalue;
}

void ComM_RxComplete_Clbk(void)
{
}
void ComM_TxComplete_Clbk(void)
{
}
