/***************************************************************
     Author             :    Ahmed Naeem
     Date 				:    23 feb 2023
     Version 			:    1.0V
     Description 		:   public Accessing mechanism prototype
                            and Sense Mode Definition [int.h]
****************************************************************/

#ifndef _ADC_INT_H
#define _ADC_INT_H

#include "../LIB/std_types.h"
#include "ADC_cfg.h"

/*****************************************************************
 *   @param [in]- pointer of (ADC_Config_t) ADC configuration struct
 *   @brief  in This function used to initialize ADC
 *   @retval void
 *****************************************************************/
void ADC_voidInit(ADC_Config_t *copyofADCconfig);

/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Enable ADC
 *
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidEnable();

/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Enable ADC Interrput
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidInterrputEnable();

/*****************************************************************
 *   @param [in] void
 *   @brief function used to Disable ADC
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidDisable();

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
void ADC_voidSetCallbackFun(pf addresscpy);
/*****************************************************************
 *   @param [in]
 *   @brief This function used to communicate with the
 *				function in App Layer(The Callback function)
 *   @retval u16  of ADC digital value
 *
 *
 *****************************************************************/
u16 ADC_u16ReadADC(ADC_Config_t *copyofADCconfig);
/*****************************************************************
 *   @param [in] void
 *   @brief This function used to Start converting of ADC
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidStartConversion();

/*****************************************************************
 *   @param [in] ADC_Config_t *copyofADCconfig
 *   @brief This function used to Set latch Interrupt happens.
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
void ADC_voidAutoTrigger(ADC_Config_t *copyofADCconfig);

/*****************************************************************
 *   @param [in] Pointer struct of ADC configuration
 *   @brief This function used to read ADC with polling mechanism
 *   @retval void
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
u16 ADC_u8ReadADCwithBlock(ADC_Config_t *copyofADCconfig);

/*****************************************************************
 *   @param [in]  ADC_Config_t pointer to configuration instant
 * 								in ADC_Configurations array
 * 	 @param [in]  Vref   verf in mili volt
 *   @brief This function used to Read ADC
 *   @retval u16 Digital Converting melli Vold
 *   @Precondition this function must be used after ADC initialized
 *****************************************************************/
u16 ADC_u16ReadADCInMV(ADC_Config_t *copyofADCconfig, u16 Vref);

/*****************************************************************
 *   @param [out] array of u16 elements of channels readings
 *   @brief This function used to Read all 8  ADC channels
 *   @retval void
 *   @Precondition This function is not need init nor start conversion
 * 					nor enable interrupt just call it
 *****************************************************************/
void ADC_voidReadAllNoBlock(u16 *copyofreadingsArr);

void ADC_voidReadAllBlocking(u16 *copyofreadingsArr);

#endif