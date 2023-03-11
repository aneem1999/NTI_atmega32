/*
 * timer1.c
 *
 * Created: 3/9/2023 2:54:17 PM
 *  Author: ncm
 */ 


/***************************************************************
 *  TIMER1 APIs
 ****************************************************************/

/*****************************************************************
 *   @param T1_MODE_t
 *   @brief This function used to initialize TIMER1 with mode
 *   @retval void
 *****************************************************************/
void T1_voidInit(u8 modemask);
{
	
}
void T1_voidEnableInteruptOV();
void T1_voidEnableInterruptOC();

void T1_voidStart()
{
	
}

void T1_voidStop();

void T1_voidSetTimerReg(u8 timValue);

void T1_voidSetOutputCompareReg(u8 value);
u8 T1_u8ReadTimer();
void T1_voidSetCallbackOC(pf copyofCB);
void T1_voidSetCallbackOV(pf copyofCB);

u32 T1_u32CalculatePreloadandOvf(u64 period, u8 *T1preload);

void T1_voidSetOC0Mode(OC0_MOd_t MODE);
