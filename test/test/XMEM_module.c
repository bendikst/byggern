/*
 * XMEM_module.c
 *
 * Created: 06.09.2017 14:15:03
 *  Author: bendikss
 */ 
#include "XMEM_module.h"
#include <avr/io.h>
//Flytt denne inn i SRAM istedet?

void XMEM_init(void){
	
	//DDRE |= (1 << PE1); Trenger vi denne? sp�r?
	MCUCR = (1 << SRE);
}
