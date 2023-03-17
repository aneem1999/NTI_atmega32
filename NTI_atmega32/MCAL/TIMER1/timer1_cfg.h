/*
 * timer0_cfg.h
 *
 * Created: 2/26/2023 11:28:54 AM
 *  Author: ncm
 */

#ifndef TIMER1_CFG_H_
#define TIMER1_CFG_H_

/*----------------------------------------------------
            Configurations Select Macros
-----------------------------------------------------*/

#define SYS_CLK 16000000U // 8 MHZ

/*  Select Timer  Mode from @ref data sheet Table 47.


0     Normal
1     PWM, Phase Correct, 8-bit
2     PWM, Phase Correct, 9-bit
3     PWM, Phase Correct, 10-bit
4     CTC											OCR1A
6     Fast PWM, 9-bit
5     Fast PWM, 8-bit
7     Fast PWM, 10-bit
8     PWM, Phase and Frequency Correct				ICR1 BOTTOM BOTTOM
9     PWM, Phase and Frequency Correct				OCR1A BOTTOM BOTTOM
10    PWM, Phase Correct                            ICR1 TOP BOTTOM
11    PWM, Phase Correct                            OCR1A TOP BOTTOM
12    CTC											ICR1 Immediate MAX
13    Reserved
14    Fast PWM										ICR1
15    Fast PWM										OCR1A

*/
#define TIM1_MOD TIM1_MOD_PWM_PHASE_CORRECT

/*  Select Timer 1 Pre-scaler from @ref TIM1_CS
        TIM1_CS_STOPPED
        TIM1_CS_PRESCALER_1
        TIM1_CS_PRESCALER_8
        TIM1_CS_PRESCALER_64
        TIM1_CS_PRESCALER_256
        TIM1_CS_PRESCALER_1024
        TIM1_CS_EXTERNAL_F_EDGE
        TIM1_CS_EXTERNAL_R_EDGE
 */
#define TIM1_CLOCK_SELECT TIM1_CS_PRESCALER_8

/* Prescaler value */

#endif /* TIMER1_CFG_H_ */