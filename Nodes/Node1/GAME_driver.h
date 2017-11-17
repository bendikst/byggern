/*
 * GAME_driver.h
 *
 * Created: 15.11.2017 10:23:04
 *  Author: bendikss
 */ 

/*
---------------------------------------------------
HIGHSCORES MEMORY LOCATIONS
			Pingpong:	Snake:
"alex"	=		0			4	
"asp"	=		10			14
"benny" =		20			24
---------------------------------------------------
Procedure for adding new players:
- Include them in this overview
- Include them in the submenus for the games
- If names are used specifically in-game, handle.
- Change GAME_EEPROM_... write/read/print_highscores/reset to include given name and memory
*/

#ifndef GAME_DRIVER_H_
#define GAME_DRIVER_H_

#include <stdint.h>


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
void GAME_play(char* name);

void GAME_print_score(game_parameters* last_game);

/*Increases the game score to be used in the ISR*/
void GAME_inc_score(game_parameters* current_game);


/*Write to EEPROM on the atmega162. Be careful with uppercase and lowercase!*/
void GAME_EEPROM_write(unsigned char data, const char* name, const char* game);

/*Read from EEPROM. Addresses for different players can be found op the top of this file.*/
int GAME_EEPROM_read(unsigned int address);

/*Prints all highscores stored in EEPROM. Takes in the name of the game. Case-sensitive!*/
void GAME_EEPROM_print_highscores(char* name);

/*Resets highscores that are permanently stored.*/
void GAME_EEPROM_reset_highscores(void);

#endif /* GAME_DRIVER_H_ */
