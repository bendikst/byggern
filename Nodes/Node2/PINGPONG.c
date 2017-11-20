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


void PINGPONG_init()
{
	sei();
	CAN_transmit_game(false);
	MOTOR_init();
	PID_init();
}


void PINGPONG_play()
{
	_delay_us(50);
	uint8_t counter = 0;
	int testvar = 0;
	bool lose = false;
	
	while (!lose)
	{
		counter++;
		testvar += IR_read();
		_delay_us(50);
		if (counter == 5) //digital low pass filter
		{   
			if((testvar/5 < 9) && !lose)
			{
				lose = true;
			}
		testvar = 0;
		counter = 0;
		}
		PWM_joystick_control(CAN_get_curr().data[0]);
		if (CAN_get_curr().data[3]) 
		{
			SOLENOID_shoot();
		}
	}
	CAN_transmit_game(lose);
}


void PINGPONG_difficulty(uint8_t difficulty)
{
	switch(difficulty){
		case 1:
		PWM_set_duty_cycle_difficulty(4000);
		break;
		case 2:
		PWM_set_duty_cycle_difficulty(3000);
		break;
		case 3:
		PWM_set_duty_cycle_difficulty(1800);
		break;
	}
}
