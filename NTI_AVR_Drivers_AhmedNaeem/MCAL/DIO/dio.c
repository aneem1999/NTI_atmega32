/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  dio.c
 *        \brief  
 \details  
 *
 *

 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dio.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void dio_vidConfigChannel
						(dio_port_t port, dio_pin_t pin, dio_direction_t direction)        
* \Description     : this service for configuring IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port 	   -> MC port ID
					 channel   -> MC channel ID
					 direction -> MC channel direction
* \Return value:   : None                            
*******************************************************************************/
void dio_vidConfigChannel(dio_portId_t port, dio_channelId_t channel, dio_direction_t direction)
{
	switch (port)
	{
	case DIO_PORTA:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRA_REG,channel);
		}
		else
		{
			CLEAR_BIT (DIO_DDRA_REG,channel);
		}
		break;

	case DIO_PORTB:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRB_REG,channel);
		}
		else
		{
			CLEAR_BIT (DIO_DDRB_REG,channel);
		}
		break;

	case DIO_PORTC:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRC_REG,channel);
		}
		else
		{
			CLEAR_BIT (DIO_DDRC_REG,channel);
		}
		break;

	case DIO_PORTD:
		if (direction == OUTPUT)
		{
			SET_BIT (DIO_DDRD_REG,channel);
		}
		else
		{
			CLEAR_BIT (DIO_DDRD_REG,channel);
		}
		break;
	}
}

/******************************************************************************
* \Syntax          : void dio_vidWriteChannel
						(dio_portId_t port, dio_channelId_t channel, dio_level_t level)      
* \Description     : this service for writting on IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port 	  -> MC port ID
					 channel  -> MC channel ID
					 level    -> MC channel level
* \Return value:   : None                            
*******************************************************************************/
void dio_vidWriteChannel(dio_portId_t port, dio_channelId_t channel, dio_level_t level)
{
	switch (port)
	{
	case DIO_PORTA:
		if (level == STD_LOW)
		{
			CLEAR_BIT(DIO_PORTA_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTA_REG,channel);
		}
		break;

	case DIO_PORTB:
		if (level == STD_LOW)
		{
			CLEAR_BIT(DIO_PORTB_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTB_REG,channel);
		}
		break;

	case DIO_PORTC:
		if (level == STD_LOW)
		{
			CLEAR_BIT(DIO_PORTC_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTC_REG,channel);
		}
		break;

	case DIO_PORTD:
		if (level == STD_LOW)
		{
			CLEAR_BIT(DIO_PORTD_REG,channel);
		}
		else
		{
			SET_BIT(DIO_PORTD_REG,channel);
		}
		break;
	}
}

/******************************************************************************
* \Syntax          :void dio_vidWriteChannelGroup
						(dio_portId_t port,u8 value,u8 mask)
* \Description     : this service for writting on group of IO channels                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 value -> data value
					 mask  -> data mask
* \Return value:   : None                            
*******************************************************************************/
void dio_vidWriteChannelGroup(dio_portId_t port,u8 value,u8 mask)
{
	u8 pos=0 , tmask = mask;
	while(!(tmask & 1))
	{
		pos++;
		tmask >>= 1;
	}
	switch (port)
	{
		case DIO_PORTA:
		DIO_PORTA_REG &= ~(mask);
		DIO_PORTA_REG |=((value << pos) & mask);
		break;

		case DIO_PORTB:
		DIO_PORTB_REG &= ~(mask);
		DIO_PORTB_REG |=((value <<pos) & mask);
		break;

		case DIO_PORTC:
		DIO_PORTC_REG &= ~(mask);
		DIO_PORTC_REG |= ((value <<pos) & mask);
		break;

		case DIO_PORTD:
		DIO_PORTD_REG &= ~(mask);
		DIO_PORTD_REG |= ((value <<pos) & mask);
		break;
	}
	
	
}
u8 dio_vidReadChannelGroup(dio_portId_t port,u8 mask)
{
	/*	show me your code */
	u8 value=0;
	u8 pos=0 , tmask = mask;
	while(!(tmask & 1))
	{
		pos++;
		tmask >>= 1;
	}
	switch (port)
	{
		case DIO_PORTA:
		value = (DIO_PINA_REG & mask) >> pos;
		
		break;

		case DIO_PORTB:
		value = (DIO_PINB_REG & mask) >> pos;
		
		break;

		case DIO_PORTC:
		value = (DIO_PINC_REG & mask) >> pos;
		break;

		case DIO_PORTD:
		value = (DIO_PIND_REG & mask) >> pos;
		break;
	}
	
	return value;
}

/******************************************************************************
* \Syntax          :void dio_vidFlipChannel
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for fliping IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : None                            
*******************************************************************************/
void dio_vidFlipChannel(dio_portId_t port, dio_channelId_t channel)
{
	switch (port)
	{
	case DIO_PORTA:
		FLIP_BIT(DIO_PORTA_REG,channel);
		break;

	case DIO_PORTB:
		FLIP_BIT(DIO_PORTB_REG,channel);
		break;

	case DIO_PORTC:
		FLIP_BIT(DIO_PORTC_REG,channel);
		break;

	case DIO_PORTD:
		FLIP_BIT(DIO_PORTD_REG,channel);
		break;
	}
}

/******************************************************************************
* \Syntax          :dio_level_t Dio_dioLevelReadChannel
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for reading IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port     -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : loc_pinRead   -> IO channel level                           
*******************************************************************************/
dio_level_t dio_dioLevelReadChannel(dio_portId_t port, dio_channelId_t channel)
{
	dio_level_t loc_pinRead = STD_LOW;
	switch (port)
	{
	 case DIO_PORTA:
		loc_pinRead = CHECK_BIT(DIO_PINA_REG, channel);
		break;

	 case DIO_PORTB:
		loc_pinRead = CHECK_BIT(DIO_PINB_REG, channel);
		break;

	 case DIO_PORTC:
		loc_pinRead = CHECK_BIT(DIO_PINC_REG, channel);
		break;

	 case DIO_PORTD:
		loc_pinRead = CHECK_BIT(DIO_PIND_REG, channel);
		break;
    }
	return loc_pinRead;
}

/******************************************************************************
* \Syntax          :void dio_vidEnablePullUp
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for enabling pull up resistor for IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : None                            
*******************************************************************************/
void dio_vidEnablePullUp(dio_portId_t port, dio_channelId_t channel)
{
	/*	show me your code */
	switch (port)
	{
		case DIO_PORTA:
		if(!CHECK_BIT(DIO_DDRA_REG,channel))
		{
		SET_BIT(DIO_PORTA_REG,channel);	
		}
		break;

		case DIO_PORTB:
		if(!CHECK_BIT(DIO_DDRB_REG,channel))
		{
			SET_BIT(DIO_PORTB_REG,channel);
		}
		break;

		case DIO_PORTC:
			if(!CHECK_BIT(DIO_DDRC_REG, channel))
			{
				SET_BIT(DIO_PORTC_REG,channel);
			}
		break;

		case DIO_PORTD:
		if(!CHECK_BIT(DIO_DDRD_REG, channel))
		{
			SET_BIT(DIO_PORTD_REG,channel);
		}
		break;
	}
}
/**********************************************************************************************************************
 *  END OF FILE: dio.c
 *********************************************************************************************************************/
