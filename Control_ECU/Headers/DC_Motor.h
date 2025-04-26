/*
 * DC_Motor.h
 *
 *  Created on: Jun 26, 2024
 *      Author: Administrator
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include"std_types.h"
typedef enum{
STOP,A_CW,CW
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, char speed);


#endif /* DC_MOTOR_H_ */
