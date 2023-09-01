/*
 * TIMERS_interface.h
 *
 *  Created on: Aug 15, 2023
 *      Author: First
 */

#ifndef MCAL_TIMERS_TIMERS_INTERFACE_H_
#define MCAL_TIMERS_TIMERS_INTERFACE_H_



typedef enum{

	TIMERS_TIM0_NORMAL_MODE,
	TIMERS_TIM0_PH_CORR_PWM_MODE,
	TIMERS_TIM0_CTC_MODE,
	TIMERS_TIM0_FAST_PWM_MODE,
}TIMERS_timer0_mode_t;


typedef enum{

	TIMERS_TIM0_CLK_STOP,
	TIMERS_TIM0_CLK_NO_SCALLING,
	TIMERS_TIM0_CLK_8,
	TIMERS_TIM0_CLK_64,
	TIMERS_TIM0_CLK_256,
	TIMERS_TIM0_CLK_1024,
	TIMERS_TIM0_CLK_EXT_FAILLING,
	TIMERS_TIM0_CLK_EXT_RISING

}TIMERS_timer0_clk_t;


typedef enum{

	TIMERS_TIM0_NORMAL_NO_OC0 	= 0,
	TIMERS_TIM0_NORMAL_TOG_OC0 	= 1,
	TIMERS_TIM0_NORMAL_CLR_OC0 	= 2,
	TIMERS_TIM0_NORMAL_SET_OC0 	= 3,

	TIMERS_TIM0_CTC_NO_OC0 		= 0,
	TIMERS_TIM0_CTC_TOG_OC0 	= 1,
	TIMERS_TIM0_CTC_CLR_OC0 	= 2,
	TIMERS_TIM0_CTC_SET_OC0 	= 3,

	TIMERS_TIM0_FAST_PWM_NO_OC0 		= 0,
	TIMERS_TIM0_FAST_PWM_N_INV_OC0 		= 2,	/*N_INV stands for non inverting*/
	TIMERS_TIM0_FAST_PWM_INV_OC0 		= 3,

	TIMERS_TIM0_PH_PWM_NO_OC0 			= 0,
	TIMERS_TIM0_PH_PWM_UP_CLR_OC0 		= 2,
	TIMERS_TIM0_PH_PWM_DOWN_CLR_OC0 	= 3,


}TIMERS_timer0_com_t;		/*com stands for compare output mode*/

typedef struct{

	TIMERS_timer0_mode_t work_mode;
	TIMERS_timer0_clk_t clk_src;
	TIMERS_timer0_com_t OC0_compare_out_mode;

}TIMERS_timer0_prop_t;



typedef enum{

	TIMERS_TIM0_OVERFLOW_INTERRUPT,
	TIMERS_TIM0_OUT_COMP_INTERRUPT,

}TIMERS_timer0_Interrupt_t;

/*sequence to use functions
 * 1. choose the mode from TIMERS_voidT0ChooseMode
 * 2. choosing the clk makes the timers begin
 * 3. if you want to stop it voidT0Stop
 * 4. if you want to enable interrupt from voidT0InterruptEnable
 * 5. // //  //   //   disable     //     voidT0InteruptDisable
 *
 *
 * */


void TIMERS_voidT0ChooseMode (TIMERS_timer0_prop_t * ptr_timer0_prop);
void TIMERS_voidT0ChooseClk(TIMERS_timer0_prop_t * ptr_timer0_prop);
void TIMERS_voidT0Stop(void);
void TIMERS_voidT0InterruptEnable(TIMERS_timer0_Interrupt_t Interrupt_type);
void TIMERS_voidT0InterruptDisable(TIMERS_timer0_Interrupt_t Interrupt_type);
void TIMERS_voidT0SetTime_ms (TIMERS_timer0_prop_t * ptr_timer0_prop, f32 Copy_f32Time_ms  );
void TIMERS_voidT0SetPreLoad(TIMERS_timer0_prop_t * ptr_timer0_prop,f32 Copy_f32TimerFreq ,f32 Copy_f32Time_ms);


/*
void TIMERS_T1Init(void);
void TIMERS_T1SetComMatchValA(u16 Value);
void TIMERS_T1SetICR1Val(u16 Value);
*/


#endif /* MCAL_TIMERS_TIMERS_INTERFACE_H_ */
