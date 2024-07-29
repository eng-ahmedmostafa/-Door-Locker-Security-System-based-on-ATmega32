/*
 * motor.c
 *
 *  Created on: Oct 16, 2023
 *      Author: Ahmed Mostafa
 */

#include"gpio.h"
#include"std_types.h"
#include"motor.h"
#include"pwm.h"

/***************************
 *                      Functions Definitions                                  *
 ***************************/
void DcMotor_Init(void){
	/* setup iInput pins */
	GPIO_setupPinDirection(PORT_MOTORS,PIN0_MOTOR,PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_MOTORS,PIN1_MOTOR,PIN_OUTPUT);
	/*stop the motor when PB0 , PB1=0*/
	GPIO_writePin(PORT_MOTORS,PIN0_MOTOR,LOGIC_LOW);
	GPIO_writePin(PORT_MOTORS,PIN1_MOTOR,LOGIC_LOW);


}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start(speed);
	if(state==CLOCKWISE){
		GPIO_writePin(PORT_MOTORS,PIN0_MOTOR,LOGIC_LOW);
		GPIO_writePin(PORT_MOTORS,PIN1_MOTOR,LOGIC_HIGH);
		/*clockWise rotate when PB0=0,PB1=1*/


	}
	else if(state==ANTI_CLOCKWISE){
		GPIO_writePin(PORT_MOTORS,PIN0_MOTOR,LOGIC_HIGH);
		GPIO_writePin(PORT_MOTORS,PIN1_MOTOR,LOGIC_LOW);
		/*antiClockWise rotate when PB0=1,PB1=0*/

	}
	else{
		GPIO_writePin(PORT_MOTORS,PIN0_MOTOR,LOGIC_LOW);
		GPIO_writePin(PORT_MOTORS,PIN1_MOTOR,LOGIC_LOW);
		/*stop the motor when PB0=PB1=0*/


	}

}
