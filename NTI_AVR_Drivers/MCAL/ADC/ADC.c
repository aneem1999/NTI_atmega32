/***********************************************************
	Author 	 	 : Ahmed Naeem
	Date   		 : 24 feb 2023
	Version 	 : 1V
	Description	 : implementation  for ADC
***********************************************************/

/****************************************************************
*********************** STD LIB DIRECTIVES *********************
****************************************************************/
#include "../LIB/bit_math.h"
#include "../LIB/std_types.h"
#include "../LIB/register.h"
#include "../HAL/LED/led.h"

#define F_CPU 16000000U
#include <util/delay.h>

/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/

#include "ADC_int.h"

/****************************************************************/
/************************ Global variables  *********************/
/****************************************************************/
void (*GP_ADC_Callback)(void);

/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/

/*****************************************************************
 *   @param [in]- ADC_Config_t
 *   @brief  in This function used to initialize ADC
 *   @retval void
 *****************************************************************/
void ADC_voidInit(ADC_Config_t *copyofADCconfig)
{

	/*referene selection */
	ADMUX &= 0x3f; /* clear Bit 7:6 – REFS1:0: Reference Selection Bits*/
	ADMUX |= ((copyofADCconfig->voltageReference << 6) & 0xc0);

	/* adjustment selection*/
	CLEAR_BIT(ADMUX, 5);
	ADMUX |= ((copyofADCconfig->adjustment & 0x1) << 5);

	/*channel selection*/
	ADMUX &= 0x70; /* Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits */
	ADMUX |= ((copyofADCconfig->channel << 4) & 0x0f);

	/* prescaller selection*/
	ADCSRA &= 0xf8; /*Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits*/
	ADCSRA |= ((copyofADCconfig->prescaler) & 0x07);

	/*Init channel as input*/
	CLEAR_BIT(DDRA, copyofADCconfig->channel);
}

/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Enable ADC
 *
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidEnable()
{
	SET_BIT(ADCSRA, 7);
}

/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Enable ADC Interrput
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidInterrputEnable()
{
	SET_BIT(ADCSRA, 3);
}

/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Enable ADC Interrput
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidDisable()
{

	CLEAR_BIT(ADCSRA, 7);
}

/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Start converting of ADC
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidStartConversion()
{
	SET_BIT(ADCSRA, 6);
}

/*****************************************************************
 *   @param [in] ADC_Config_t *copyofADCconfig
 *   @brief This function used to Set latch Interrupt happens.
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidAutoTrigger(ADC_Config_t *copyofADCconfig)
{

	/** Enable ADC Auto Trigger	 							   **/
	/** ADATE = 1 =====> 	SET_BIT( ADATE , 5 ); 			   **/

	SET_BIT(ADCSRA, 5);

	/* select auto trigger source */
	SFIOR &= 0x1f; /*clear Bit 7:5 – ADTS2:0: ADC Auto Trigger Source*/
	SFIOR |= (copyofADCconfig->AutoTriggerSource << 5) & 0xe0;
}

/*****************************************************************
 *   @param [in] Pointer struct of ADC configuration
 *   @brief This function used to read ADC with polling mechanism
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
u16 ADC_u16ReadADCwithBlock(ADC_Config_t *copyofADCconfig)
{
	u16 ADCvalue = 0;

	/* polling*/
	while ((ADCSRA & (1 << 4)) == 0)
		;
	if (copyofADCconfig->adjustment == RIGHT_ADJUSTMENT)
	{
		ADCvalue = ADC;
	}
	else if (copyofADCconfig->adjustment == LEFT_ADJUSTMENT)
	{
		ADCvalue = ADC >> 6;
	}

	return ADCvalue;
}

/*****************************************************************
 *   @param [in] addresscpy pointer to callback function
 *   @brief This function used to communicate with the
 *				function in App Layer(The Callback function)
 *   @retval void
 *   @Precondition 1-this function must be used after ADC initialized
 * 				   2- ADC must be enabled
 * 				   3- GIE and ADCIE must be set
 *
 *****************************************************************/
void ADC_voidSetCallbackFun(pf addresscpy)
{
	GP_ADC_Callback = addresscpy;
}

/*****************************************************************
 *   @param [in]  copyofADCconfig
 *   @brief Read ADC digital value
 *   @retval u16  of ADC digital value
 *
 *
 *****************************************************************/
u16 ADC_u16ReadADC(ADC_Config_t *copyofADCconfig)
{
	u16 ADCvalue = 0;

	if (copyofADCconfig->adjustment == RIGHT_ADJUSTMENT)
	{
		ADCvalue = ADC;
	}
	else if (copyofADCconfig->adjustment == LEFT_ADJUSTMENT)
	{
		ADCvalue = ADC >> 6;
	}

	return ADCvalue;
}

/*****************************************************************
 *   @param [in]  ADC_Config_t pointer to configuration instant
 * 								in ADC_Configurations array
 * 	 @param [in]  Vref   verf in mili volt
 *   @brief This function used to Read ADC
 *   @retval u16 Digital Converting melli Vold
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
u16 ADC_u16ReadADCInMV(ADC_Config_t *copyofADCconfig, u16 Vref)
{
	u16 ADCvalue = 0, value_ms = 0;

	/* polling*/
	while ((ADCSRA & (1 << 4)) == 0)
		;
	if (copyofADCconfig->adjustment == RIGHT_ADJUSTMENT)
	{
		ADCvalue = ADC;
	}
	else if (copyofADCconfig->adjustment == LEFT_ADJUSTMENT)
	{
		ADCvalue = ADC >> 8;
	}

	value_ms = (Vref * ADCvalue) / 1024;

	return value_ms;
}

u16 readingsArr[8] = {0};
void ADC_voidReadAllNoBlock_ISR()
{

	led_viToggle(LED_RED);
	static u8 channelIndex = 0;
	if (channelIndex <= 7)
	{
		readingsArr[channelIndex] = ADC_u16ReadADC(&ADC_configurations[channelIndex]);
		channelIndex++;

		ADC_voidInit(&ADC_configurations[channelIndex]);
		// start conversion
		SET_BIT(ADCSRA, 6);
	}
	else
	{
		channelIndex = 0;
	}
}
/*****************************************************************
 *   @param [out] array of u16 elements of channels readings
 *   @brief This function used to Read all 8  ADC channels
 *   @retval void
 *   @Precondition This function is not need init nor start conversion
 * 					nor enable interrupt just call it
 *****************************************************************/
void ADC_voidReadAllNoBlock(u16 *copyofreadingsArr)
{
	// init channel 0
	ADC_voidInit(&ADC_configurations[0]);

	copyofreadingsArr = readingsArr;

	// set callback function
	GP_ADC_Callback = ADC_voidReadAllNoBlock_ISR;
	// Enable ADC
	SET_BIT(ADCSRA, 7);
	// Enable ADC interrupt
	SET_BIT(ADCSRA, 3);

	// start conversion
	SET_BIT(ADCSRA, 6);
}

/*****************************************************************
 *   @param [out] array of u16 elements of channels readings
 *   @brief This function used to Read all 8  ADC channels with polling
 *   @retval void
 *   @Precondition This function is not need init nor start conversion
 * 					nor enable interrupt just call it
 *****************************************************************/
void ADC_voidReadAllBlocking(u16 *copyofreadingsArr)
{
	u8 channelIndex = 0;
	while (channelIndex <= 7)
	{
		// init channel 0
		ADC_voidInit(&ADC_configurations[channelIndex]);
		// Enable ADC
		SET_BIT(ADCSRA, 7);
		// start conversion
		SET_BIT(ADCSRA, 6);

		/* polling*/
		while ((ADCSRA & (1 << 4)) == 0)
			;

		copyofreadingsArr[channelIndex] = ADC_u16ReadADC(&ADC_configurations[channelIndex]);
		channelIndex++;
	}
}

/* vector of ADC interrupt */
void __vector_16(void) __attribute__((signal, used));
void __vector_16(void)
{
	if (GP_ADC_Callback != NULL)
	{
		GP_ADC_Callback();
	}
}

/***********************************************************************************************/
/************************************* END OF PROGRAM ******************************************/
/***********************************************************************************************/