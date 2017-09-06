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
#include "XMEM_module.h"
#include "SRAM.h"
#include <stdio.h>


int main(void)
{
	
	UART_init(9600);
	XMEM_init();
	DDRA = 0xFF;
	PORTE |= (1 << PE1);
	PORTA = 0xFF;
	PORTA |= (1 << PA1);
	
	SRAM_test();	
	//const unsigned char test[500];
	//UART_transmit('y');
	//printf("Hello\n");
    while(1)
    {
		
		
		//UART_transmit('\n');
		//scanf("%s",test);
		
		
		//if(test){
			//UART_transmit(test);
			//UART_transmit('\n');
			//UART_transmit('y');
			//printf("%s\n", test);
		//}
		//test = 0;
		//printf("\n");
    }
}

//ISR();
//printf("r:\n %c", UDR0);