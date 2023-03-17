/*
 * TD_delay.c
 *
 * Created: 3/16/2023 11:47:29 AM
 *  Author: ncm
 */

#include "../MCAL/TIMER0/timer0_interface.h"
#include "TD_delay.h"

void TD_delay_us(u64 prd)
{

	T0_voidInit();
	T0_voidStart();

	T0_voidWait_us(prd);

	T0_voidStop();
}

void TD_delay_ms(u64 prd)
{

	T0_voidInit();
	T0_voidStart();

	T0_voidWait_us(prd * 1000);

	T0_voidStop();
}