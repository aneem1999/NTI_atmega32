/***************************************************************
     @author             :    Ahmed Naeem
     @date 				 :    4 Mar 11:15:02 AM
     @version 			 :    1.0V
     @brief 		     :    interface file  file [_interface.h]
***************************************************************/
#include "../LIB/register.h"
#include "../LIB/std_types.h"
#include "../LIB/bit_math.h"
				    	
#include "spi_interface.h"
#include "spi_cfg.h"



void SPI_voidMasterInit()
{
	/* Set MOSI(PB5) and SCK(PB7) output, all others input b7, b4*/   
	SET_BIT(DDRB,5);
	SET_BIT(DDRB,7);
	CLEAR_BIT(DDRB,6);
	
	// set clk frequency
	SPCR &= ~(0x03);
	#if SPI_PCK_Prescaler > 3
	SET_BIT(SPSR,0);
	#endif
	SPCR |= SPI_PCK_Prescaler & (0x03);
	
	// set data order
	CLEAR_BIT(SPCR,5);
	SPCR |= (SPI_DATA_Order<<5);
	
	// select clock polarity and phase
	CLEAR_BIT(SPCR, 3);
	SPCR |= (SPI_CPOL<<3);
	CLEAR_BIT(SPCR,2 );
	SPCR |= (SPI_CPHA<<2);
	
	// enable SPI
	SET_BIT(SPCR,6);
	// enable master mode
	SET_BIT(SPCR,4);
	
	

	
}

void SPI_voidSlaveInit()
{
	/* Set MISO output, all others input */
	CLEAR_BIT(DDRB,5);
	SET_BIT(DDRB,6);
	CLEAR_BIT(DDRB,7);
	CLEAR_BIT(DDRB,4);
	
	// set data order
	CLEAR_BIT(SPCR,5);
	SPCR |= (SPI_DATA_Order<<5);
	
	// select clock polarity and phase
	CLEAR_BIT(SPCR, 3);
	SPCR |= (SPI_CPOL<<3);
	CLEAR_BIT(SPCR,2 );
	SPCR |= (SPI_CPHA<<2);
	
	// enable slave mode
	CLEAR_BIT(SPCR,4);
	
	// enable SPI
	SET_BIT(SPCR,6);
	
	
}



/*************************************************************
 *  
 *   @param [in]- data buffer (recived or transfered)  (8 bit length)
 *   @brief     - Transmit and receive Via SPI
 *                write into data register --> polling SPIF --> read data register
 *                in send
 *   @retval    - recived or transfered data value (8 bit length)
 */

void SPI_voidTransmit(u8 data)
{
	SPDR =data;
	while(!CHECK_BIT(SPSR,7));
}


u8 SPI_u8Recieve()
{
	while(!CHECK_BIT(SPSR,7));
	return SPDR;
	
}



void SPI_voidIEN(void (*CallBack)())
{	
		/* Enable Global interrupt flag*/
		GIE_ENABLE();
		
		SET_BIT(SPCR,7);
		/*Code to execute whenever transmission/receptionis complete.
		SPIF  is cleared by hardware when executing the corresponding 
		interrupt handling vector*/
		GP_SPI_CallBack = CallBack;
}



/* SPI Transmission/reception complete ISR */
void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	

	/* call back function */
	GP_SPI_CallBack();
}
