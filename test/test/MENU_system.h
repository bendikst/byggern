/*
 * MENU_system.h
 *
 * Created: 20.09.2017 17:40:57
 *  Author: aleksra
 */ 


#ifndef MENU_SYSTEM_H_
#define MENU_SYSTEM_H_

typedef struct Menu_struct Menu;

static Menu* main_menu;

typedef struct Menu_struct
{
	char* name;
	Menu* parent = NULL;
	int num_children;
	Menu* children;
	
}Menu;

void MENU_init(void);
void MENU_new_submenu(char* name, );


#endif /* MENU_SYSTEM_H_ */