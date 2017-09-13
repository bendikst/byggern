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
#include "macaroni.h"
#include "ADC.h"
#include <stdio.h>
#include <avr/interrupt.h>

int main(void)
{
	
	UART_init(9600);
	XMEM_init();
	ADC_init();
	sei();
	
	//SRAM_test();
	
	//unsigned char val = adc_read(X_axis);
			
	//printf("%d\n",val);
	
	
	//volatile char *ext_ram = (char *) 0x0000;
	
	//const unsigned char test[500];
	//UART_transmit('y');
	//printf("Hello\n");
    while(1)
    {
		unsigned char val = adc_read(X_axis);
		
		//printf("%d\n",val);
		printf("%d\n",val);
		_delay_ms(100);
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