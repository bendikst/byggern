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

void XMEM_init(void)
{
	set_bit(MCUCR, SRE);
	set_bit(SFIOR, XMM2);
}

