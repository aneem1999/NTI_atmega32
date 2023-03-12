/*
 * twi.c
 *
 * Created: 3/5/2023 2:43:08 PM
 *  Author: ncm
 */ 

#include "twi_interface.h"

/* Disable TWI peripheral */
void TWI_voidDeinit()
{
	CLEAR_BIT(TWCR ,2);
}


/*************************************************************
 *
 *	 @fun		- TWI_SetBitRate
 *	 @param [in]- BitRate bit rate with max value 400,000 (400 KHZ)
 *   @brief     - Enable TWI and set prescaler and bit rate of clock
 *   @retval    - None
 */
void TWI_Master_voidInit(u32 BitRate)
{
	TWSR = TWI_PS & 0x03;
	
	TWBR = TWI_BITRATE(BitRate);
	
	SET_BIT(TWCR,6);
	
	/* Enable TWI */
	SET_BIT(TWCR,2);
}

/*************************************************************
 *	 @fun		- TWI_enuStartCond
 *   @brief     - send start condition 
 *   @retval    - TWI_ERROR_t  ---> EVENT_OK_STATE      SUCCESS State
 *							   ---> EVENT_ERROR_STATE   FAILD State
 */
TWI_ERROR_t TWI_enuStartCond(void)
{
	TWI_ERROR_t EVENT_State;
	/* Clear TWINT (set TWCR bit 7 TWSTA) 
	
	Send start condition (set TWCR bit 5) and clear TWINT */
	TWCR |= (1 << 7) | (1 << 5);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	/* Check Status of send start */
	if (READ_TWI_EVENT_STATE() == START_STATE)
	{
		EVENT_State = EVENT_OK_STATE;
		
	}
	else
	{
		EVENT_State = EVENT_ERROR_STATE;
	}
	return EVENT_State;
	
	
}

/*************************************************************
 *	 @fun		- TWI_enuRepeatedStartCond
 *   @brief     - send repeated start condition 
 *   @retval    - SWI_ERROR_t  ---> EVENT_OK_STATE      SUCCESS State
 *							   ---> EVENT_ERROR_STATE   FAILD State
 */
TWI_ERROR_t TWI_enuRepeatedStartCond(void)
{
	TWI_ERROR_t EVENT_State;
	/* Clear TWINT (set TWCR bit 7 TWSTA) */
	/*Enable TWI   (set TWCR bit 2)  */
	/* Send start condition (set TWCR bit 5) */
	TWCR |= (1 << 7)  | (1 << 5);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7))
	;
	/* Check Status of send start */
	if (READ_TWI_EVENT_STATE() == REPSTART_STATE)
	{
		EVENT_State = EVENT_OK_STATE;
	}
	else
	{
		EVENT_State = EVENT_ERROR_STATE;
	}
	return EVENT_State;
}

/*************************************************************
 *	 @fun		- TWI_enuSelectSlave
 *	 @param [in]- SLA   -> 7 bit slave Slave address
 *	 @param [in]- RW    -> read or write operation (TWI_RW_OP_t)
 *   @brief     - send selected slave address
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_enuSelectSlave(u8 SLA, TWI_RW_OP_t RW)
{
	
	TWDR = SLA  | RW ;
	CLEAR_BIT(TWCR,5);
	TWCR |= (1 << 7);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	return READ_TWI_EVENT_STATE();
	
	
}

/*************************************************************
 *	 @fun		- TWI_enuSendByte
 *	 @param [in]- CopyofData  8 bit data
 *   @brief     - send data
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_enuSendByte(u8 CopyofData)
{
	
	TWDR = CopyofData;
	TWCR |= (1 << 7) ;
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	
	
	return READ_TWI_EVENT_STATE();

	
}

/*************************************************************
 *	 @fun		- TWI_enuReceiveByte
 *	 @param [In]  ack  (ACK/NACK)
 *	 @param [Out] CopyofData  -> 8 bit data
 *   @brief     - Receive data then send ACK or NACK
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_enuReceiveByte(u8 *CopyofData, TWI_ACK_t ack)
{
	
	/* turn off flag  & Enable/Disable ACK/NACK condition */
	CLEAR_BIT(TWCR,6);
	TWCR |= (1 << 7)|(ack << 6);
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
	    *CopyofData = TWDR;
	    
	return READ_TWI_EVENT_STATE();
	
	
}

/*************************************************************
 *	 @fun		- TWI_Stop
 *   @brief     - send stop condition
 *   @retval    - None
 */
void TWI_voidStopCond(void)
{
	TWCR |= (1 << 7) | (1<<4);
}

/*************************************************************
 *	 @fun		- TWI_Salve_voidInit
 *	 @param [in]- init salve CopyofSLA  7 bit address (bit 0 is neglected)
 *   @brief     - send data
 *   @retval    - None
 */
void TWI_Salve_voidInit(u8 CopyofSLA)
{
	
	/* Enable TWI */
	TWCR=(1<<2)|(1<<6);
	
	TWAR = CopyofSLA <<1;
}


void TWI_Salve_voidLisent(u8 CopyofSLA)
{
	/* Busy wait until TWINT is set */
	while (!CHECK_BIT(TWCR, 7));
}
