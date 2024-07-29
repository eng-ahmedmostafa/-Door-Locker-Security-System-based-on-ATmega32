/*
 * Timer_1.c
 *
 *  Created on: Oct 27, 2023
 *      Author: Yousef Mostafa
 */

#include "Timer_1.h"
#include "std_types.h"
#include "avr/io.h"
#include "avr/Interrupt.h"


static volatile void (*g_callBackPtr)(void) = NULL_PTR;




ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}



void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	if (Config_Ptr->mode == NORMAL_MODE)
	{

		TIMSK |= (1<<TOIE1);



		TCCR1A = (1<<FOC1A);


		TCCR1B = Config_Ptr->prescaler;

	}
	else
	{

		OCR1A = Config_Ptr->compare_value;

		TIMSK |= (1<<OCIE1A);

		TCCR1A = (1<<FOC1A);


		TCCR1B = Config_Ptr->prescaler | Config_Ptr->mode;
	}
}


void Timer1_deInit(void)
{
	/* stop Timer */
	TCCR1B = (TCCR1B & 0xF8)  | (No_clock);
}


void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}


