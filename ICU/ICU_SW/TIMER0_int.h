

#ifndef _TIMER0_INT_H_
#define _TIMER0_INT_H_




void TIMER0_void_intialization(void);

void TIMER0_void_setOCR0(u8 value_cpy);

void TIMER0_void_setTCNT0(u8 value_cpy);

void TIMER0_void_setTCCR0(u8 value_cpy);

void TIMER0_void_overflowInterruptEnable(void);

void TIMER0_void_comapreMatchInterruptEnable(void);

void TIMER0_void_overflowInterruptDisable(void);

void TIMER0_void_comapreMatchInterruptDisable(void);

void TIMER0_void_clearOverflowInterruptFlag(void);

u8 TIMER0_void_getOverflowInterruptFlag(void);

void TIMER0_void_clearCompareMatchInterruptFlag(void);

u8 TIMER0_void_getCompareMatchInterruptFlag(void);

void TIMER0_COMPAREMATCH_void_setCallBack(pf address_cpy);

void TIMER0_OVERFLOW_void_setCallBack(pf address_cpy);

u8 TIMER0_void_getTCNT0(void);

#endif
