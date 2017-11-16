/*
 * MENU_source.c
 *
 * Created: 20.09.2017 17:40:12
 *  Author: aleksra
 */ 

#define F_CPU 4915200UL
#include "MENU_system.h"
#include "SRAM.h"
#include <stdbool.h>
#include <util/delay.h>
#include "OLED_driver.h"
#include "snake.h"
#include "GAME_driver.h"

/*Variables to keep track of where in the menu system we are*/
static Menu* main_menu;
static int position;
static Menu* curr_menu;


Menu* MENU_init(){
	//create main menu
	
	main_menu = malloc(sizeof(Menu));
	
	main_menu->name = "MAIN MENU";
	main_menu->num_children = 0;
	main_menu->function = NULL;
	main_menu->parent = NULL;
	
	
	Menu* sneakygirls_menu = MENU_new_submenu(main_menu,"Sneakygirls", NULL);
	MENU_new_submenu(main_menu,"Test", &SRAM_test);
	MENU_new_submenu(main_menu, "Snake", &play_snake);
	Menu* pingpong_menu = MENU_new_submenu(main_menu, "Ping Pong", NULL);
	Menu* highscores_menu = MENU_new_submenu(main_menu, "Highscores", NULL);
	
	MENU_new_submenu(pingpong_menu, "alex", &GAME_play);
	MENU_new_submenu(pingpong_menu, "asp", &GAME_play);
	MENU_new_submenu(pingpong_menu, "benny", &GAME_play);
	
	MENU_new_submenu(highscores_menu, "Snake", &GAME_EEPROM_print_highscores);
	MENU_new_submenu(highscores_menu, "Pingpong", &GAME_EEPROM_print_highscores);
	
	MENU_new_submenu(sneakygirls_menu,"Julie",NULL);
	MENU_new_submenu(sneakygirls_menu,"Andrea",NULL);
	MENU_new_submenu(sneakygirls_menu,"Johanne <3",NULL);
	MENU_new_submenu(sneakygirls_menu->children[0], "Snik", NULL);
	
	curr_menu = main_menu;
	position = 0;

	return main_menu;
}

Menu* MENU_new_submenu(Menu* self, char* name, void (*function)(char*)){
	Menu* new_menu = malloc(sizeof(Menu));
	
	new_menu->name = name;
	new_menu->parent = self;
	new_menu->num_children = 0;
	new_menu->children = NULL;
	new_menu->function = function;
	
	
	self->children = realloc(self->children, sizeof(Menu*)*(self->num_children+1));

	self->children[self->num_children] = new_menu;
	self->num_children = self->num_children + 1;
	
	return new_menu;
}


void MENU_main(){

	switch (JOYSTICK_getDirection()){
		case DOWN:
			position++;
			_delay_ms(200);
			break;
		case UP:
			position--;
			_delay_ms(100);
			break;
		case RIGHT:
			if (curr_menu->children != NULL){
				curr_menu = curr_menu->children[position];
				position = 0;
				_delay_ms(100);
			}
			break;
		case LEFT:
			if(curr_menu->parent != NULL){
				curr_menu = curr_menu->parent;
				position = 0;
				_delay_ms(100);
			}
			break;
		default:
			break;
	}
	
	if (curr_menu->function != NULL)
		{
			OLED_SRAM_RESET();
			OLED_print_menu(curr_menu);
			MENU_run_functions();
			
			//Trenger ikke dette når vi starter games osv??
			//VI vil heller oppdatere en state fra menu til riktig state?
			_delay_ms(1000);
			curr_menu = curr_menu->parent;
		}
	
	//Handling when the arrow moves outside bounds
	if (position == -1){
		if (curr_menu->num_children == 0){
			position = 0;
		}
		else{
			position = curr_menu->num_children-1;	
		}
		
	}else if(position >= curr_menu->num_children){
		position = 0;
	}
	
	OLED_SRAM_RESET();
	OLED_print_menu(curr_menu);
	OLED_draw_arrow(position);
}


void MENU_run_functions(){
	if (curr_menu->function == &SRAM_test)
	{
		(*curr_menu->function)("");
	}
	else if (curr_menu->function == &GAME_EEPROM_print_highscores)
	{
		(*curr_menu->function)(curr_menu->name);
		_delay_ms(2000);
	}
	else if (curr_menu->function == &GAME_play)
	{
		(*curr_menu->function)(curr_menu->name);
	}
	else if (curr_menu->function == &play_snake)
	{
		(*curr_menu->function)(curr_menu->name);
	}
	
	
}