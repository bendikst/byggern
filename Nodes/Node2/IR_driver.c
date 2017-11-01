/*
 * IR_driver.c
 *
 * Created: 25.10.2017 15:38:16
 *  Author: bendikss
 */ 

#include "IR_driver.h"
#include "macaroni.h"
#include <avr/interrupt.h>
#include <stdbool.h>

volatile static bool IR_intflag = false;


void IR_init(){
	//Enable the ADC
	set_bit(ADCSRA, ADEN);
	//ADCL must be read first, then ADCH, remember: if 
	//ADCL is read and a conv completes before ADCH is read, data is lost. 
	//Set ADC prescaler bits to 128
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	
	//Set PF0 as input
	clear_bit(DDRF, PF0);
	//Select reference to AVCC
	set_bit(ADMUX, REFS0);
		
	//Enable interrupt
	set_bit(ADCSRA, ADIE);
	//Clear interrupt flag
	clear_bit(ADCSRA, ADIF);

}


uint8_t IR_read(){
	//Start conversion
	set_bit(ADCSRA, ADSC);
	
	while (!IR_intflag);
	IR_intflag = false;
	
	return ADC;
}


ISR(ADC_vect){
	//printf("kjørr\n");
	IR_intflag = true;
}