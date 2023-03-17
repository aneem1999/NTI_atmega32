/*
 * timer0_cfg.h
 *
 * Created: 2/26/2023 11:28:54 AM
 *  Author: ncm
 */

#ifndef TIMER2_CFG_H_
#define TIMER2_CFG_H_

/*----------------------------------------------------
            Configurations Select Macros
-----------------------------------------------------*/

#define SYS_CLK 16000000U // 8 MHZ

/*  Select Timer 0 Mode from @ref TIM2_MOD
        TIM2_MOD_NORMAL
        TIM2_MOD_PWM_PHASE_CORRECT
        TIM2_MOD_CTC
        TIM2_MOD_PWM_FAST
*/
#define TIM2_MOD TIM2_MOD_NORMAL

/*  Select Timer 0 Pre-scaler from @ref TIM2_CS
        TIM2_CS_STOPPED
        TIM2_CS_PRESCALER_1
        TIM2_CS_PRESCALER_8
        TIM2_CS_PRESCALER_8
        TIM2_CS_PRESCALER_32
        TIM2_CS_PRESCALER_64
        TIM2_CS_PRESCALER_128
        TIM2_CS_PRESCALER_256
        TIM2_CS_PRESCALER_1024

 */
#define TIM2_CLOCK_SELECT TIM2_CS_PRESCALER_256

/* Prescaler value */
#define TIM2_PRESCALER TIM2_PRESCALER_VALUE

#endif /* TIMER2_CFG_H_ */