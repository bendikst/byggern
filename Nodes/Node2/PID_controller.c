/*
* PID_controller.c
*
* Created: 08.11.2017 16:30:48
*  Author: alexjoha
*/
#define F_CPU 16000000L
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MOTOR_driver.h"
#include "PID_controller.h"
#include "macaroni.h"
#include "CAN_driver.h"

//GAINS:
double K_p = 1;
double K_i = 0.03;
double K_d = 0.02;
double dt = 0.033;

int16_t position = 0;
int16_t error = 0;
int16_t prev_error = 0;
int16_t integral = 0;
int16_t derivative = 0;


int16_t u = 0;

void PID_init()
{
	position = 0;
	error = 0;
	prev_error = 0;
	integral = 0;
	derivative = 0;
	
	cli();
	
	//Using normal mode
	set_bit(TCCR3B, CS31);

	//Enable timer interrupt
	set_bit(TIMSK3, TOIE3); //Kan også enable overflow/Interrupt B?
		
	sei();
	
	_delay_ms(200);
	
}



void PID_regulator()
{
	uint8_t ref = CAN_get_curr().data[2];
	
	if (ref < 10){
		ref = 10;
	}
	else if (ref > 245){
		ref = 245;
	}
	
	position = MOTOR_get_position(); 
	error = ref - position;
	integral += error;
	
	if(error<7 && error > -7){
		integral = 0;
	}
	
	derivative = (error-prev_error);
	u = K_p*error + K_i*integral + K_d*derivative;

	prev_error = error;
	MOTOR_move(u);
	
}


ISR(TIMER3_OVF_vect)
{
	PID_regulator();
}
