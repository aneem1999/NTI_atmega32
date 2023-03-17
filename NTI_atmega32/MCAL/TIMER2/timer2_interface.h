/***************************************************************
     Author             :    Ahmed Naeem
     Date 				:    26 feb 2023
     Version 			:    1.0V
     Description 		:    timer0 interface
****************************************************************/

#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

#include "timer2_cfg.h"

/***************************************************************
 *  Timer0 Configurations  define
 ****************************************************************/

/* Timer 0 bits */
#define TIMER2_BITS_NUM 8
/* Number of ticks to reach Overflow*/
#define TIMER2_MAX_TICKS 256

/********************** Mode **********************/

/*
        --------------------------------------------------------
        WGM01   WGM01	Mode                OCR0		TOV0
        --------------------------------------------------------
        0		0		Normal		        Immediate	 MAX
        0		1		PWM, Phase Correct  TOP			 BOTTOM
        1		0		CTC                 Immediate	 MAX
        1		1		Fast PWM            BOTTOM		 MAX
        --------------------------------------------------------
*/

/* @ref TIM2_MOD */
#define TIM2_MOD_NORMAL 0
#define TIM2_MOD_PWM_PHASE_CORRECT 1
#define TIM2_MOD_CTC 2
#define TIM2_MOD_PWM_FAST 3

/********************** Clock select **********************/

/* @ref TIM2_CS*/
#define TIM2_CS_STOPPED 0
#define TIM2_CS_PRESCALER_1 1
#define TIM2_CS_PRESCALER_8 2
#define TIM2_CS_PRESCALER_32 3

#define TIM2_CS_PRESCALER_64 4
#define TIM2_CS_PRESCALER_128 5

#define TIM2_CS_PRESCALER_256 6
#define TIM2_CS_PRESCALER_1024 7

/******************* CTC Mode Configurations *******************/

/* @ref  TIMER2_OC2_Mod */
/*
            COM01 COM00
             0	  0			Normal port operation, OC2 disconnected.
             0    1			Toggle OC2 on compare match
             1    0			Clear OC2 on compare match
             1    1			Set OC2 on compare match
*/
typedef enum
{
    TIMER2_OC2_DISCONNECTED,
    TIMER2_OC2_TOGGLE,
    TIMER2_OC2_CLR,
    TIMER2_OC2_SET,
} OC2_MOd_t;

/* Detect prescaler value*/

#if TIM2_CLOCK_SELECT == TIM2_CS_PRESCALER_1
#define TIM2_PRESCALER_VALUE 1
#elif TIM2_CLOCK_SELECT == TIM2_CS_PRESCALER_8
#define TIM2_PRESCALER_VALUE 8
#elif TIM2_CLOCK_SELECT == TIM2_CS_PRESCALER_64
#define TIM2_PRESCALER_VALUE 64
#elif TIM2_CLOCK_SELECT == TIM2_CS_PRESCALER_256
#define TIM2_PRESCALER_VALUE 256
#elif TIM2_CLOCK_SELECT == TIM2_CS_PRESCALER_1024
#define TIM2_PRESCALER_VALUE 1024
#endif

#define F_CPU 16000000U
#define T2_TICK_TIME ((TIM2_PRESCALER_VALUE * 1000000U) / F_CPU)

/***************************************************************
 *  Timer0 APIs
 ****************************************************************/

/*****************************************************************
 *   @param T2_MODE_t
 *   @brief This function used to initialize timer0 with mode
 *   @retval void
 *****************************************************************/
void T2_voidInit();
void T2_voidEnableInteruptOV();
void T2_voidEnableInterruptOC();

void T2_voidStart();

void T2_voidStop();

void T2_voidSetTimerReg(u8 timValue);

void T2_voidSetOutputCompareReg(u8 value);
u8 T2_u8ReadTimer();
void T2_voidSetCallbackOC(pf copyofCB);
void T2_voidSetCallbackOV(pf copyofCB);

u32 T2_u32CalculatePreloadandOvf(u64 period, u8 *T2preload);

void T2_voidSetOC2Mode(OC2_MOd_t MODE);

#endif /* TIMER2_INTERFACE_H_ */