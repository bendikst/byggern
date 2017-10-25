/*
 * Node2.c
 *
 * Created: 11.10.2017 16:57:57
 *  Author: alexjoha
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include "SPI_driver.h"
#include "CAN_driver.h"
#include "macaroni.h"
#include "UART_driver.h"
#include "PWM_driver.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	
	cli();
		
	UART_init(9600);
	CAN_init();
	PWM_init();
	sei();
	
	_delay_ms(50);
	
	//printf("node 2 \n");
	//printf("node 2 \n");
	
	_delay_ms(100);
	
	//char* data = "Hvor er";
	//CAN_message test_can;
	//test_can.id = 6;
	//test_can.length = 7;
	//for (uint8_t i = 0; i < test_can.length; i++){
		//test_can.data[i] = data[i];
	//}
	//char* data2 = "Bendik?";
	//CAN_message test_can2;
	//test_can2.id = 2;
	//test_can2.length = 7;
	//for (uint8_t i = 0; i < test_can2.length; i++){
		//test_can2.data[i] = data2[i];
	//}
//
	//JOYSTICK_direction_t pos = 0;
	//CAN_message msg = CAN_get_curr();
		//
		//if(msg.id == 0){
			//
			//pos = msg.data[0];
			//
		//}
		////CAN_print();
		//
		//
		//
		//printf("Node2 Pos: %d\n",pos);
		//
		//_delay_ms(100);
//
	printf("node2\n");
	
	
	
    while(1)
    {
		//_delay_ms(1000);
		PWM_joystick_control(CAN_get_curr().data[0]);
		
    }
}