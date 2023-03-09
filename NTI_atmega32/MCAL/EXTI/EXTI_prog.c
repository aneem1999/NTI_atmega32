/***************************************************************
	 @author             :    Ahmed Naeem
	 @date 				 :    24 Feb 2023
	 @version 			 :    1.0V
	 @brief 		     :    EXTI implemention
***************************************************************/

#include "EXTI_int.h"

/***************************************************************
 *  Externql interrupt callback functions
 ****************************************************************/
void (*EXTI0_callback)();
void (*EXTI1_callback)();
void (*EXTI2_callback)();

/***************************************************************
 *  Function Implementation
 ****************************************************************/

void EXTI_Init(EXTI_num_t EXTIn, EXTI_sensitivity_t sense)
{
	switch (EXTIn)
	{
	case EXTI_0:
	{
		// 1-Choose interrupt sensitivity
		// clear bit0, bit1
		MCUCR &= ~(0x03);
		// put bit0 , bit1 values in EXTI_sensitivity
		MCUCR |= (sense & 0x03);

		// 2- Enable INTx
		SET_BIT(GICR, 6);
	}
	break;
	case EXTI_1:
	{
		// 1- Choose interrupt sensitivity
		//  clear bit2, bit3
		MCUCR &= ~(0x0C);
		// put bit2 , bit3 values in EXTI_sensitivity
		MCUCR |= (sense & 0x0C);

		// 2- Enable INT1
		SET_BIT(GICR, 7);
	}
	break;
	case EXTI_2:
	{
		// 1- Choose interrupt sensitivity
		//  clear bit6
		CLEAR_BIT(MCUCSR, 6);
		// put bit6 values in EXTI_sensitivity
		MCUCSR |= ((sense - 2) & 0x20);

		// 2- Enable INT2
		SET_BIT(GICR, 5);
	}
	break;
	}
}

void EXTI_voidSetCallbackFunction(EXTI_num_t EXTIn, pf copyofCBfun)
{
	switch (EXTIn)
	{
	case EXTI_0:
	{
		// 3- specify callback function
		EXTI0_callback = copyofCBfun;
	}
	break;
	case EXTI_1:
	{
		// 3- specify callback function
		EXTI1_callback = copyofCBfun;
	}
	break;
	case EXTI_2:
	{
		// 3- specify callback function
		EXTI2_callback = copyofCBfun;
	}
	break;
	}
}

void EXTI_DeInit(EXTI_num_t EXTIx)
{
	switch (EXTIx)
	{
	case EXTI_0:
	{
		// Disable INT0
		SET_BIT(GICR, 6);
	}
	break;
	case EXTI_1:
	{
		// Disable INT1
		CLEAR_BIT(GICR, 7);
	}
	break;
	case EXTI_2:
	{
		// Disable INT2
		CLEAR_BIT(GICR, 5);
	}
	break;
	}
}

void __vector_1(void) __attribute__((signal, used));
void __vector_2(void) __attribute__((signal, used));
void __vector_3(void) __attribute__((signal, used));

void __vector_1(void)
{
	EXTI0_callback();
}

void __vector_2(void)
{
	EXTI1_callback();
}

void __vector_3(void)
{
	EXTI2_callback();
}