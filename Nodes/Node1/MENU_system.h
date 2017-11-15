/*
 * MENU_system.h
 *
 * Created: 20.09.2017 17:40:57
 *  Author: aleksra
 */ 


#ifndef MENU_SYSTEM_H_
#define MENU_SYSTEM_H_

#include <stdlib.h>
#include <stdio.h>
#include "JOYSTICK_driver.h"


typedef struct Menu_struct Menu;

static Menu* main_menu;
static int position;
static Menu* curr_menu;

typedef struct Menu_struct
{
	char* name;
	Menu* parent;
	int num_children;
	Menu** children;
	
	void (*function)(void);
}Menu;



//Menu creation
Menu* MENU_init(void);
Menu* MENU_new_submenu(Menu* self, char* name, void (*function)(void));
Menu* MENU_new_submenu_warguments(Menu* self, char* name, void (*function)(char*, uint8_t));

//Menu navigation
void MENU_main(void);




#endif /* MENU_SYSTEM_H_ */