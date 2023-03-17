/*
 * exEEPROM.c
 *
 * Created: 3/11/2023 10:27:37 AM
 *  Author: ncm
 */ 

#include "../MCAL/TWI/twi_interface.h"
#include "exEEPROM.h"

#include "../HAL/LCD/LCD.h"


void exEEPROM_voidWriteByte(u8 copyofWordAddrs,u8 copyofByte)
{
	
	// send start condition'
	TWI_enuStartCond() ;
	
	// send chip address + 3 MSBs of word address + W
	if(TWI_enuSelectSlave(0xA0 ,WRITE_OP) == SLA_W_SENT_WITH_ACK_STATE)
	{
		// send rest of addresss
		if(TWI_enuSendByte(copyofWordAddrs)== DATA_SENT_WITH_ACK_STATE)
		{
			// send data byte;
			TWI_enuSendByte(copyofByte);
		}
	}
}

void exEEPROM_voidReadByte(u8 copyofWordAddrs,u8* copyofByte)
{
	
	// send start condition'
	TWI_enuStartCond();
	
	// send chip address + 3 MSBs of word address + W
	if(TWI_enuSelectSlave(0xA0 ,WRITE_OP) == SLA_W_SENT_WITH_ACK_STATE)
	{
	
		// send rest of addresss
		if(TWI_enuSendByte(copyofWordAddrs)== DATA_SENT_WITH_ACK_STATE)
		{
			TWI_enuRepeatedStartCond();
	
			if(TWI_enuSelectSlave(0xA0 ,READ_OP) == SLA_R_SENT_WITH_ACK_STATE)
			{
				// send data byte
				TWI_enuReceiveByte(copyofByte, ACK);
				LCD_WriteString("I write : ");
				LCD_WriteData(*copyofByte);
			}
			
		}
		
	}
}