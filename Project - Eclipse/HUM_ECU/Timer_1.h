/*
 * Timer_1.h
 *
 *      Author: Ahemd Mostafa
 */

#ifndef TIMER_1_H_
#define TIMER_1_H_
#include "std_types.h"

typedef enum
{
	 No_clock ,  F_1 , _8 ,_64 ,_256, _1024,
	 ex_falling , ex_rising

}Timer1_Prescaler;

typedef enum
{
	NORMAL_MODE , COMPARE_MODE = 8
}Timer1_Mode;


typedef struct {
 uint16 initial_value;
 uint16 compare_value;
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_deInit(void);
void Timer1_init(const Timer1_ConfigType * );
void Timer1_setCallBack(void(* )(void));


#endif /* TIMER_1_H_ */
