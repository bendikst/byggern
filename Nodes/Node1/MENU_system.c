/*
 * MENU_system.c
 *
 * Created: 20.09.2017 17:40:12
 * Authors: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 

#define F_CPU 4915200UL
#include "MENU_system.h"
#include "SRAM.h"
#include <stdbool.h>
#include <util/delay.h>
#include "OLED_driver.h"
#include "SNAKE_game.h"
#include "GAME_driver.h"

/* Variables to keep track of where in the menu system we are */
static Menu* main_menu;
static int position;
static Menu* curr_menu;


Menu* MENU_init()
{
	
	main_menu = malloc(sizeof(Menu));
	
	main_menu->name = "MAIN MENU";
	main_menu->num_children = 0;
	main_menu->function = NULL;
	main_menu->parent = NULL;
	
	MENU_new_submenu(main_menu, "Snake", &SNAKE_play);
	
	Menu* pingpong_menu = MENU_new_submenu(main_menu, "Ping Pong", NULL);
		Menu* easy = MENU_new_submenu(pingpong_menu, "easy", &GAME_difficulty);
		//Menu* medium = MENU_new_submenu(pingpong_menu, "medium", &GAME_difficulty);
		Menu* hard = MENU_new_submenu(pingpong_menu, "hard", &GAME_difficulty);
			Menu* alex = MENU_new_submenu(easy, "alex", &GAME_play);
			Menu* asp = MENU_new_submenu(easy, "asp", &GAME_play);
			Menu* benny = MENU_new_submenu(easy, "benny", &GAME_play);
			Menu* guest = MENU_new_submenu(easy, "guest", &GAME_play);
			
			MENU_allocate_submenu(hard, alex);
			MENU_allocate_submenu(hard, asp);
			MENU_allocate_submenu(hard, benny);
			MENU_allocate_submenu(hard, guest);
    
	Menu* highscores_menu = MENU_new_submenu(main_menu, "Highscores", &GAME_EEPROM_print_highscores);
		//MENU_new_submenu(highscores_menu, "Snake", &GAME_EEPROM_print_highscores);
		//MENU_new_submenu(highscores_menu, "Pingpong", &GAME_EEPROM_print_highscores);
    
	MENU_new_submenu(main_menu,"Test", &SRAM_test);

	curr_menu = main_menu;
	position = 0;

	return main_menu;
}

Menu* MENU_new_submenu(Menu* self, char* name, void (*function)(char*))
{
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

void MENU_allocate_submenu(Menu* self, Menu* submenu)
{
	self->children = realloc(self->children, sizeof(Menu*)*(self->num_children+1));
	self->children[self->num_children] = submenu;
	self->num_children = self->num_children + 1;
}


void MENU_main()
{

	switch (JOYSTICK_getDirection())
	{
		case DOWN:
			position++;
			_delay_ms(200);
			break;
		case UP:
			position--;
			_delay_ms(100);
			break;
		case RIGHT:
			if (curr_menu->children != NULL)
			{
				curr_menu = curr_menu->children[position];
				position = 0;
				if (curr_menu->function != NULL)
				{
					OLED_SRAM_RESET();
					OLED_print_menu(curr_menu);
					MENU_run_functions();
					
				}
				_delay_ms(100);
			}
			break;
		case LEFT:
			if(curr_menu->parent != NULL)
			{
				curr_menu = curr_menu->parent;
				position = 0;
				_delay_ms(100);
			}
			break;
		default:
			break;
	}
	
	//Handling when the arrow moves outside bounds
	if (position == -1)
	{
		if (curr_menu->num_children == 0)
		{
			position = 0;
		}
		else
		{
			position = curr_menu->num_children-1;	
		}
		
	}
	else if(position >= curr_menu->num_children)
	{
		position = 0;
	}
	
	OLED_SRAM_RESET();
	OLED_print_menu(curr_menu);
	OLED_draw_arrow(position);
}


void MENU_run_functions()
{
	if (curr_menu->function == &SRAM_test)
	{
		(*curr_menu->function)("");
		curr_menu = curr_menu->parent;
	}
	else if (curr_menu->function == &GAME_EEPROM_print_highscores)
	{
		(*curr_menu->function)("Pingpong");
		_delay_ms(2000);
		curr_menu = curr_menu->parent;
	}
	else if (curr_menu->function == &GAME_play)
	{
		(*curr_menu->function)(curr_menu->name);
		curr_menu = main_menu;
	}
	else if (curr_menu->function == &GAME_difficulty)
	{
		(*curr_menu->function)(curr_menu->name);
		_delay_ms(100); //Wait for node 2 to react
	}
	
	else if (curr_menu->function == &SNAKE_play)
	{
		(*curr_menu->function)(curr_menu->name);
		curr_menu = curr_menu->parent;
	}
}
