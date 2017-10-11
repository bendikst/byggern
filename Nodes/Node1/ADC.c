/*
 * ADC.c
 *
 * Created: 13.09.2017 13:40:24
 *  Author: bendikss
 */ 


#include <avr/io.h>
#include <stdbool.h>
#include "macaroni.h"
#include "ADC.h"
#include <avr/interrupt.h>

volatile bool intflag = false;

void ADC_init(void){
	cli();
	
	clear_bit(GICR, INT2);
	//Interrupt on falling edge PE0
	clear_bit(EMCUCR, ISC2);
	// INT2 intflag is cleared by writing 1 to INTF2
	set_bit(GIFR, INTF2);
	//Enabler interrupt on PE0:
	set_bit(GICR, INT2);
	
}

uint8_t adc_read(channel_type channel){
	volatile char *adresse = ext_adc;
	adresse[0] = channel;
	while(!(intflag));
	intflag = false;
	
	return adresse[0];
}

//Using local flag, later: use function for starting conversion, and one for reading in interrupt
ISR(INT2_vect){
	intflag = true;
}