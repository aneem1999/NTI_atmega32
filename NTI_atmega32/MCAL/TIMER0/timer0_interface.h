/***************************************************************
     Author             :    Ahmed Naeem
     Date 				:    26 feb 2023
     Version 			:    1.0V
     Description 		:    timer0 interface
****************************************************************/

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#include "../LIB/std_types.h"

/***************************************************************
 *  Timer0 Configurations  define
 ****************************************************************/

/* Timer 0 bits */
#define TIMER0_BITS_NUM 8
/* Number of ticks to reach Overflow*/
#define TIMER0_MAX_TICKS 256

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

/* @ref TIM0_MOD */
#define TIM0_MOD_NORMAL 0
#define TIM0_MOD_PWM_PHASE_CORRECT 1
#define TIM0_MOD_CTC 2
#define TIM0_MOD_PWM_FAST 3

/********************** Clock select **********************/

/* @ref TIM0_CS*/
#define TIM0_CS_STOPPED 0
#define TIM0_CS_PRESCALER_1 1
#define TIM0_CS_PRESCALER_8 2
#define TIM0_CS_PRESCALER_64 3
#define TIM0_CS_PRESCALER_256 4
#define TIM0_CS_PRESCALER_1024 5

#define TIM0_CS_EXTERNAL_F_EDGE 6
#define TIM0_CS_EXTERNAL_R_EDGE 7

/******************* CTC Mode Configurations *******************/

/* @ref  TIMER0_OC0_Mod */
/*
            COM01 COM00
             0	  0			Normal port operation, OC0 disconnected.
             0    1			Toggle OC0 on compare match
             1    0			Clear OC0 on compare match
             1    1			Set OC0 on compare match
*/
typedef enum
{
    TIMER0_OC0_DISCONNECTED,
    TIMER0_OC0_TOGGLE,
    TIMER0_OC0_CLR,
    TIMER0_OC0_SET,
} OC0_MOd_t;

#define F_CPU 16000000U
#define TickTime ((TIM0_PRESCALER * 1000000.0) / F_CPU)

/***************************************************************
 *  Timer0 APIs
 ****************************************************************/

/*****************************************************************
 *   @param T0_MODE_t
 *   @brief This function used to initialize timer0 with mode
 *   @retval void
 *****************************************************************/
void T0_voidInit();
void T0_voidEnableInteruptOV();
void T0_voidEnableInterruptOC();

void T0_voidStart();

void T0_voidStop();

void T0_voidSetTimerReg(u8 timValue);

void T0_voidSetOutputCompareReg(u8 value);
u8 T0_u8ReadTimer();
void T0_voidSetCallbackOC(pf copyofCB);
void T0_voidSetCallbackOV(pf copyofCB);

void T0_voidWait_us(u64 period);
void T0_voidSetOC0Mode(OC0_MOd_t MODE);

#endif /* TIMER0_INTERFACE_H_ */