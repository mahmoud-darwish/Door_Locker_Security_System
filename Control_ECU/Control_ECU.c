/*
 * Control_ECU.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Administrator
 */
#include "Headers/std_types.h"
#include "Headers/common_macros.h"
#include <util/delay.h>
#include "avr/io.h"
#include "Headers/uart2.h"
#include "Headers/buzzer.h"
#include "Headers/external_eeprom.h"
#include "Headers/timer1.h"
#include "Headers/DC_Motor.h"
#define MC2_READY 0x10
#define BUZZER_ON (char) 0
#define VERIFY (char) 1
#define AUTH (char) 2
#define MOTOR (char) 3
unsigned char Main_pass[6];
unsigned char EEPROM_pass[6];
unsigned char Recived_pass[6];
unsigned char seconds = 0;
/*UART_ConfigType UART_config;*/
Timer1_ConfigType Timer_config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
char strcmpp(const unsigned char *pass1 , const unsigned char *pass2);
void order(char task);
void timer_increment(void);


int main(){
	/*UART_config.baud_rate = 9600;
	UART_config.bit_data = BIT_8;
	UART_config.parity = EVEN;
	UART_config.stop_bit=ONE;
	UART_init(&UART_config);*/
	Timer_config.mode = COMPARE;
	Timer_config.prescaler = F_CPU_1024;
	Timer_config.compare_value = 7812;
	Timer_config.initial_value = 0;

	EEPROM_init();
	Buzzer_init() ;
	//Buzzer_on();
	DcMotor_Init();
	UART_init(9600);
	UART_recieveByte();
	UART_receiveString(Main_pass);
	EEPROM_writeString(0x0311,Main_pass);
	EEPROM_readString(0x0311,EEPROM_pass,5);
	if (strcmpp(EEPROM_pass,Main_pass)){
		//Buzzer_on();
	}
	while(1){
		char task = UART_recieveByte();
		switch (task)
			    {
			        case BUZZER_ON:
			        	Buzzer_on();
			            break;
			        case VERIFY:
			        	UART_receiveString(Main_pass);
			        	EEPROM_writeString(0x0311,Main_pass);
			        	EEPROM_readString(0x0311,EEPROM_pass,5);
			        	/*you can check if it recieved all chars of pass*/
			            break;
			        case AUTH:
			        	UART_receiveString(Recived_pass);
			        	if (strcmpp(EEPROM_pass,Recived_pass)){
			        		UART_sendByte(1);
			        	}
			        	else{
			        		UART_sendByte(0);
			        	}
			            break;
			        case MOTOR:
			        	Timer1_init(&Timer_config);
			        	Timer1_setCallBack(timer_increment);
			        	DcMotor_Rotate(CW, 100);
			        	while(seconds<15){}
			        	DcMotor_Rotate(STOP, 0);
			        	seconds=0;
			        	DcMotor_Rotate(A_CW, 100);
			        	while(seconds<15){}
			        	DcMotor_Rotate(STOP, 0);
			        	Timer1_deInit();

			        	break;
			        default:
			            break;
			    }

	}
	return 0;
}
char strcmpp(const unsigned  char *pass1 , const unsigned char *pass2){

	while(*pass1 != '\0'){
		if (*pass1 != *pass2){
			return 0;
		}
		pass1++;
		pass2++;
	}
	return 1;
}

void timer_increment(void){
	seconds++;
}
void order(char task){
	switch (task)
	    {
	        case BUZZER_ON:
	        	Buzzer_on();
	            break;
	        case VERIFY:
	        	UART_receiveString(Main_pass);
	        	EEPROM_writeString(0x0311,Main_pass);
	        	EEPROM_readString(0x0311,EEPROM_pass,5);
	        	/*you can check if it recieved all chars of pass*/
	            break;
	        case AUTH:
	        	UART_receiveString(Recived_pass);
	        	if (strcmpp(EEPROM_pass,Recived_pass)){
	        		UART_sendByte(1);
	        	}
	        	else{
	        		UART_sendByte(0);
	        	}
	            break;
	        default:
	            break;
	    }
}

