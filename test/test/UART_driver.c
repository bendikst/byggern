/*
 * UART_driver.c
 *
 * Created: 30.08.2017 14:07:59
 *  Author: bendikss
 */ 


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
	
	uint16_t baudrate = 4915200/16/baud -1;
	//Set baud rate
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) baudrate;
	
	//Enable receiver, transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	//Set frame format: 8 data, 1 stop bit
	//UCSR0C = (1<<URSEL0)|(0<<USBS0)|(3<<UCSZ00);
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
	
	uart = fdevopen(UART_transmit, UART_receive);
	
}