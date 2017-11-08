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
	
	//Set top value
	ICR1 = 40000; //The compiler handles writing to the 16-bit registers
	OCR1A = 3000;
	
	//Enable timer interrupt
	//set_bit(TIMSK1, OCIE1A); //Kan også enable overflow/Interrupt B?
	//Clearing interrupt flags 
	TIFR1 = 0;
	
	//Set PB5 as output
	set_bit(DDRB, PB5);
}

void PWM_set_duty_cycle(int cycles){
	if(cycles<=4200 && cycles>=1800){	
		OCR1A = cycles;
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
	
	clear_bit(TIFR1, OCF1A);
}