/*
 * twi_interface.h
 *
 * Created: 3/5/2023 2:02:21 PM
 *  Author: ncm
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/********************************************************************
--------------------------- includes -------------------------------
*********************************************************************/
#include "math.h"
#include "../LIB/std_types.h"
#include "../LIB/register.h"
#include "../LIB/bit_math.h"

/********************************************************************
------------------------ TWI Errors  -----------------------------
*********************************************************************/
typedef enum
{
 EVENT_ERROR_STATE,
 EVENT_OK_STATE,
 START_STATE				  =	0x08,
 REPSTART_STATE				  =	0x10,
 SLA_W_SENT_WITH_ACK_STATE	  =	0x18,
 SLA_W_SENT_WITH_NACK_STATE	  =	0x20,
 DATA_SENT_WITH_ACK_STATE	  =	0x28,
 DATA_SENT_WITH_NACK_STATE	  =	0x30,
 ARBIT_LOST_STATE		      = 0x38,
 SLA_R_SENT_WITH_ACK_STATE	  =	0x40,
 SLA_R_SENT_WITH_NACK_STATE	  =	0x48,
 DATA_RECIVED_WITH_ACK_STATE  =	0x50,
 DATA_RECIVED_WITH_NACK_STATE =	0x58,
 SLA_RECIVED_WITH_ACK_STATE	  =	0x40,
 SLA_RECIVED_WITH_NACK_STATE  =	0x48

} TWI_ERROR_t;

/********************************************************************
------------------------ Configurations -----------------------------
*********************************************************************/

/* enum for read or write*/
typedef enum
{
	WRITE_OP,
	READ_OP
} TWI_RW_OP_t;
/* enum for ACK Enable*/
typedef enum
{
	NACK,
	ACK,
} TWI_ACK_t;

/* @ref TWI_PS */
typedef enum
{
 TWI_PS_1,
 TWI_PS_4,
 TWI_PS_16,
 TWI_PS_64
 
}TWI_PS_t;


#define TWI_PS TWI_PS_16

/*-*-*-*-*-*-*-*-*-*-*-* Bit rate Settings *-*-*-*-*-*-*-*-*-*-*-*-*/
#define F_CPU 16000000U


/*-*-*-*-*-*-*-*-*-*-*-* Bit rate Settings *-*-*-*-*-*-*-*-*-*-*-*-*/
#define TWI_BITRATE(SCL_CLK) (((F_CPU / SCL_CLK) - 16) / (2 * pow(4, TWI_PS)))


/********************************************************************
--------------------------- TWI States ---------------------------
*********************************************************************/



/********************************************************************
-------------------------- Helper Macros ---------------------------
*********************************************************************/
#define READ_TWI_EVENT_STATE() (TWSR & 0xf8)

/********************************************************************
---------------------------- TWI APIs ------------------------------
*********************************************************************/

/*************************************************************
 *
 *	 @fun		- TWI_SetBitRate
 *	 @param [in]- BitRate bit rate with max value 400,000 (400 KHZ)
 *   @brief     - Enable TWI and set prescaler and bit rate of clock
 *   @retval    - None
 */
void TWI_Master_voidInit(u32 BitRate);

/*************************************************************
 *	 @fun		- TWI_enuStartCond
 *   @brief     - send start condition 
 *   @retval    - TWI_ERROR_t  ---> EVENT_OK_STATE      SUCCESS State
 *							   ---> EVENT_ERROR_STATE   FAILD State
 */
TWI_ERROR_t TWI_enuStartCond(void);

/*************************************************************
 *	 @fun		- TWI_enuRepeatedStartCond
 *   @brief     - send repeated start condition 
 *   @retval    - SWI_ERROR_t  ---> EVENT_OK_STATE      SUCCESS State
 *							   ---> EVENT_ERROR_STATE   FAILD State
 */
TWI_ERROR_t TWI_enuRepeatedStartCond(void);

/*************************************************************
 *	 @fun		- TWI_enuSelectSlave
 *	 @param [in]- SLA   -> 7 bit slave Slave address
 *	 @param [in]- RW    -> read or write operation (TWI_RW_OP_t)
 *   @brief     - send selected slave address
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_enuSelectSlave(u8 SLA, TWI_RW_OP_t RW);

/*************************************************************
 *	 @fun		- TWI_enuSendByte
 *	 @param [in]- CopyofData  8 bit data
 *   @brief     - send data
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_enuSendByte(u8 CopyofData);

/*************************************************************
 *	 @fun		- TWI_enuReceiveByte
 *	 @param [In]  ack  (ACK/NACK)
 *	 @param [Out] CopyofData  -> 8 bit data
 *   @brief     - Receive data then send ACK or NACK
 *   @retval    - Status of send SLA + RW according to twi status register
 */
TWI_ERROR_t TWI_enuReceiveByte(u8 *CopyofData, TWI_ACK_t ack);

/*************************************************************
 *	 @fun		- TWI_Stop
 *   @brief     - send stop condition
 *   @retval    - None
 */
void TWI_voidStopCond(void);

/*************************************************************
 *	 @fun		- TWI_Salve_voidInit
 *	 @param [in]- init salve CopyofSLA  7 bit address (bit 0 is neglected)
 *   @brief     - send data
 *   @retval    - None
 */
void TWI_Salve_voidInit(u8 CopyofSLA);


void TWI_Salve_voidLisent(u8 CopyofSLA);

#endif /* TWI_INTERFACE_H_ */