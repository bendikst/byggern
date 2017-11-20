/*
 * SPI_driver.c
 *
 * Created: 04.10.2017 11:57:56
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 

#include "SPI_driver.h"
#include <avr/io.h>


void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);
    
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<MSTR)|(1<<SPR0);
	SPCR |= (1<<SPE);
}


char SPI_transceive(char cData)
{
	/* Start transmission */
	SPDR = cData;
    
	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));
    
	return SPDR;
}
