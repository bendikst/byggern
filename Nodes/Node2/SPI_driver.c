/*
 * SPI_driver.c
 *
 * Created: 04.10.2017 11:57:56
 *  Author: aleksra
 */ 

#include "SPI_driver.h"
#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit(void)
{
	/* Set MOSI, SCK and !SS output, all others input */
	DDRB |= (1<<PB2)|(1<<PB1)|(1<<PB0)|(1<<PB7); //the arduino shield defines PB7 as SS
	//DDRB &= ~(1<<PB3); // set miso to input
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
