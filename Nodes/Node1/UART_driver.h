/*
 * UART_driver.h
 *
 * Module for making UART communication between the atmega162 and computer.
 *
 * Created: 30.08.2017 14:50:13
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal */ 
#ifndef UART_driver_h
#define UART_driver_h
#include <avr/io.h>

/* Sets the correct baud rate for communicating. We are using baud rate of 9600.
 Also enables the receiver and transmitter.*/
void UART_init(unsigned int baud);

/*Functions for receiving and transmitting data. Waits for an empty transmit buffer
 before transmitting or receiving.*/
void UART_transmit(unsigned char data);
unsigned char UART_receive(void);
	
#endif
