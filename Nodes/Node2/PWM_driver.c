/*
 * TIMER.c
 *
 * Created: 25.10.2017 11:30:12
 *  Author: Administrator
 */ 
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM_driver.h"
#include "macaroni.h"

void PWM_init(){
	//Set waveform generation mode to fast PWM, TOP: ICRn, update of OCRx at: BOTTOM, TOV flag set on: TOP
	//And normal port operation compare output mode
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	
	/*Setting up TIMER 4 for servo controlling difficulty*/
	TCCR4A = (1<<WGM41)|(1<<COM4A1);
	TCCR4B = (1<<WGM42)|(1<<WGM43)|(1<<CS41);
	
	//Set top values
	ICR1 = 40000;
	OCR1A = 3000;
	
	ICR4 = 40000;
	OCR4A = 3000;
	
	//Enable timer interrupt
	set_bit(TIMSK1, OCIE1A);
	set_bit(TIMSK4, OCIE4A);
	
	//Clear interrupt flags
	TIFR1 = 0;	
	//Set PB5 as output for gameservo
	set_bit(DDRB, PB5);
	set_bit(DDRH, PH3);
}

void PWM_set_duty_cycle(int cycles){
	if(cycles<=4200 && cycles>=1800){	
		OCR1A = cycles;
	}
	else{
		printf("Invalid duty cycle value\n");
	}
}


void PWM_set_duty_cycle_difficulty(int cycles){
	if(cycles<=4200 && cycles>=1800){
		OCR4A = cycles;
	}
	else{
		printf("Invalid duty cycle value\n");
	}
}



void PWM_joystick_control(uint8_t val){
	
	int PWM_value = 24*val+1800;
	
	PWM_set_duty_cycle(PWM_value);
	
	/*
	switch (dir){
		case LEFT:
			PWM_set_duty_cycle(1800);
			break;
		case RIGHT:
			PWM_set_duty_cycle(4200);
			break;
		default:
			PWM_set_duty_cycle(3000);
	}
	*/
}


ISR(TIMER1_COMPA_vect){
}

ISR(TIMER4_COMPA_vect){
}