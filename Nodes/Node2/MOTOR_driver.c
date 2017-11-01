/*
 * MOTOR_driver.c
 *
 * Created: 01.11.2017 12:09:57
 *  Author: bendikss
 */ 

#define F_CPU 16000000L

#include "MOTOR_driver.h"
#include "TWI_Master.h"
#include "macaroni.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void MOTOR_init(){
	TWI_Master_Initialise();

	//Enable motor
	set_bit(DDRH, PH4);
	set_bit(PORTH, PH4);
	
	//Direction pin output
	set_bit(DDRH, PH1);
	
	//Encoder pins
	
	
}


void MOTOR_move(uint8_t val){//Kunne også tatt inn både direction og value??
	uint8_t address = 0x50;
	uint8_t command = 0b0; //Do we need this?? page 11 in the datasheet for DAC
	uint8_t data = 0b0;
	//printf("val: %d\n", val);
	//Set direction
	if (val < 50)
	{
		set_bit(PORTH, PH1);
		data = (-1)*(val - 50)/10;
	} else if (val >= 50)
	{
		clear_bit(PORTH, PH1);
		data = (val-50)/10;
	}	
	
	//Set SPEEEED/POWEEEEER
	
	uint8_t message[3];
	message[0] = address;
	message[1] = command;
	message[2] = data;
	_delay_us(100);
	//printf("TWI state: %d\n", TWI_Get_State_Info());
	
	TWI_Start_Transceiver_With_Data(message, 3);
	_delay_us(100);
	

	
	
}
