/*
 * PINGPONG.c
 *
 * Created: 13.11.2017 16:17:22
 *  Author: bendikss
 */ 
#define F_CPU 16000000L
#include "PINGPONG_game.h"
#include "PWM_driver.h"
#include "IR_driver.h"
#include "MOTOR_driver.h"
#include "PID_controller.h"
#include "SOLENOID_driver.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//static game* current_game;

void PINGPONG_init(){
	//PWM_init();
	//IR_init();
	//SOLENOID_init();
	
	sei();
	MOTOR_init();
	PID_init();
		
}

void PINGPONG_play(){
	CAN_transmit_game(false);
	_delay_us(50);
	uint8_t counter = 0;
	int testvar = 0;
	bool lose = false; //TESTVERDI, TA VEKK??	
	while (!lose)
	{
		counter++;
		testvar += IR_read();
		_delay_us(50);
		if (counter == 5){   //digital low pass filter
			if(testvar/5 < 9 && !lose){
		
			lose = true;

			
		}
		testvar = 0;
		counter = 0;
		}
		printf("tranceived from CAN: %d\n", CAN_get_curr().data[2]);
		PWM_joystick_control(CAN_get_curr().data[0]);
				if (CAN_get_curr().data[3]) {
			SOLENOID_shoot();
		}
	}
	CAN_transmit_game(lose);
}

