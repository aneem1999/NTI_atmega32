/*
 * twi.c
 *
 * Created: 3/5/2023 2:43:08 PM
 *  Author: ncm
 */ 

#include "twi_interface.h"

/* enable TWI peripheral */
void TWI_Init()
{
	SET_BIT(TWCR ,2);
}

/* Disable TWI peripheral */
void TWI_Deinit()
{
	CLEAR_BIT(TWCR ,2);
}


/*************************************************************
 *
 *	 @fun		- TWI_SetBitRate
 *	 @param [in]- BitRate  bit rate with max value 400,000 (400 KHZ)
 *   @brief     - initialize TWI set prescaler and bit rate
 *   @retval    - None
 */
void TWI_SetBitRate(u32 BitRate)
{
	TWSR = TWI_PS & 0x03;
	TWBR = TWI_BITRATE(BitRate);
}

/*************************************************************
 *	 @fun		- TWI_Start
 *   @brief     - send start condition 
 *   @retval    - TWI_ERROR_t  ---> EVENT_OK_STATE      SUCCESS State
 *							   ---> EVENT_ERROR_STATE   FAILD State
 */
TWI_ERROR_t TWI_Start(void)
{
	TWI_ERROR_t EVENT_State;
	/* Clear TWINT (set TWCR bit 7 TWSTA) 
	
	Send start condition (set TWCR bit 5) */
	TWCR |= (1 << 7) |(1<<2)| (1 << 5);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	/* Check Status of send start */
	if (READ_TWI_EVENT_STATE() == START_STATE)
	{
		TWCR |= (1 << 7) | (1<<2);
		EVENT_State = EVENT_OK_STATE;
		
	}
	else
	{
		EVENT_State = EVENT_ERROR_STATE;
	}
	return EVENT_State;
	
	
}

/*************************************************************
 *	 @fun		- TWI_RepeatedStart
 *   @brief     - send repeated start condition 
 *   @retval    - SWI_ERROR_t  ---> EVENT_OK_STATE      SUCCESS State
 *							   ---> EVENT_ERROR_STATE   FAILD State
 */
TWI_ERROR_t TWI_RepeatedStart(void)
{
	TWI_ERROR_t EVENT_State;
	/* Clear TWINT (set TWCR bit 7 TWSTA) */
	/*Enable TWI   (set TWCR bit 2)  */
	/* Send start condition (set TWCR bit 5) */
	TWCR |= (1 << 7) | (1<<2) | (1 << 5);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7))
	;
	/* Check Status of send start */
	if (READ_TWI_EVENT_STATE() == REPSTART_STATE)
	{
		TWCR |= (1 << 7) | (1<<2);
		
		EVENT_State = EVENT_OK_STATE;
	}
	else
	{
		EVENT_State = EVENT_ERROR_STATE;
	}
	return EVENT_State;
}

/*************************************************************
 *	 @fun		- TWI_SlaveSelect
 *	 @param [in]- SLA   -> 7 bit slave Slave address
 *	 @param [in]- RW    -> read or write operation (TWI_RW_OP_t)
 *   @brief     - send selected slave address
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_SlaveSelect(u8 SLA, TWI_RW_OP_t RW)
{
	
	TWDR = (SLA & 0x7f) | (RW<<7) ;
	TWCR |= (1 << 7) | (1<<2);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	return READ_TWI_EVENT_STATE();
	
	
}

/*************************************************************
 *	 @fun		- TWI_SendData
 *	 @param [in]- CopyofData  8 bit data
 *   @brief     - send data
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_SendByte(u8 CopyofData)
{
	
	TWDR = CopyofData;
	TWCR |= (1 << 7) | (1<<2);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	
	return READ_TWI_EVENT_STATE();

	
}

/*************************************************************
 *	 @fun		- TWI_ReceiveByte
 *	 @param [In]  ack  (ACK/NACK)
 *	 @param [Out] CopyofData  -> 8 bit data
 *   @brief     - Receive data then send ACK or NACK
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_ReceiveByte(u8 *CopyofData, TWI_ACK_t ack)
{
	*CopyofData = TWDR;
	
	/* SEND ACK OR NACK condation */
	CLEAR_BIT(TWCR,6);
	TWCR |= (ack << 6);
	TWCR |= (1 << 7) | (1<<2);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	return READ_TWI_EVENT_STATE();
	
}

/*************************************************************
 *	 @fun		- TWI_Stop
 *   @brief     - send stop condition
 *   @retval    - None
 */
void TWI_Stop(void)
{
	TWCR |= (1 << 7) | (1<<2) | (1<<4);
	/* Busy wait until STOP bit is set */
	while (CHECK_BIT(TWCR, 4));
	
}

/*************************************************************
 *	 @fun		- TWI_SetSlaveAddress
 *	 @param [in]- CopyofSLA  7 bit address (bit 0 is neglected)
 *   @brief     - send data
 *   @retval    - None
 */
void TWI_SetSlaveAddress(u8 CopyofSLA)
{
	TWAR = CopyofSLA;
	TWCR=(1<<2)|(1<<6)|(1<<7);
}