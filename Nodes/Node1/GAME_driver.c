/*
 * GAME_driver.c
 *
 * Created: 15.11.2017 10:23:25
 *  Author: bendikss
 */ 

#define F_CPU 4915200UL

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


void GAME_init()
{
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


void GAME_play(char* name)
{
	current_game.name = name;
	current_game.score = 0;
	
	//Send a message to start the game module in Node 2:
	CAN_message start_game;
	start_game.id = 5;
	start_game.length = 1;
	start_game.data[0] = 0;
	
	OLED_SRAM_RESET();
	OLED_pos(0, 30);
	OLED_print_str(current_game.name);
	OLED_pos(4, 0);
	OLED_print_str("GET READY...");
	OLED_draw();
	CAN_transmit(&start_game);
	_delay_ms(100);
	
	GAME_init();
	while(1)
	{
		//TODO: switch on difficulty
		CAN_gamecontrols_transmit();
		_delay_ms(100); //how much DELAY??
		
		OLED_SRAM_RESET();
		OLED_pos(0, 30);
		OLED_print_str(current_game.name);
		OLED_pos(4, 0);
		OLED_print_str("SCORE:");
		OLED_pos(4, 70);
		OLED_print_str(OLED_int_to_str(current_game.score));
		OLED_draw();
		
		if (CAN_get_curr().id == 11)//EKSEMPEL TAPVERDI? DISKUTER
		{
			clear_bit(TIMSK, TOIE1); //Shutting off timer for counting score
			GAME_print_score(&current_game);
			_delay_ms(2000);
			if (!(strcmp(current_game.name, "alex"))) 
			{
				unsigned int address = 0;
				if (current_game.score > GAME_EEPROM_read(address)) 
				{
					GAME_EEPROM_write(current_game.score, "alex", "Pingpong");
				}
			}
			else if (!(strcmp(current_game.name, "benny"))) 
			{
				unsigned int address = 20;
				if (current_game.score > GAME_EEPROM_read(address))
				{
					GAME_EEPROM_write(current_game.score, "benny", "Pingpong");
				}
			}
			else if (!(strcmp(current_game.name, "asp"))) 
			{
				unsigned int address = 10;
				if (current_game.score > GAME_EEPROM_read(address))
				{
					GAME_EEPROM_write(current_game.score, "asp", "Pingpong");
				}
			}
			else if (!(strcmp(current_game.name, "guest"))) 
			{
				unsigned int address = 30;
				if (current_game.score > GAME_EEPROM_read(address))
				{
					GAME_EEPROM_write(current_game.score, "guest", "Pingpong");
				}
			}
			GAME_EEPROM_print_highscores("Pingpong");
			_delay_ms(5000);
			break;
		}		
	}
}


void GAME_difficulty(char* difficulty){
	CAN_message msg;
	msg.id = 8;
	msg.length = 1;
	if (difficulty == "hard")
	{
	msg.data[0] = 3;
	}
	else if (difficulty == "medium")
	{
		msg.data[0] = 2;
	}
	else
	{
		msg.data[0] = 1;
	}
	
	CAN_transmit(&msg);
}


void GAME_print_score(game_parameters* last_game)
{
	OLED_SRAM_RESET();
	OLED_print_str("GAME OVER!");
	OLED_pos(3, 0);
	OLED_print_str("SCORE: ");
	OLED_pos(3, 70);
	OLED_print_str(OLED_int_to_str(current_game.score));
	OLED_draw();
}


void GAME_EEPROM_print_highscores(char* game)
{
	if (!strcmp(game, "Pingpong"))
	{
		OLED_SRAM_RESET();
		OLED_pos(0, 0);
		OLED_print_str("---HIGHSCORES---");
		OLED_pos(1, 0);
		OLED_print_str("Alex:");
		OLED_pos(1, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(0))); //ADDRESS for alex
		OLED_pos(2, 0);
		OLED_print_str("Asp:");
		OLED_pos(2, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(10))); //ADDRESS for asp
		OLED_pos(3, 0);
		OLED_print_str("Benny:");
		OLED_pos(3, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(20))); //ADDRESS for Benny
		OLED_pos(4, 0);
		OLED_print_str("Guests:");
		OLED_pos(4, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(30))); //ADDRESS for Guest
		OLED_draw();
	}
	else if(!strcmp(game, "Snake"))
	{
		OLED_SRAM_RESET();
		OLED_pos(0, 0);
		OLED_print_str("---HIGHSCORES---");
		OLED_pos(1, 0);
		OLED_print_str("Alex:");
		OLED_pos(1, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(4)));
		OLED_pos(2, 0);
		OLED_print_str("Asp:");
		OLED_pos(2, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(14)));
		OLED_pos(3, 0);
		OLED_print_str("Benny:");
		OLED_pos(3, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(24)));
		OLED_pos(4, 0);
		OLED_print_str("Guests:");
		OLED_pos(4, 60);
		OLED_print_str(OLED_int_to_str(GAME_EEPROM_read(30)));
		OLED_draw();
	}
 	else 
	 {
		OLED_SRAM_RESET();
		OLED_pos(1,0);
		OLED_print_str("Error GAME.h");
		OLED_pos(4, 40);
		OLED_print_str(":(((");
		OLED_draw();
	}
}


void GAME_inc_score(game_parameters* current_game)
{
	current_game->score += 1;
}



void GAME_EEPROM_write(unsigned char data, const char* name, const char* game)
{
	while(EECR & (1<<EEWE)){};
	if (!strcmp(name, "alex"))
	{
		if (!strcmp(game, "Snake"))
		{
			EEAR = 4;
			EEDR = data;
		}
		else if (!strcmp(game, "Pingpong"))
		{
			EEAR = 0;
			EEDR = data;
		}
	}
	else if (!strcmp(name, "asp"))
	{
		if (!strcmp(game, "Snake"))
		{
			EEAR = 14;
			EEDR = data;
		}
		else if (!strcmp(game, "Pingpong"))
		{
			EEAR = 10;
			EEDR = data;
		}
	}
	else if (!strcmp(name, "benny"))
	{
		if (!strcmp(game, "Snake"))
		{
			EEAR = 24;
			EEDR = data;
		}
		else if (!strcmp(game, "Pingpong"))
		{
			EEAR = 20;
			EEDR = data;
		}
	}
	else if (!strcmp(name, "guest"))
	{
		if (!strcmp(game, "Snake"))
		{
			EEAR = 34;
			EEDR = data;
		}
		else if (!strcmp(game, "Pingpong"))
		{
			EEAR = 30;
			EEDR = data;
		}
	}
	set_bit(EECR, EEMWE);
	set_bit(EECR, EEWE);	
}

	
int GAME_EEPROM_read(unsigned int address)
{
	
	while(EECR & (1<<EEWE)){};
	EEAR = address;
	set_bit(EECR, EERE);
	return EEDR;
}


void GAME_EEPROM_reset_highscores()
{
	char* players[4] = {"alex","asp","benny", "guest"};
	for (int i = 0; i < 4; i++)
	{ 
		GAME_EEPROM_write(0, players[i], "Snake");
	}
	for (int i = 0; i < 4; i++)
	{
		GAME_EEPROM_write(0, players[i], "Pingpong");
	}
}

ISR(TIMER1_OVF_vect){
	GAME_inc_score(&current_game);
}
