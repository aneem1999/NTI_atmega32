/*
 * IncFile1.h
 *
 * Created: 3/16/2023 8:29:47 AM
 *  Author: ncm
 */

#ifndef SW_ICU_H_
#define SW_ICU_H_

/*******************************************************************
 * Includes
 ******************************************************************/
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/TIMER2/timer2_interface.h"
#include "../LIB/std_types.h"

void SW_ICU_voidInit(EXTI_num_t EXTI_num);
u16 SW_ICU_u16ReadTon_us();

u16 SW_ICU_u16ReadToff_us();
void SW_ICU_voidStop();
#endif /* INCFILE1_H_ */