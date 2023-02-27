/***************************************************************
	 @author             :    Ahmed Naeem
	 @date 				 :    24 Feb 2023
	 @version 			 :    1.0V
	 @brief 		     :    interface file [cfg.c]
***************************************************************/

#ifndef EXTI_H_
#define EXTI_H_

/***************************************************************
 *   Includes
 ***************************************************************/

#include "../LIB/register.h"
#include "../LIB/std_types.h"
#include "../LIB/bit_math.h"

/************************** EXTI Configurations ******************************/
typedef enum
{
	EXTI_0,
	EXTI_1,
	EXTI_2
} EXTI_num_t;

/*
	EXTI_sensitivity --> specify interrupt senstivity
	in pins ISCx0 , ISCx1 in MCUCR for INT0, INT1
	and pin ISC2 in MCUCSR for INT2 (only falling or rising edge)
 */
typedef enum
{
	LOW_LEVEL,
	TOGGLE_LEVEl,
	FALLING_EDGE,
	RISINING_EDGE,

} EXTI_sensitivity_t;

typedef struct
{
	EXTI_num_t EXTI_x; /* EXTI number */
	EXTI_sensitivity_t EXTI_sensitivity;
	void (*EXTI_callback)(); /* callback function for EXTI ISR */

} EXTI_Configs_t;

/************************************ EXTI APIs **********************************/

/* in app create EXTI_Configs_t with EXTI number , sensitivity , callback function*/
void EXTI_Init(EXTI_num_t EXTIn, EXTI_sensitivity_t sense);
void EXTI_DeInit(EXTI_num_t EXTIx);
void EXTI_voidSetCallbackFunction(EXTI_num_t EXTIn, pf copyofCBfun);
#endif /* EXTI_H_ */