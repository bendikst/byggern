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
#include "JOYSTICK_driver.h"
#include "SLIDER_driver.h"
#include "ADC.h"
#include "OLED_driver.h"
#include "MENU_system.h"
#include "SPI_driver.h"
#include "MCP2515_setup.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

int main(void)
{
	cli();
	UART_init(9600);
	XMEM_init();
	ADC_init();
	sei();
	JOYSTICK_init();
	OLED_init();
	MENU_init();
	SPI_MasterInit();
	//MCP2515_init();
	
	
	_delay_ms(100);
	
	
	
	
    while(1)
    {
		
		SPI_transceive(0);
		

		//MENU_main();
		//OLED_draw();
		//_delay_ms(100);
		
    }
}
