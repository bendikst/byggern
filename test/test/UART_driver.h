/*
 * UART_driver.h
 *
 * Created: 30.08.2017 14:50:13
 *  Author: bendikss
 */ 
#ifndef UART_driver_h
#define UART_driver_h
#include <avr/io.h>


void UART_init(unsigned int baud);
void UART_transmit(unsigned char data);
unsigned char UART_receive(void);
	
#endif
