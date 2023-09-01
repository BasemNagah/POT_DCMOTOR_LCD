/*
 * TIMERS_program.c
 *
 *  Created on: Aug 15, 2023
 *      Author: First
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMERS_private.h"
#include "TIMERS_config.h"
#include "TIMERS_interface.h"



void TIMERS_voidT0ChooseMode (TIMERS_timer0_prop_t * ptr_timer0_prop){
	switch(ptr_timer0_prop->work_mode){

	case TIMERS_TIM0_NORMAL_MODE:

		CLR_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM00_BIT);
		CLR_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM01_BIT);
		break;

	case TIMERS_TIM0_PH_CORR_PWM_MODE:

		CLR_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM01_BIT);
		SET_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM00_BIT);

		break;
	case TIMERS_TIM0_CTC_MODE:

		CLR_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM00_BIT);
		SET_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM01_BIT);
		break;

	case TIMERS_TIM0_FAST_PWM_MODE:
		SET_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM00_BIT);
		SET_BIT(TIMERS_TIM0_TCCR0_REG,TIMERS_TIM0_WGM01_BIT);

		break;

	default:
		break;
	}

	/*Compare output mode*/
	TIMERS_TIM0_TCCR0_REG &= 0b11001111;
	TIMERS_TIM0_TCCR0_REG |= ((ptr_timer0_prop->OC0_compare_out_mode) << 4) ;

}
void TIMERS_voidT0ChooseClk(TIMERS_timer0_prop_t * ptr_timer0_prop){

	TIMERS_TIM0_TCCR0_REG &= 0xF8;
	TIMERS_TIM0_TCCR0_REG |= ptr_timer0_prop->clk_src;
}
void TIMERS_voidT0InterruptEnable(TIMERS_timer0_Interrupt_t Interrupt_type){

	switch(Interrupt_type){
	case TIMERS_TIM0_OVERFLOW_INTERRUPT:
		SET_BIT(TIMERS_TIM0_TIMSK_REG, 0);
		break;
	case TIMERS_TIM0_OUT_COMP_INTERRUPT:
		SET_BIT(TIMERS_TIM0_TIMSK_REG, 1);
		break;
	}
}
void TIMERS_voidT0InterruptDisable(TIMERS_timer0_Interrupt_t Interrupt_type){

	switch(Interrupt_type){
	case TIMERS_TIM0_OVERFLOW_INTERRUPT:
		CLR_BIT(TIMERS_TIM0_TIMSK_REG, 0);
		break;
	case TIMERS_TIM0_OUT_COMP_INTERRUPT:
		CLR_BIT(TIMERS_TIM0_TIMSK_REG, 1);
		break;
	}
}
void TIMERS_voidT0Stop(void){

	TIMERS_TIM0_TCCR0_REG &= 0xF8;
}




void TIMERS_voidT0SetTime_ms (TIMERS_timer0_prop_t * ptr_timer0_prop, f32 Copy_f32Time_ms ){

	f32 Local_f32Timer0Freq = 0;

	switch(ptr_timer0_prop->clk_src){
	case TIMERS_TIM0_CLK_8:
		Local_f32Timer0Freq =	F_CPU / 8;
		/*Set the preload and with this function stop and start the timer*/
		TIMERS_voidT0SetPreLoad(ptr_timer0_prop,Local_f32Timer0Freq ,Copy_f32Time_ms);
		break;
	case TIMERS_TIM0_CLK_64:
		Local_f32Timer0Freq =	F_CPU / 64;
		/*Set the preload and with this function stop and start the timer*/
		TIMERS_voidT0SetPreLoad(ptr_timer0_prop,Local_f32Timer0Freq ,Copy_f32Time_ms);

		break;
	case TIMERS_TIM0_CLK_256:
		Local_f32Timer0Freq =	F_CPU / 256;
		/*Set the preload and with this function stop and start the timer*/
		TIMERS_voidT0SetPreLoad(ptr_timer0_prop,Local_f32Timer0Freq ,Copy_f32Time_ms);

		break;
	case TIMERS_TIM0_CLK_1024:
		Local_f32Timer0Freq =	F_CPU / 1024;
		/*Set the preload and with this function stop and start the timer*/
		TIMERS_voidT0SetPreLoad(ptr_timer0_prop,Local_f32Timer0Freq ,Copy_f32Time_ms);

		break;

	default :
		break;
	}


}

void TIMERS_voidT0SetPreLoad(TIMERS_timer0_prop_t * ptr_timer0_prop,f32 Copy_f32TimerFreq ,f32 Copy_f32Time_ms){

	u8 Local_u8Ticks = 0;

	/*Stop the timer First*/
	TIMERS_TIM0_TCCR0_REG &= 0xF8;


	/*Get the max time*/
	f32 Local_f32MaxTime = (1/Copy_f32TimerFreq) * 256;  /*max time in sec*/

	/*Compare the required time with the max*/
	/*if the required is less than it*/
	if((Copy_f32Time_ms/1000) <= Local_f32MaxTime ){

		/*put the preload value*/


		Local_u8Ticks =  (Copy_f32Time_ms*Copy_f32TimerFreq)/1000;


		TIMERS_TIM0_TCNT0_REG =  256  -  Local_u8Ticks;
		//TIMERS_TIM0_OCR0_REG = Local_u8Ticks;

		/*Starting the timer*/
		TIMERS_TIM0_TCCR0_REG |= (ptr_timer0_prop->clk_src);


		/* Awaiting for the flag to be set*/
		while((TIMERS_TIM0_TIFR_REG & 0x01) == 0){
			asm("NOP");
		}
		//while((TIMERS_TIM0_TIFR_REG & 0x02) == 0);

		/*Clearing the flag*/
		TIMERS_TIM0_TIFR_REG |= 0x01;
		//TIMERS_TIM0_TIFR_REG |= 0x02;

		/*Stop timer working*/
		TIMERS_TIM0_TCCR0_REG &= 0xf8;
	}
	else{
		u64 Local_u64NumOfCounts = ((Copy_f32Time_ms / 1000)  * Copy_f32TimerFreq)/256;

		TIMERS_TIM0_TCCR0_REG |= (ptr_timer0_prop->clk_src);

		while(Local_u64NumOfCounts > 0){

			/*Clearing the flag*/
			TIMERS_TIM0_TIFR_REG |= 0x01;

			/*Set the value of preload*/
			TIMERS_TIM0_TCNT0_REG = 0;

			/* Awaiting for the flag to be set*/
			while((TIMERS_TIM0_TIFR_REG & 0x01) == 0){
				asm("NOP");
			}
			Local_u64NumOfCounts--;

		}
		/*Stop timer working*/
		TIMERS_TIM0_TCCR0_REG &= 0xf8;

	}

}





//void TIMERS_T1Init(void){
//
//	/*NORMAL*/
//	CLR_BIT(TIMERS_TIM1_TCCR1A_REG,0);		/*0,1,3,4*/
//	CLR_BIT(TIMERS_TIM1_TCCR1A_REG,1);
//	CLR_BIT(TIMERS_TIM1_TCCR1B_REG,3);
//	CLR_BIT(TIMERS_TIM1_TCCR1B_REG,4);
////	/*Non inverstoing mode*/
////
////	SET_BIT(TIMERS_TIM1_TCCR1A_REG, 7);
////	CLR_BIT(TIMERS_TIM1_TCCR1A_REG, 6);
//
//
//
//
//	/*prescalar / 8*/
//	CLR_BIT(TIMERS_TIM1_TCCR1B_REG,2);
//	SET_BIT(TIMERS_TIM1_TCCR1B_REG,1);
//	SET_BIT(TIMERS_TIM1_TCCR1B_REG,0);
//
//	/*Enable OV interrupt */
//	SET_BIT(TIMERS_TIM0_TIMSK_REG,2);
//
//
////	/* ICR1 value*/
////	TIMERS_T1SetICR1Val(20000);
//}
//
//
//
//
//
//
//void TIMERS_T1SetComMatchValA(u16 Value){
//	TIMERS_TIM1_OCR1A_REG = Value;
//}
//
//void TIMERS_T1SetICR1Val(u16 Value){
//
//	TIMERS_TIM1_ICR1_REG = Value;
//}
//











void TIMERS_voidT0Init	(void)
{

	/*		CTC		*/
	SET_BIT(TIMERS_TIM0_TCCR0_REG , 3 );
	CLR_BIT(TIMERS_TIM0_TCCR0_REG , 6 );

	/* OC0 Disconnected */
	CLR_BIT(TIMERS_TIM0_TCCR0_REG , 5);
	CLR_BIT(TIMERS_TIM0_TCCR0_REG , 4);

	/* Enable PIE for CTC*/
	SET_BIT(TIMERS_TIM0_TIMSK_REG , 1 );

	TIMERS_TIM0_OCR0_REG = 200;

	/*Start Timer , with prescaler 8 */
	CLR_BIT(TIMERS_TIM0_TCCR0_REG , 2 );
	SET_BIT(TIMERS_TIM0_TCCR0_REG , 1 );
	CLR_BIT(TIMERS_TIM0_TCCR0_REG , 0 );

}
void TIMERS_voidSetPreloadValT0	(u8 Copy_u8PreloadValue )
{
	TIMERS_TIM0_TCNT0_REG = Copy_u8PreloadValue;
}



