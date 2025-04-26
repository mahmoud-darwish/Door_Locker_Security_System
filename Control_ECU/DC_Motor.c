/*
 * DC_Motor.c
 *
 *  Created on: Jun 26, 2024
 *      Author: Administrator
 */

#include"Headers/DC_Motor.h"
#include"Headers/common_macros.h"
#include"Headers/PWM.h"
#include <avr/io.h>
void DcMotor_Init(void){
	SET_BIT(DDRB ,PB0);
	SET_BIT(DDRB ,PB1);
	SET_BIT(DDRB ,PB3);
	CLEAR_BIT(PORTB,PB0);
	CLEAR_BIT(PORTB,PB1);
	SET_BIT(PORTB,PB3);
}
void DcMotor_Rotate(DcMotor_State state,char speed){
	if (state == STOP){
		PORTB &= ~((1 << PB0) | (1 << PB1));
	}
	else if (state == CW ){
		PORTB &= ~(1 << PB0);
		PORTB |= (1 << PB1);
	}
	else if (state == A_CW ){
		PORTB &= ~(1 << PB1);
		PORTB |= (1 << PB0);
	}
	//PORTB |= (PORTB & 0xF8)|(state&0x03);
	//char percentage = ((float)speed/ 100) * 255;
	//Timer0_PWM_Init(percentage);
}



