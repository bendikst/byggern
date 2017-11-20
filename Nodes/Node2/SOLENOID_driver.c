/*
 * SOLENOID_driver.c
 *
 * Created: 13.11.2017 12:42:22
 *  Author: bendikss
 */ 
#define F_CPU 16000000L
#include "SOLENOID_driver.h"
#include <util/delay.h>
#include <avr/io.h>
#include "macaroni.h"


void SOLENOID_init()
{
	set_bit(DDRB, PB4);
	set_bit(PORTB, PB4);
}

void SOLENOID_shoot()
{
	clear_bit(PORTB, PB4);
	_delay_ms(70);
	set_bit(PORTB, PB4);
	
	
}
