/*
 * motor.h
 *
 *  Created on: Oct 16, 2023
 *      Author: Ahmed Mostafa
 */

#ifndef MOTOR_H_
#define MOTOR_H_


#define PORT_MOTORS PORTA_ID
#define PIN0_MOTOR PIN1_ID
#define PIN1_MOTOR PIN2_ID



/***************************
 * Enum Declaration                                   *
 ***************************/

typedef enum{
	stop,ANTI_CLOCKWISE,CLOCKWISE
}DcMotor_State;

/***************************
 *  Functions Prototypes                                   *
 ***************************/
/*
 * DC_motor driver initializetion
 */
void DcMotor_Init(void);
/*
 state and speed function
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif
