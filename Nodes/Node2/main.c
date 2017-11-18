/*
 * Node2.c
 *
 * Created: 11.10.2017 16:57:57
 *  Author: alexjoha
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include "SPI_driver.h"
#include "CAN_driver.h"
#include "macaroni.h"
#include "UART_driver.h"
#include "PWM_driver.h"
#include "IR_driver.h"
#include "MOTOR_driver.h"
#include "PID_controller.h"
#include "SOLENOID_driver.h"
#include "PINGPONG_game.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
	PLAY = 0,
	IDLE = 1,
	TEST = 2
}state_machine;


int main(void)
{
	
	cli();
	//int score = 0;
	
	UART_init(9600);
	CAN_init();
	PWM_init();
	IR_init();
	SOLENOID_init();
	sei();
	MOTOR_init();
	//PID_init();
	
	PINGPONG_difficulty(1);
	_delay_ms(100);
	
	//int testvar = 0;
	printf("node2\n");
	//uint8_t ref;
	uint8_t testvar;

	state_machine state = PLAY;
	uint8_t difficulty = 0;
	//state = TEST;
	//MOTOR_calibrate();
	//bool goal = false;
	//int counter = 0;
	
    while(1)
    {		
		//SOLENOID_shoot();
		//
		//_delay_ms(1000);
		//printf("Main\n");
		
		switch (state)
		{
			case PLAY:
				PINGPONG_init();
				PINGPONG_play();
				state = IDLE;
				break;
			case IDLE:
				clear_bit(TIMSK3, TOIE3);
				if (CAN_get_curr().id == 5) {
					state = PLAY;
				}
				if (CAN_get_curr().id == 8){
					PINGPONG_difficulty(CAN_get_curr().data[0]);
					printf("diff\n");
				}
				break;
				
			case TEST:
				//MOTOR_calibrate();
				_delay_ms(500);
				/*Different test functions. Comment in which you want to use.*/
				//CAN_transmit_game(false);
				//printf("TEST MODE:\n");
				////testvar = IR_read();
				////printf("IR: %d\n", testvar);
				////_delay_ms(100);
//
				//PWM_joystick_control(CAN_get_curr().data[0]);
				//if (CAN_get_curr().data[3]) {
					//SOLENOID_shoot();
				//}
				////_delay_ms(100);
				//printf("tranceived from CAN: %d\n", CAN_get_curr().data[2]);
		//
				////_delay_ms(1000);
				//MOTOR_move(50);
		//
				////printf("Position: %d\n", MOTOR_get_position());
		//
				////printf("Encoder values: %d\n", MOTOR_read_encoder());
				////_delay_ms(1000);
				//uint16_t encoder = MOTOR_read_encoder();
		//
				////ref = CAN_get_curr().data[2];
				////_delay_ms(50);
				//printf("Encoder output: %d\n", encoder);
				//state = TEST;
				//break;
				//PWM_set_duty_cycle_difficulty(3000);
			default:
				state = IDLE;
		}
		//PWM_joystick_control(CAN_get_curr().data[0]);
		//if (CAN_get_curr().data[3]) {
		//SOLENOID_shoot();
		//}
		//uint16_t encoder = MOTOR_read_encoder();
		////_delay_ms(100);
		//printf("tranceived from CAN: %d\n", CAN_get_curr().data[0]);
		//_delay_ms(50);
		//printf("Encoder output: %d\n", encoder);
		//
		
    }
}

ISR(BADISR_vect){
	printf(("BADISR"));
	while(1);
}