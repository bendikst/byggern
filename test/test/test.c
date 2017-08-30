/*
 * test.c
 *
 * Created: 30.08.2017 12:31:52
 *  Author: bendikss
 */ 
#define F_OSC 4915200UL
#define F_CPU F_OSC
//#define BAUD 9600
//#define MYUBRR (F_OSC)/(16*BAUD)-1

#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include <stdio.h>


int main(void)
{
	
	UART_init(9600);
	unsigned char test = 0;
	UART_transmit('y');
	printf("Hello\n");
    while(1)
    {
		//UART_transmit('y');
		//UART_transmit('s');
		_delay_ms(500);
		
		printf(" its me\n");
		printf("Hellooo\n");
		//UART_transmit('\n');
		test = UART_receive();
		
		
		
		if(test){
			UART_transmit(test);
			//UART_transmit('\n');
			UART_transmit('y');
		}
		test = 0;
		printf("test\n");
    }
}

//ISR();
//printf("r:\n %c", UDR0);