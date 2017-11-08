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
#include "IR_driver.h"
//#include "TWI_Master.h"
#include "MOTOR_driver.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void)
{
	
	cli();
	int score = 0;
	
	UART_init(9600);
	//CAN_init();
	//PWM_init();
	//IR_init();
	sei();
	MOTOR_init();
	
	_delay_ms(100);
	
	int testvar = 0;
	printf("node2\n");
	
	
	bool goal = false;
	int counter = 0;
    while(1)
    {
		
		_delay_ms(1000);
		MOTOR_move(40);
		//_delay_ms(1000);
		//PWM_joystick_control(CAN_get_curr().data[0]);
		//printf("tranceived from CAN: %d\n", CAN_get_curr().data[1]);
		
		//_delay_ms(1000);
		//MOTOR_move(40);
		//_delay_ms(1000);
		
		//testvar += IR_read();
		//int irvalue = IR_read(); 
		//printf("IR_value: %d\n", irvalue);
		//_delay_ms(500);
		//counter++;
		//if (counter == 5){   //digital low pass filter
			//if(testvar/5 < 15 && !goal){
				//score++;
				//goal = true;
				//printf("the score is: %d\n", score);
				//printf("IR_value: %d\n", testvar/5);
			//}else if (testvar/5 > 20){
				//goal = false;
			//}
			////printf("IR_value: %d\n", testvar/5);
			////goal = false;
			//counter = 0;
			//testvar = 0;
		//}
    }
}

ISR(BADISR_vect){
	printf(("BADISR"));
	while(1);
}