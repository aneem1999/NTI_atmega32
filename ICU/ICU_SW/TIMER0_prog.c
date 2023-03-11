

#include "STD_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "TIMER0_int.h"
#include "TIMER0_config.h"
#include "TIMER0_priv.h"


static pf GLOB_TIMER0_OVERFLOW_ISRLocation_ptrToFunc;
static pf GLOB_TIMER0_COMPAREMATCH_ISRLocation_ptrToFunc;

void TIMER0_void_intialization(void){
	TCCR0 = 0x05;
	TCNT0 = 0 ;

}

void TIMER0_void_setOCR0(u8 value_cpy){
	OCR0 = value_cpy;
}
void TIMER0_void_setTCNT0(u8 value_cpy){
	TCNT0 = value_cpy;
}
void TIMER0_void_setTCCR0(u8 value_cpy){
	TCCR0 = value_cpy;
}

u8 TIMER0_void_getTCNT0(void){
	return TCNT0;
}

void TIMER0_void_overflowInterruptEnable(void){
	SET_BIT(TIMSK, 0);
}

void TIMER0_void_comapreMatchInterruptEnable(void){
	SET_BIT(TIMSK, 1);
}

void TIMER0_void_overflowInterruptDisable(void){
	CLEAR_BIT(TIMSK, 0);
}

void TIMER0_void_comapreMatchInterruptDisable(void){
	CLEAR_BIT(TIMSK, 0);
}

void TIMER0_void_clearOverflowInterruptFlag(void){
	SET_BIT(TIFR, 0);
}

u8 TIMER0_void_getOverflowInterruptFlag(void){
	return (GET_BIT(TIFR, 0));
}

void TIMER0_void_clearCompareMatchInterruptFlag(void){
	SET_BIT(TIFR, 1);
}

u8 TIMER0_void_getCompareMatchInterruptFlag(void){
	return (GET_BIT(TIFR, 1));
}


void TIMER0_OVERFLOW_void_setCallBack(pf address_cpy){
	GLOB_TIMER0_OVERFLOW_ISRLocation_ptrToFunc = address_cpy;
}




void __vector_11 (void) __attribute__ ((signal, used));
void __vector_11 (void){
	GLOB_TIMER0_OVERFLOW_ISRLocation_ptrToFunc();
}





void TIMER0_COMPAREMATCH_void_setCallBack(pf address_cpy){
	GLOB_TIMER0_COMPAREMATCH_ISRLocation_ptrToFunc = address_cpy;
}


/*
void __vector_10 (void) __attribute__ ((signal, used));
void __vector_10 (void){
	GLOB_TIMER0_COMPAREMATCH_ISRLocation_ptrToFunc();
}
*/
