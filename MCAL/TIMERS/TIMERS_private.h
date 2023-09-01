#ifndef MCAL_TIMERS_TIMERS_PRIVATE_H_
#define MCAL_TIMERS_TIMERS_PRIVATE_H_

#define TIMERS_TIM0_TCCR0_REG	*((volatile u8*)0x53)
#define TIMERS_TIM0_TCNT0_REG	*((volatile u8*)0x52)
#define TIMERS_TIM0_OCR0_REG	*((volatile u8*)0x5C)

#define TIMERS_TIM0_TIMSK_REG	*((volatile u8*)0x59)
#define TIMERS_TIM0_TIFR_REG	*((volatile u8*)0x58)


#define TIMERS_TIM1_TCCR1A_REG	*((volatile u8*)0x4F)
#define TIMERS_TIM1_TCCR1B_REG	*((volatile u8*)0x4E)


#define TIMERS_TIM1_TCNT1_REG	*((volatile u16*)0x4C)

#define TIMERS_TIM1_OCR1A_REG	*((volatile u16*)0x4A)
#define TIMERS_TIM1_OCR1B_REG	*((volatile u16*)0x48)

#define TIMERS_TIM1_ICR1_REG	*((volatile u16*)0x46)




#define TIMERS_TIM0_WGM00_BIT   6
#define TIMERS_TIM0_WGM01_BIT   3

#define TIMERS_TIM0_COM00_BIT   4
#define TIMERS_TIM0_COM01_BIT   5




#endif /* MCAL_TIMERS_TIMERS_PRIVATE_H_ */
