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
	
	
	//Encoder pins:
	set_bit(DDRH, PH6); //RST pin output
	set_bit(DDRH, PH3);
	set_bit(DDRH, PH5);
	MOTOR_reset_encoder();
	
	//Data bits:
	clear_bit(DDRK, PK0);
	clear_bit(DDRK, PK1);
	clear_bit(DDRK, PK2);
	clear_bit(DDRK, PK3);
	clear_bit(DDRK, PK4);
	clear_bit(DDRK, PK5);
	clear_bit(DDRK, PK6);
	clear_bit(DDRK, PK7);
	
	MOTOR_calibrate();
}


void MOTOR_reset_encoder() {
	clear_bit(PORTH, PH6);
	_delay_us(200);
	set_bit(PORTH, PH6);
}


int16_t MOTOR_read_encoder(void){
	//!OE low to enable output of encoder
	clear_bit(PORTH, PH5);
	
	//Set SEL low to select high byte 
	clear_bit(PORTH,PH3);
	_delay_us(100);
	
	//Read MSB:
	uint8_t hi = PINK;
	
	//Set SEL low to select high byte
	set_bit(PORTH, PH3);	
	_delay_us(100);
	
	//Read LSB
	uint8_t lo = PINK;
	
	//MOTOR_reset_encoder();
	
	
	set_bit(PORTH, PH5);
	return (int16_t) ((hi<<8) | lo);
}


uint8_t MOTOR_get_position(void){
	int enc_min = -350;
	int enc_max = 9090;
	uint8_t result;
	uint16_t read_value = (-1)*MOTOR_read_encoder(); //Read_encoder gives negative
	result = (double)((read_value - enc_min)/(double)(enc_max))*255;
	return result;
}


void MOTOR_set_direction(uint8_t val){
	if (val < 128)
	{
		clear_bit(PORTH, PH1);
		
	} else if (val >= 128)
	{
		set_bit(PORTH, PH1);
	}
	
}


void MOTOR_move(int16_t val){//Kunne også tatt inn både direction og value??
	uint8_t address = 0x5e;
	uint8_t command = 0b00; //Do we need this?? page 11 in the datasheet for DAC
	uint8_t data = 0b0;
	
	//Set direction
	if (val < 0)
	{
		clear_bit(PORTH, PH1);
		data = (-1)*val;
	} else if (val >= 0)
	{
		set_bit(PORTH, PH1);
		data = (val);
	}	
	
	//Set SPEEEED/POWEEEEER
	uint8_t message[3];
	message[0] = address;
	message[1] = command;
	message[2] = data;
	_delay_us(20);
	
	TWI_Start_Transceiver_With_Data(message, 3);
}

void MOTOR_move_PID(uint8_t val, uint8_t direction){
	uint8_t address = 0x5e;
	uint8_t command = 0b00; 
	uint8_t data = 0b0;
	
	//Set direction
	if (val < 128)
	{
		clear_bit(PORTH, PH1);
		data = (-1)*val*2;
		
	} else if (val >= 128)
	{
		set_bit(PORTH, PH1);
		data = (val-128)*2;
	}
	
	//Set SPEEEED/POWEEEEER
	uint8_t message[3];
	message[0] = address;
	message[1] = command;
	message[2] = data;
	_delay_us(20);
	
	TWI_Start_Transceiver_With_Data(message, 3);
}





void MOTOR_calibrate(){
	MOTOR_move(-100); //SETTER VENSTRE
	int16_t rotation = MOTOR_read_encoder();
	int16_t prev_rotation = rotation + 300;
	while (rotation != prev_rotation){
		prev_rotation = rotation;
		_delay_ms(20);
		rotation = MOTOR_read_encoder();
	}
	MOTOR_move(0);
	_delay_ms(180); //To make the encoder reset properly to ~0
	MOTOR_reset_encoder();
}