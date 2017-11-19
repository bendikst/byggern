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

void ADC_init(void)
{
    //Interrupt on falling edge PE0:
	clear_bit(EMCUCR, ISC2);
    // Clearing interruptflag:
	set_bit(GIFR, INTF2);
	//Enabler interrupt on PE0:
	set_bit(GICR, INT2);
	
}

uint8_t adc_read(channel_type channel)
{
	volatile char *adresse = ext_adc;
	adresse[0] = channel;
	while(!(intflag));
	intflag = false;
	return adresse[0];
}


ISR(INT2_vect)
{
	intflag = true;
}
