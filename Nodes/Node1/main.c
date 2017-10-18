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
#include "CAN_driver.h"
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
	CAN_init();
	sei();
	JOYSTICK_init();
	OLED_init();
	MENU_init();
	SPI_MasterInit();
	//MCP2515_init();
	
	
	_delay_ms(100);
	
	char* data = "yolo";
	CAN_message test_can;
	test_can.id = 6;
	test_can.length = 4;
	for (uint8_t i = 0; i < test_can.length; i++){
		test_can.data[i] = data[i];
	}
	char* data2 = "snek2";
	CAN_message test_can2;
	test_can2.id = 2;
	test_can2.length = 5;
	for (uint8_t i = 0; i < test_can2.length; i++){
		test_can2.data[i] = data2[i];
	}
	
	//CAN_transmit(&test_can);
	
	_delay_ms(50);
	//CAN_print();
	
	//_delay_ms(1000);
	
	//CAN_transmit(&test_can2);
	
	_delay_ms(50);
	//CAN_print();
	
	
	//CAN_transmit(&test_can2);
	//CAN_print(&test_can2);
	CAN_message msg;
    while(1)
    {
		msg = CAN_joystick_transmit();
		
		CAN_transmit(&msg);
		printf("Node 1 pos: %d\n",msg.data[0]);
		//printf("Node 1 ID: %d\n", msg.id);
		_delay_ms(100);
		//MENU_main();
		//OLED_draw();
		//_delay_ms(100);
		
    }
}
