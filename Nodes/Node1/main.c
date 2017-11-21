/*
 * test.c
 *
 * Created: 30.08.2017 12:31:52
 *  Author: bendikss
 */ 
#define F_OSC 4915200UL
#define F_CPU F_OSC

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
#include "CAN_driver.h"
#include "MCP2515_setup.h"
#include "GAME_driver.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


typedef enum{
	MENU = 0,
	TEST = 1
	} state_enum;

int main(void)
{
	cli();
	UART_init(9600);
	XMEM_init();
	ADC_init();
	CAN_init();
	sei();
	JOYSTICK_init();
	OLED_init();
	MENU_init();
	SPI_MasterInit();
	
	_delay_ms(100);
	/*-------- ONLY USE WHEN YOU WANT TO RESET THE SCORES!!---------*/
	//GAME_EEPROM_reset_highscores();
	/*--------------------------------------------------------------*/
	
	printf("Node 1\n");
	
	state_enum state = MENU;
	
	//state = TEST;
    while(1)
    {		
		switch (state)
		{
		case MENU:
			MENU_main();
			OLED_draw();
			_delay_ms(90);
			break;
		case TEST:
			/*DIFFERENT TEST FUNCTIONS FOR DEBUGGING PURPOSES.*/
			CAN_gamecontrols_transmit();
			printf("Transmitting\n");
			_delay_ms(200);
			break;
		default:
			state = MENU;
			
		}
	}
}

ISR(BADISR_vect)
{
    printf("BADISR\n");
}
