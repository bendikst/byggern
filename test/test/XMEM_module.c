/*
 * XMEM_module.c
 *
 * Created: 06.09.2017 14:15:03
 *  Author: bendikss
 */ 
#include "XMEM_module.h"
#include "macaroni.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//Flytt denne inn i SRAM istedet?

void XMEM_init(void){
	cli();
	//DDRE |= (1 << PE1); //Trenger vi denne? spør?
	//MCUCR = (1 << SRE);
	set_bit(MCUCR, SRE);
	//SFIOR = (1 << XMM2);
	set_bit(SFIOR, XMM2);
	
	//Enabler interrupt på PD2:

	clear_bit(GICR, INT0);
	//Interrupt on falling edge PE0
	//clear_bit(EMCUCR, ISC2);
	// INT0 intflag is cleared by writing 1 to INTF2
	set_bit(GIFR, INTF0);
	//Enabler interrupt on PE0:
	set_bit(GICR, INT0);
}

