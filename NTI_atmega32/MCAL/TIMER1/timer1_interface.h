/***************************************************************
     Author             :    Ahmed Naeem
     Date 				:    26 feb 2023
     Version 			:    1.0V
     Description 		:    timer0 interface
****************************************************************/

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "timer1_cfg.h"

/***************************************************************
 *  Timer Configurations  define
 ****************************************************************/
#include "../LIB/std_types.h"
/* Timer 0 bits */
#define TIMER1_BITS_NUM 16
/* Number of ticks to reach Overflow*/
#define TIMER1_MAX_TICKS 65535

/********************** Mode **********************/

/* @ref TIM1_MOD */

#define TIM_NORMAL 0
#define TIM1_PWM_PHASE_CORRECT_8B 1
#define TIM1_PWM_PHASE_CORRECT_9B 2
#define TIM1_PWM_PHASE_CORRECT_10B 3
#define TIM1_PWM_FAST_8B 5
#define TIM1_PWM_FAST_9B 6
#define TIM1_PWM_FAST_10B 7
#define TIM1_PWM_PH_F_COORECT 8

/********************** Clock select **********************/

/* @ref TIM1_CS*/
#define TIM1_CS_STOPPED 0
#define TIM1_CS_PRESCALER_1 1
#define TIM1_CS_PRESCALER_8 2
#define TIM1_CS_PRESCALER_64 3
#define TIM1_CS_PRESCALER_256 4
#define TIM1_CS_PRESCALER_1024 5

#define TIM1_CS_EXTERNAL_F_EDGE 6
#define TIM1_CS_EXTERNAL_R_EDGE 7

/* Detect prescaler value*/
#if TIM1_CLOCK_SELECT == 0
#define TIM1_PRESCALER_VALUE 0
#endif
#if TIM1_CLOCK_SELECT == TIM1_CS_EXTERNAL_R_EDGE
#define TIM1_PRESCALER_VALUE 0
#elif TIM1_CLOCK_SELECT == TIM1_CS_PRESCALER_1
#define TIM1_PRESCALER_VALUE 1
#elif TIM1_CLOCK_SELECT == TIM1_CS_PRESCALER_8
#define TIM1_PRESCALER_VALUE 8
#elif TIM1_CLOCK_SELECT == TIM1_CS_PRESCALER_64
#define TIM1_PRESCALER_VALUE 64
#elif TIM1_CLOCK_SELECT == TIM1_CS_PRESCALER_256
#define TIM1_PRESCALER_VALUE 256
#elif TIM1_CLOCK_SELECT == TIM1_CS_PRESCALER_1024
#define TIM1_PRESCALER_VALUE 1024
#endif

/******************* CTC Mode Configurations *******************/

/* @ref  TIMER1_OC0_Mod */
/*
            COM01 COM00
             0	  0			Normal port operation, OC0 disconnected.
             0    1			Toggle OC0 on compare match
             1    0			Clear OC0 on compare match
             1    1			Set OC0 on compare match
*/
typedef enum
{
    TIMER1_OC_DISCONNECTED,
    TIMER1_OC_TOGGLE,
    TIMER1_OC_CLR,
    TIMER1_OC_SET,
} OC_MOd_t;

#define F_CPU 16000000U
#define TickTime ((TIM1_PRESCALER * 1000000U) / F_CPU)

/***************************************************************
 *  Timer0 APIs
 ****************************************************************/

/*****************************************************************
 *   @param T0_MODE_t
 *   @brief This function used to initialize timer0 with mode
 *   @retval void
 *****************************************************************/
void T1_voidInit(u8 t1ModeMask);

void T1_voidEnable_InteruptOVF(void (*copyofFun)());
void T1_voidEnable_InterruptOCA(void (*copyofFun)());

void T1_voidEnable_InterruptOCB(void (*copyofFun)());

void T1_voidEnable_InterruptIC(void (*copyofFun)());
void T1_voidStart();
void T1_voidStop();
void T1_voidSetTimerReg(u16 timValue);
void T1_voidSet_OutputCompareAReg(u16 value);
void T1_voidSet_OutputCompareBReg(u16 value);
void T1_voidSet_InputCapturReg(u16 value);

u16 T1_u16Read_Timer();

void T1_voidSetCallbackOV(pf copyofCB);

/*
 *		 @fun			 : TIMER0_SetOutputComparePinMode
 *		 @Description	 : Set Output Compare Pin Mode according to @ref  TIMER0_OC0_MOd
 *						   The OC0 value will not be visible on the port pin unless
 *						   the data direction for the pin is set to output
 *
 */
void T1_voidSet_OC1AMode(OC_MOd_t MODE);
void T1_voidSet_OC1BMode(OC_MOd_t MODE);

#endif /* TIMER1_INTERFACE_H_ */