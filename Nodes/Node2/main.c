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
	UART_init(9600);
	CAN_init();
	PWM_init();
	IR_init();
	SOLENOID_init();
	sei();

	
	PINGPONG_difficulty(1);
	_delay_ms(100);
	
	printf("node2\n");
	
	state_machine state = IDLE;
	
    while(1)
    {
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
				}
				break;
			case TEST:
                /*Different test functions. Comment in which you want to use.*/
                printf("TEST MODE:\n");
				//MOTOR_calibrate();
				_delay_ms(500);
				//CAN_transmit_game(false);
				////testvar = IR_read();
				////printf("IR: %d\n", testvar);
				////_delay_ms(100);
				//PWM_joystick_control(CAN_get_curr().data[0]);
				//if (CAN_get_curr().data[3])
                //{
					//SOLENOID_shoot();
				//}
				////_delay_ms(100);
				//printf("tranceived from CAN: %d\n", CAN_get_curr().data[2]);
                ////printf("Position: %d\n", MOTOR_get_position());
				////printf("Encoder values: %d\n", MOTOR_read_encoder());
                ////_delay_ms(1000);
				state = TEST;
                break;
			default:
				state = IDLE;
		}
		
    }
}

ISR(BADISR_vect){
	printf(("BADISR"));
	while(1);
}
