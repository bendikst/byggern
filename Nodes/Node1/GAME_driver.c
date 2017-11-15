/*
 * GAME_driver.c
 *
 * Created: 15.11.2017 10:23:25
 *  Author: bendikss
 */ 

#define F_CPU 4915200UL //Atmegaens CPU går vel på oscillatoren??
#include "GAME_driver.h"
#include "CAN_driver.h"
#include "macaroni.h"
#include "OLED_driver.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*Variable to keep record of the game being played*/
static game_parameters current_game;

/*
----------------------------
HIGHSCORES MEMORY LOCATIONS
"alex"	= 0b0
"asp"	= 0b1000
"benny" = 0b10000
----------------------------
*/

void GAME_init(){
	//Setting NORMAL mode, using prescaler 256
	TCCR1A = 0;
	clear_bit(TCCR1B, CS12);
	set_bit(TCCR1B, CS11);
	set_bit(TCCR1B, CS10);
	
	//Enabling overflow interrupt for TIMER1
	set_bit(TIMSK, TOIE1);
	//Clear interrupt flag
	clear_bit(TIFR, TOV1);
}


void GAME_play(char* name, uint8_t difficulty){
	//TODO: WRITE A START GAME CAN MESSAGE
	current_game.name = "benny";
	current_game.difficulty = difficulty;
	current_game.score = 0;
	
	SRAM_reset();
	OLED_pos(0, 30);
	OLED_print_str(current_game.name);
	OLED_pos(4, 0);
	OLED_print_str("GET READY...");
	OLED_draw();
	_delay_ms(1000);
	GAME_init();
	
	while(1){
		//TODO: switch on difficulty
		CAN_gamecontrols_transmit();
		_delay_ms(100); //how much DELAY??
		
		SRAM_reset();
		_delay_ms(100);
		OLED_pos(0, 30);
		OLED_print_str(current_game.name);
		OLED_pos(4, 0);
		OLED_print_str("Score:");
		OLED_pos(4, 70);
		OLED_print_str(OLED_int_to_str(current_game.score));
		OLED_draw();
		
		if (CAN_get_curr().id == 11)//EKSEMPEL TAPVERDI? DISKUTER
		{
			clear_bit(TIMSK, TOIE1); //Shutting off timer for counting score
			GAME_print_score(&current_game);
			_delay_ms(2000);
			if (!(strcmp(current_game.name, "alex"))) {
				unsigned int address = 0b0;
				if (current_game.score > GAME_EEPROM_read(address)) {
					GAME_EEPROM_write(current_game.score, "alex");
				}
			}
			else if (!(strcmp(current_game.name, "benny"))) {
				unsigned int address = 0b10000;
				if (current_game.score > GAME_EEPROM_read(address))
				{
					GAME_EEPROM_write(current_game.score, "benny");
				}
			}
			else if (!(strcmp(current_game.name, "asp"))) {
				unsigned int address = 0b1000;
				if (current_game.score > GAME_EEPROM_read(address))
				{
					GAME_EEPROM_write(current_game.score, "asp");
				}
			}
			GAME_EEPROM_print_highscores();
			_delay_ms(5000);
			break;
		}		
	}
}


void GAME_print_score(game_parameters* last_game){
	SRAM_reset();
	OLED_print_str("GAME OVER!");
	OLED_pos(3, 0);
	OLED_print_str("YOUR SCORE IS: ");
	OLED_pos(4, 10);
	OLED_print_str(OLED_int_to_str(current_game.score));
	OLED_draw();
}


void GAME_EEPROM_print_highscores(){
	SRAM_reset();
	OLED_pos(0, 20);
	OLED_print_str("HIGHSCORES");
	OLED_pos(1, 0);
	OLED_print_str("Alex:");
	OLED_pos(1, 60);
	OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(0b0))); //ADDRESS for alex
	OLED_pos(2, 0);
	OLED_print_str("Asp:");
	OLED_pos(2, 60);
	OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(0b1000))); //ADDRESS for asp
	OLED_pos(3, 0);
	OLED_print_str("Benny:");
	OLED_pos(3, 60);
	OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(0b10000))); //ADDRESS for Benny
	OLED_draw();
}


void GAME_inc_score(game_parameters* current_game){
	current_game->score += 1;
}


//void GAME_EEPROM_init(void){
	//
	//unsigned int ad_alex = 0b0;
	//unsigned int ad_asp = 0b1000;
	//unsigned int ad_ben = 0b10000;
//}


void GAME_EEPROM_write(unsigned char data, const char* name){
	
	while(EECR & (1<<EEWE)){};
	if (!strcmp(name, "alex")){
		EEAR = 0b0;
		EEDR = data;
	}
	else if (!strcmp(name, "asp")){
		EEAR = 0b1000;
		EEDR = data;
	}
	else if (!strcmp(name, "benny")){
		EEAR = 0b10000;
		EEDR = data;
	}
	set_bit(EECR, EEMWE);
	set_bit(EECR, EEWE);	
}

int GAME_EEPROM_read(unsigned int address){
	
	while(EECR & (1<<EEWE)){};
	EEAR = address;
	set_bit(EECR, EERE);
	return EEDR;
}


ISR(TIMER1_OVF_vect){
	GAME_inc_score(&current_game);
	//increase score by 1 per 1.05 seconds??
}