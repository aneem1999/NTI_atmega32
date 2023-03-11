


#ifndef _TIMER0_PRIV
#define _TIMER0_PRIV

#define TIMSK	 		(*(volatile u8 * )0x59)
#define OCR0 	 		(*(volatile u8 * )0x5C)
#define TCCR0	 		(*(volatile u8 * )0x53)
#define TCNT0			(*(volatile u8 * )0x52)
#define TIFR			(*(volatile u8 * )0x58)


#define TCCR1A        (*((volatile u8 *)(0x4F)))
#define TCCR1B        (*((volatile u8 *)(0x4E)))
#define TCNT1H        (*((volatile u8 *)(0x4D)))
#define TCNT1L        (*((volatile u8 *)(0x4C)))
#define TCNT1         (*((volatile u16 *)(0x4C)))
#define OCR1AH        (*((volatile u8 *)(0x4B)))
#define OCR1AL        (*((volatile u8 *)(0x4A)))
#define OCR1A         (*((volatile u16 *)(0x4A)))

#define OCR1BH        (*((volatile u8 *)(0x49)))
#define OCR1BL        (*((volatile u8 *)(0x48)))
#define OCR1B         (*((volatile u16 *)(0x48)))

#define ICR1H         (*((volatile u8 *)(0x47)))
#define ICR1L         (*((volatile u8 *)(0x46)))

#define ICR1		  (*((volatile u16 *)(0x46)))







#define TIMER0_NORMAL 		1
#define TIMER0_CTC 			2
#define TIMER0_FAST_PWM 	3
#define TIMER0_PHASE_PWM 	4

#define TIMER0_DIV_BY_1			1
#define TIMER0_DIV_BY_8			5
#define TIMER0_DIV_BY_64		8
#define TIMER0_DIV_BY_256		10
#define TIMER0_DIV_BY_1024		15


#define TIMER0_NO_ACTION	100
#define TIMER0_TOGGLE		12
#define TIMER0_SET			20
#define TIMER0_CLEAR		25


#endif
