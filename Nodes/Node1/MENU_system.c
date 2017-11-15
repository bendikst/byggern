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

Menu* MENU_init(){
	//create main menu
	
	main_menu = malloc(sizeof(Menu));
	
	main_menu->name = "MAIN MENU";
	main_menu->num_children = 0;
	main_menu->function = NULL;
	main_menu->parent = NULL;
	
	Menu* test_menu = MENU_new_submenu(main_menu,"test", &SRAM_test);
	Menu* sneakygirls_menu = MENU_new_submenu(main_menu,"sneakygirls", NULL);
	
	MENU_new_submenu(main_menu, "snake", &play_snake);
	MENU_new_submenu_warguments(main_menu, "Ping Pong", &GAME_play);
	
	MENU_new_submenu(sneakygirls_menu,"Julie",NULL);
	MENU_new_submenu(sneakygirls_menu,"Andrea",NULL);
	MENU_new_submenu(sneakygirls_menu,"Johanne <3",NULL);
	//uint8_t test = 99;
	//char* hei = OLED_int_to_str(&test);
	MENU_new_submenu(sneakygirls_menu->children[0], "Snik", NULL);
	//MENU_new_submenu(sneakygirls_menu->children[0], hei, NULL);
	curr_menu = main_menu;
	position = 0;

	return main_menu;
}

Menu* MENU_new_submenu(Menu* self, char* name, void (*function)(void)){
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

Menu* MENU_new_submenu_warguments(Menu* self, char* name, void (*function)(char*, uint8_t)){
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
			SRAM_reset();
			OLED_print_menu(curr_menu);
			//if (curr_menu->function == &GAME_play)
			//{
				//(*curr_menu->function)();
			//}
			
			(*curr_menu->function)();
			
			//Trenger ikke dette når vi starter games osv??
			//VI vil heller oppdatere en state fra menu til riktig state?
			_delay_ms(1000);
			curr_menu = curr_menu->parent;
		}
	
	
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
	
	SRAM_reset();
	OLED_print_menu(curr_menu);
	OLED_draw_arrow(position);
}