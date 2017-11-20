/*
 * UART_driver.c
 *
 * Created: 30.08.2017 14:07:59
 *  Author: bendikss
 */ 

#define F_CPU 16000000L

#include "UART_driver.h"
#include <stdio.h>

FILE *uart;

void UART_transmit(unsigned char data){
	//Wait for empty transmit buffer
	while (!(UCSR0A & ( 1<<UDRE0)));
		
	//Puts data into buffer, sends data
	UDR0 = data;
}

unsigned char UART_receive(void){
	
	while (!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}

void UART_init(unsigned int baud){
	
	uint16_t baudrate = F_CPU/16/baud - 1;
	//Set baud rate
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) baudrate;
	
	//Enable receiver, transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	uart = fdevopen(&UART_transmit, &UART_receive);
	
}
