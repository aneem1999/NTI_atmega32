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
			SET_BIT (DDRA,channel);
		}
		else
		{
			CLEAR_BIT (DDRA,channel);
		}
		break;

	case DIO_PORTB:
		if (direction == OUTPUT)
		{
			SET_BIT (DDRB,channel);
		}
		else
		{
			CLEAR_BIT (DDRB,channel);
		}
		break;

	case DIO_PORTC:
		if (direction == OUTPUT)
		{
			SET_BIT (DDRC,channel);
		}
		else
		{
			CLEAR_BIT (DDRC,channel);
		}
		break;

	case DIO_PORTD:
		if (direction == OUTPUT)
		{
			SET_BIT (DDRD,channel);
		}
		else
		{
			CLEAR_BIT (DDRD,channel);
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
			CLEAR_BIT(PORTA,channel);
		}
		else
		{
			SET_BIT(PORTA,channel);
		}
		break;

	case DIO_PORTB:
		if (level == STD_LOW)
		{
			CLEAR_BIT(PORTB,channel);
		}
		else
		{
			SET_BIT(PORTB,channel);
		}
		break;

	case DIO_PORTC:
		if (level == STD_LOW)
		{
			CLEAR_BIT(PORTC,channel);
		}
		else
		{
			SET_BIT(PORTC,channel);
		}
		break;

	case DIO_PORTD:
		if (level == STD_LOW)
		{
			CLEAR_BIT(PORTD,channel);
		}
		else
		{
			SET_BIT(PORTD,channel);
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
		PORTA &= ~(mask);
		PORTA |=((value << pos) & mask);
		break;

		case DIO_PORTB:
		PORTB &= ~(mask);
		PORTB |=((value <<pos) & mask);
		break;

		case DIO_PORTC:
		PORTC &= ~(mask);
		PORTC |= ((value <<pos) & mask);
		break;

		case DIO_PORTD:
		PORTD &= ~(mask);
		PORTD |= ((value <<pos) & mask);
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
		value = (PINA & mask) >> pos;
		
		break;

		case DIO_PORTB:
		value = (PINB & mask) >> pos;
		
		break;

		case DIO_PORTC:
		value = (PINC & mask) >> pos;
		break;

		case DIO_PORTD:
		value = (PIND & mask) >> pos;
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
		FLIP_BIT(PORTA,channel);
		break;

	case DIO_PORTB:
		FLIP_BIT(PORTB,channel);
		break;

	case DIO_PORTC:
		FLIP_BIT(PORTC,channel);
		break;

	case DIO_PORTD:
		FLIP_BIT(PORTD,channel);
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
		loc_pinRead = CHECK_BIT(PINA, channel);
		break;

	 case DIO_PORTB:
		loc_pinRead = CHECK_BIT(PINB, channel);
		break;

	 case DIO_PORTC:
		loc_pinRead = CHECK_BIT(PINC, channel);
		break;

	 case DIO_PORTD:
		loc_pinRead = CHECK_BIT(PIND, channel);
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
		if(!CHECK_BIT(DDRA,channel))
		{
		SET_BIT(PORTA,channel);	
		}
		break;

		case DIO_PORTB:
		if(!CHECK_BIT(DDRB,channel))
		{
			SET_BIT(PORTB,channel);
		}
		break;

		case DIO_PORTC:
			if(!CHECK_BIT(DDRC, channel))
			{
				SET_BIT(PORTC,channel);
			}
		break;

		case DIO_PORTD:
		if(!CHECK_BIT(DDRD, channel))
		{
			SET_BIT(PORTD,channel);
		}
		break;
	}
}
/**********************************************************************************************************************
 *  END OF FILE: dio.c
 *********************************************************************************************************************/
