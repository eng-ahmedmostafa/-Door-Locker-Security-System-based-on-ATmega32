/*
 * pwm.h
 *
 *  Created on: Oct 15, 2023
 *      Author: Ahmed Mostafa
 */

#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"/as we need uint8/
/***************************
 *Functions Prototypes                                   *
 ***************************/

/*PWM driver initializetion*/
void PWM_Timer0_Start(uint8 duty_cycle);
#endif /* PWM_H_ */
