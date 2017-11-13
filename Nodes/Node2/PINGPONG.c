/*
 * PINGPONG.c
 *
 * Created: 13.11.2017 16:17:22
 *  Author: bendikss
 */ 
#define F_CPU 16000000L
#include "PINGPONG_game.h"
#include "PWM_driver.h"
#include "IR_driver.h"
#include "MOTOR_driver.h"
#include "PID_controller.h"
#include "SOLENOID_driver.h"
#include <util/delay.h>
#include <avr/interrupt.h>

static game* current_game;

void PINGPONG_init(){
	//PWM_init();
	//IR_init();
	//SOLENOID_init();
	sei();
	//MOTOR_init();
	PID_init();
	
	//Game_struct:
	current_game->score = 0;
	current_game->lose = false;
		
}

void PINGPONG_play(){
	uint8_t counter;
	int testvar;
	current_game->lose = false;
	
	while (!current_game->lose)
	{

		counter++;
		testvar = IR_read();
		printf("IR: %d \n", testvar);
		if (counter == 5){   //digital low pass filter
			if(testvar/5 < 15 && !current_game->lose){
			//score++;
			current_game->lose = true;
			
			//printf("IR: %d \n", testvar);
		
			}
		testvar = 0;
		counter = 0;
		}
		
		PWM_joystick_control(CAN_get_curr().data[0]);
		if (CAN_get_curr().data[3]) {
			SOLENOID_shoot();
		}
	}
	
}



//bool PINGPONG_lose(){ //kopiert fra main, endre på denne?
	//Kjøres egt i while løkke
	//testvar += IR_read();
	//_delay_ms(50);
	//bool goal;
	//uint8_t counter;
	//counter++;
	//if (counter == 5){   //digital low pass filter
		//if(testvar/5 < 15 && !goal){
			////score++;
			////goal = true;
			////printf("the score is: %d\n", score);
		//}else if (testvar/5 > 20){
			//goal = false;
	//}
	//goal = false;
	//counter = 0;
//}
