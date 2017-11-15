/*
 * GAME_driver.h
 *
 * Created: 15.11.2017 10:23:04
 *  Author: bendikss
 */ 


#ifndef GAME_DRIVER_H_
#define GAME_DRIVER_H_

#include <stdint.h>

//TODO: Implement timer on atmega162, play function, print scores, keep track of scores, highscores ++??
//TODO: turn of timer/interrupt when game over??
//TODO: FIx bugen med at den resetter seg!!

typedef struct  
game_parameters{	
	char* name;
	uint8_t score; //Make this larger??
	uint8_t difficulty;
}game_parameters;

/*GAME_init initializes the timer to keep track of the score...*/
void GAME_init(void);


/*Game function for the amazing pingpong game. Takes in the name of the player and desired difficulty 
(between 1-3) from the menu. Stores the score in highscores*/
void GAME_play(char* name, uint8_t difficulty);

void GAME_print_score(game_parameters* last_game);

/*Increases the game score to be used in the ISR*/
void GAME_inc_score(game_parameters* current_game);


//void GAME_EEPROM_init(void);
void GAME_EEPROM_write(unsigned char data, const char* name);
int GAME_EEPROM_read(unsigned int address);
/*Prints all highscores stored in EEPROM, hardcoded*/
void GAME_EEPROM_print_highscores(void);

#endif /* GAME_DRIVER_H_ */