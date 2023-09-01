/*
 * main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{

	u32 ReadValue 		;
	u32 Real_Value		;
	u32 New_Value = 0	;
	ADC_Conf_t  LDR_VALUE = { ADC_AVCC ,ADC_FCPU_64};
	ADC_voidInit(&LDR_VALUE);
	ADC_voidChooseTrigSrc(ADC_FREE_RUNNING_MODE);

	CLCD_voidInit();

	u8 Hamok4a_right[] = { 0x0E , 0x0E , 0x0E , 0x04 , 0x0C , 0x14 , 0x0A , 0x12 } ;
	u8 Hamok4a_left[]  = { 0x0E , 0x0E , 0x0E , 0x04 , 0x06 , 0x05 , 0x0A , 0x09 } ;

	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN4 , DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN5 , DIO_OUTPUT);

	while(1)
	{
		ReadValue = ADC_u16SynchReadChannel(ADC_SINGLE_ENDED_0);
		Real_Value = (ReadValue*5000)/1024 ;
		Real_Value = Real_Value/150 ;
		if(Real_Value != New_Value)
		{
			if (Real_Value > New_Value)
			{
				DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_HIGH );
				DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_LOW );
				CLCD_voidSendCommand(0x01);
				CLCD_voidSetPositoion(1,4);
				CLCD_voidSendString((u8*)"MOTOR RIGHT" , 12);
				CLCD_voidCreateAndDispNew( 1 , Hamok4a_right , 2 , (Real_Value/2));
			}
			else
			{
				DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_LOW );
				DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_HIGH );
				CLCD_voidSendCommand(0x01);
				CLCD_voidSetPositoion(1,4);
				CLCD_voidSendString((u8*)"MOTOR LEFT" , 10);
				CLCD_voidCreateAndDispNew( 0 , Hamok4a_left , 2 , (Real_Value/2));
			}
			New_Value = Real_Value ;
		}

	}
	return 0 ;
}

