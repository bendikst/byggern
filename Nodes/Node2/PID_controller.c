/*
* PID_controller.c
*
* Created: 08.11.2017 16:30:48
*  Author: alexjoha
*/
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MOTOR_driver.h"
#include "PID_controller.h"
#include "macaroni.h"

//GAINS:
double K_p = 1;
double K_i = 4;
double K_d = 0.1;
double dt = 0.016; //timestep?? regn over

double position = 0; //integral av encoder???
double error = 0;
double prev_error = 0;
double integral = 0;
double derivative = 0;

uint8_t u = 0;
uint16_t ref = 0;
uint16_t encoder_output;


void PID_init(){
	//cli();
	//
	////enable timer overflow interrupt for timer 2
	//set_bit(TIMSK2, TOIE2);
	//
	////Start timer2 with prescaler of 1024
	//
	//set_bit(TCCR2B, CS20);
	//set_bit(TCCR2B, CS21);
	//set_bit(TCCR2B, CS22);
	//
	//
	//sei();
	MOTOR_calibrate();
	_delay_ms(200);
	
}


void PID_update_reference(uint16_t pos){
	ref = pos;
}


//ISR(TIMER2_OVF_vect){
	//printf("Inteerr\n");
	//encoder_output = MOTOR_read_encoder(); //Integrating speed to find position
	//printf("Output: %d\n", encoder_output);
	//position += encoder_output*dt;
	//printf("Postition: %d\n", position);
	//error = ref - position;
	//integral += error*dt;
	//
	//derivative = -(error-prev_error)/dt; //Do we need negative??
	//
	//u = K_p*error + K_i*integral + K_d*derivative;
	//
	//prev_error = error;
	//
	//MOTOR_move(u);
	//
	////set_bit(TIFR2, TOV2); Trengs ikke, gjøres av hardware
//}