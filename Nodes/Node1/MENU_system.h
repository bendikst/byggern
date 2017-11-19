/*
 * MENU_system.h
 *
 * Created: 20.09.2017 17:40:57
 * Authors: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 


#ifndef MENU_SYSTEM_H_
#define MENU_SYSTEM_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "JOYSTICK_driver.h"


typedef struct Menu_struct Menu;

typedef struct Menu_struct
{
	char* name;
	Menu* parent;
	uint8_t num_children;
	Menu** children;
	
	void (*function)(char*);
}Menu;



/* Menu creation handled here */
Menu* MENU_init(void);

/*Functions to create the submenus for a menu system. Takes in the menu itself,
 and the name of the submenu, in addidtion to the function pointer the submenu calls*/
Menu* MENU_new_submenu(Menu* self, char* name, void (*function)(char*));
void MENU_allocate_submenu(Menu* self, Menu* submenu);

/*Menu navigation is handled here. Heads up and down in the menu hierarchy according to input
from the joystick. Acts as Node 1's main function when in the MENU state.*/
void MENU_main(void);

/*Function to run the function pointers from the submenu structs.*/
void MENU_run_functions();



#endif /* MENU_SYSTEM_H_ */
