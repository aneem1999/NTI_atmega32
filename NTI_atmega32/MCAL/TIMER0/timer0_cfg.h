/*
 * timer0_cfg.h
 *
 * Created: 2/26/2023 11:28:54 AM
 *  Author: ncm
 */

#ifndef TIMER0_CFG_H_
#define TIMER0_CFG_H_

/*----------------------------------------------------
            Configurations Select Macros
-----------------------------------------------------*/

#define SYS_CLK 16000000U // 8 MHZ

/*  Select Timer 0 Mode from @ref TIM0_MOD
        TIM0_MOD_NORMAL
        TIM0_MOD_PWM_PHASE_CORRECT
        TIM0_MOD_CTC
        TIM0_MOD_PWM_FAST
*/
#define TIM0_MOD TIM0_MOD_NORMAL

/*  Select Timer 0 Pre-scaler from @ref TIM0_CS
        TIM0_CS_STOPPED
        TIM0_CS_PRESCALER_1
        TIM0_CS_PRESCALER_8
        TIM0_CS_PRESCALER_64
        TIM0_CS_PRESCALER_256
        TIM0_CS_PRESCALER_1024
        TIM0_CS_EXTERNAL_F_EDGE
        TIM0_CS_EXTERNAL_R_EDGE
 */
#define TIM0_CLOCK_SELECT TIM0_CS_PRESCALER_8

/* Detect prescaler value*/
#if TIM0_CLOCK_SELECT == TIM0_CS_EXTERNAL_F_EDGE
#define TIM0_PRESCALER_VALUE 0
#elif TIM0_CLOCK_SELECT == TIM0_CS_EXTERNAL_R_EDGE
#define TIM0_PRESCALER_VALUE 0
#elif TIM0_CLOCK_SELECT == TIM0_CS_PRESCALER_1
#define TIM0_PRESCALER_VALUE 1
#elif TIM0_CLOCK_SELECT == TIM0_CS_PRESCALER_8
#define TIM0_PRESCALER_VALUE 8
#elif TIM0_CLOCK_SELECT == TIM0_CS_PRESCALER_64
#define TIM0_PRESCALER_VALUE 64
#elif TIM0_CLOCK_SELECT == TIM0_CS_PRESCALER_256
#define TIM0_PRESCALER_VALUE 256
#elif TIM0_CLOCK_SELECT == TIM0_CS_PRESCALER_1024
#define TIM0_PRESCALER_VALUE 1024
#endif

/* Prescaler value */
#define TIM0_PRESCALER TIM0_PRESCALER_VALUE

#endif /* TIMER0_CFG_H_ */